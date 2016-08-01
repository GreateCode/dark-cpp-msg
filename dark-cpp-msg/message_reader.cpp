#include "StdAfx.h"
#include "message_reader.h"
#include "message_fragmentation.h"
#include "message.h"


message_reader::message_reader(void)
{
	
}


message_reader::~message_reader(void)
{
	
}
bool message_reader::get_message(const char* data,std::size_t size,message_t* p_msg)
{
	for(std::size_t i=0;i<size;++i)
	{
		_datas.push_back(data[i]);
	}
	return get_message(p_msg);
}
bool message_reader::get_message(message_t* p_msg)
{
	////�]�� �xȡ�� ��Ƭ�^
	if(!_fragmentation)
	{
		//�xȡ��Ƭ�^
		_fragmentation = read_header();
		if(!_fragmentation)
		{
			//�]�� ��Ƭ�^ ���� ֱ�� ����
			return false;
		}
		//���x��Ƭ�^
		if(_fragmentation_header)
		{
			//��C ��Ƭ�^
			PMESSAGE_FRAGMENTATION_HEADER header_left = _fragmentation_header->get_header();
			PMESSAGE_FRAGMENTATION_HEADER header_right = _fragmentation->get_header();
			
			//��Ϣ id �� ׃�� �G�� δ���������� ��Ϣ
			if(header_left->id != header_right->id
				|| header_left->count != header_right->count)
			{
				_fragmentations.clear();
				_fragmentation_header = _fragmentation;
			}
		}
		else
		{
			//���� ��Ϣ�^
			_fragmentation_header = _fragmentation;
		}
	}

	//�xȡ body
	PMESSAGE_FRAGMENTATION_HEADER header = _fragmentation->get_header();
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		//���F �µ� ��Ϣ�^ �G����Ϣ
		if('^' == *iter)
		{
			//�G�� �e�`��Ϣ
			_fragmentations.clear();
			_fragmentation_header.reset();
			_fragmentation.reset();

			//�h�� �e�`����
			_datas.erase(_datas.begin(),iter);

			//���x ��Ϣ
			return get_message(p_msg);
		}
		_fragmentation->get_unpack()->_body.push_back(*iter);

		if(_fragmentation->get_unpack()->_body.size() == header->size)
		{
			_fragmentations[header->order] = _fragmentation;
			//�xȡ�� 1�l ��Ϣ
			if(_fragmentations.size() == header->count)
			{
				//�h�� ���x����
				++iter;
				_datas.erase(_datas.begin(),iter);
				//���� ��Ϣ �K����
				if(create_message(p_msg))
				{
					//��� �xȡӛ�
					reset();
					return true;
				}
				else
				{
					//��� �xȡӛ�
					reset();

					//��Ϣ �e�` ���x
					return get_message(p_msg);
				}
			}
			//ֻ�xȡ�� 1�l ��Ƭ �^�m �xȡ �l ��Ƭ
			_fragmentation.reset();
			return get_message(p_msg);
		}
	}

	//�h�� ���x����
	_datas.clear();
	return false;
}
void message_reader::reset()
{
	_fragmentation.reset();
	_fragmentation_header.reset();
	_fragmentations.clear();
}
bool message_reader::create_message(message_t* p_msg)
{
	message* msg = new message();
	WORD id = 0;
	BOOST_FOREACH(auto& node,_fragmentations)
	{
		//��Ϣ �e�` �G��֮
		if(node.first != id)
		{
			delete msg;
			return false;
		}

		msg->insert(node.second);

		++id;
	}


	message* ptr = p_msg->swap(msg);
	if(ptr)
	{
		delete ptr;
	}
	return true;
}
message_fragmentation_ptr_t message_reader::read_header()
{
	message_fragmentation_ptr_t fragmentation;
	if(!find_reader())
	{
		return fragmentation;
	}

	//���� С� �����^ �ȴ��� ����
	if(_datas.size() < sizeof(MESSAGE_FRAGMENTATION_HEADER))
	{
		return fragmentation;
	}

	//�xȡ ��Ƭ�^
	fragmentation = boost::make_shared<message_fragmentation_t>();
	//PMESSAGE_FRAGMENTATION_HEADER
	char* header = (char*)fragmentation->get_header();
	iterator_t iter = _datas.begin();
	for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
	{
		/*
		//���F�� �^��ӛ �f�� �����e�` �G��֮
		if(i && *iter == '^')
		{
			_datas.erase(_datas.begin(),iter);
			return message_fragmentation_ptr_t();
		}
		*/

		header[i] = *iter;
		++iter;
	}
	//�h�� ���x����
	_datas.erase(_datas.begin(),iter);
	return fragmentation;
}
bool message_reader::find_reader()
{
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		if(*iter == '^')
		{
			//�h�� ��Ƭ�^ ֮ǰ�� �e�` ����
			_datas.erase(_datas.begin(),iter);
			return true;
		}
	}

	//������ ��Ƭ�^ �@ʾ�� �e�`���� ֱ�� �G��
	_datas.clear();
	return false;
}