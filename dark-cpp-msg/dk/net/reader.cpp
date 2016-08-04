#include "StdAfx.h"
#include "reader.h"
using namespace dk::net;

reader::reader(void)
{
	_size = 0;
}


reader::~reader(void)
{
}
bool reader::get_message(const char* data,std::size_t size,message* p_msg)
{
	std::size_t pos = _datas.size();
	_datas.insert(_datas.end(),size,0);
	memcpy(_datas.data()+pos,data,size);
	return get_message(p_msg);
}
bool reader::get_message(message* p_msg)
{
	//�]�� �xȡ�� �^
	if(!_data)
	{
		//�xȡ�^
		_data = read_header();
		if(!_data)
		{
			//�]�� �^ ���� ֱ�� ����
			return false;
		}
		_size = 0;
	}

	//�]�� body ����
	if(_datas.empty())
	{
		return false;
	}

	PMESSAGE_HEADER header = (PMESSAGE_HEADER)_data->data();
	char* dist = _data->data() + sizeof(MESSAGE_HEADER) + _size;
	std::size_t need = header->size - _size;

	if(need > _datas.size())
	{
		//�xȡ���� ��Ϣ
		memcpy(dist,_datas.data(),_datas.size());
		//ӛ� �xȡ��
		_size +=  _datas.size();

		//�h�� ���x����
		_datas.clear();

		return false;
	}
	else
	{
		//�xȡ ����
		memcpy(dist,_datas.data(),need);

		//�h�� ���x����
		_datas.erase(_datas.begin(),_datas.begin() + need);		
		
		p_msg->_data = _data;

		_data.reset();
		return true;
	}

	/*
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		PMESSAGE_HEADER header = (PMESSAGE_HEADER)_data->data();
		char* ptr = _data->data() + sizeof(MESSAGE_HEADER);
		ptr[_size++] =  *iter;
		if(_size == header->size)
		{
			//�h�� ���x����
			++iter;
			_datas.erase(_datas.begin(),iter);

			p_msg->_data = _data;

			//����xȡӛ�
			_data.reset();
			return true;
		}

	}*/
	return false;
}
message_data_ptr_t reader::read_header()
{
	message_data_ptr_t data;
	if(!find_reader())
	{
		return data;
	}

	//���� С� �����^ �ȴ��� ����
	if(_datas.size() < sizeof(MESSAGE_HEADER))
	{
		return data;
	}

	//�xȡ ��Ƭ�^
	MESSAGE_HEADER header;
	memcpy((char*)&header,_datas.data(),sizeof(MESSAGE_HEADER));
	//std::copy(_datas.begin(),_datas.begin() + sizeof(MESSAGE_HEADER),(char*)&header);
	std::size_t size = sizeof(MESSAGE_HEADER) + header.size;
	data = boost::make_shared<std::vector<char>>(size,0);
	memcpy(data->data(),&header,sizeof(MESSAGE_HEADER));

	//�h�� ���x����
	_datas.erase(_datas.begin(),_datas.begin() + sizeof(MESSAGE_HEADER));
	return data;
}
bool reader::find_reader()
{
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		if(*iter == DK_MESSAGE_HEADER_FLAG_0)
		{
			iterator_t tmp_iter = iter;
			++tmp_iter;
			if(tmp_iter == _datas.end() || *tmp_iter != DK_MESSAGE_HEADER_FLAG_1)
			{
				continue;
			}
			++tmp_iter;
			if(tmp_iter == _datas.end() || *tmp_iter != DK_MESSAGE_HEADER_FLAG_2)
			{
				continue;
			}
			++tmp_iter;
			if(tmp_iter == _datas.end() || *tmp_iter != DK_MESSAGE_HEADER_FLAG_3)
			{
				continue;
			}
			//�h�� �^ ֮ǰ�� �e�` ����
			_datas.erase(_datas.begin(),iter);
			return true;
		}
	}

	//������ �^ �@ʾ�� �e�`���� ֱ�� �G��
	if(_datas.size() > 4)
	{
		_datas.erase(_datas.begin(),_datas.begin() + (_datas.size() - 4));
	}
	return false;
}