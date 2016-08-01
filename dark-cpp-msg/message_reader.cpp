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
	////沒有 讀取到 分片頭
	if(!_fragmentation)
	{
		//讀取分片頭
		_fragmentation = read_header();
		if(!_fragmentation)
		{
			//沒有 分片頭 數據 直接 返回
			return false;
		}
		//已讀分片頭
		if(_fragmentation_header)
		{
			//驗證 分片頭
			PMESSAGE_FRAGMENTATION_HEADER header_left = _fragmentation_header->get_header();
			PMESSAGE_FRAGMENTATION_HEADER header_right = _fragmentation->get_header();
			
			//消息 id 已 變化 丟棄 未接收完整的 消息
			if(header_left->id != header_right->id
				|| header_left->count != header_right->count)
			{
				_fragmentations.clear();
				_fragmentation_header = _fragmentation;
			}
		}
		else
		{
			//保存 消息頭
			_fragmentation_header = _fragmentation;
		}
	}

	//讀取 body
	PMESSAGE_FRAGMENTATION_HEADER header = _fragmentation->get_header();
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		//出現 新的 消息頭 丟棄消息
		if('^' == *iter)
		{
			//丟棄 錯誤消息
			_fragmentations.clear();
			_fragmentation_header.reset();
			_fragmentation.reset();

			//刪除 錯誤數據
			_datas.erase(_datas.begin(),iter);

			//重讀 消息
			return get_message(p_msg);
		}
		_fragmentation->get_unpack()->_body.push_back(*iter);

		if(_fragmentation->get_unpack()->_body.size() == header->size)
		{
			_fragmentations[header->order] = _fragmentation;
			//讀取到 1條 消息
			if(_fragmentations.size() == header->count)
			{
				//刪除 已讀數據
				++iter;
				_datas.erase(_datas.begin(),iter);
				//創建 消息 並返回
				if(create_message(p_msg))
				{
					//清空 讀取記錄
					reset();
					return true;
				}
				else
				{
					//清空 讀取記錄
					reset();

					//消息 錯誤 重讀
					return get_message(p_msg);
				}
			}
			//只讀取到 1條 分片 繼續 讀取 下條 分片
			_fragmentation.reset();
			return get_message(p_msg);
		}
	}

	//刪除 已讀數據
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
		//消息 錯誤 丟棄之
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

	//數據 小於 數據頭 等待新 數據
	if(_datas.size() < sizeof(MESSAGE_FRAGMENTATION_HEADER))
	{
		return fragmentation;
	}

	//讀取 分片頭
	fragmentation = boost::make_shared<message_fragmentation_t>();
	//PMESSAGE_FRAGMENTATION_HEADER
	char* header = (char*)fragmentation->get_header();
	iterator_t iter = _datas.begin();
	for(int i=0;i<sizeof(MESSAGE_FRAGMENTATION_HEADER);++i)
	{
		/*
		//出現新 頭標記 說明 數據錯誤 丟棄之
		if(i && *iter == '^')
		{
			_datas.erase(_datas.begin(),iter);
			return message_fragmentation_ptr_t();
		}
		*/

		header[i] = *iter;
		++iter;
	}
	//刪除 已讀數據
	_datas.erase(_datas.begin(),iter);
	return fragmentation;
}
bool message_reader::find_reader()
{
	for(iterator_t iter = _datas.begin();iter != _datas.end();++iter)
	{
		if(*iter == '^')
		{
			//刪除 分片頭 之前的 錯誤 數據
			_datas.erase(_datas.begin(),iter);
			return true;
		}
	}

	//不存在 分片頭 顯示是 錯誤數據 直接 丟棄
	_datas.clear();
	return false;
}