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
	//沒有 讀取到 頭
	if(!_data)
	{
		//讀取頭
		_data = read_header();
		if(!_data)
		{
			//沒有 頭 數據 直接 返回
			return false;
		}
		_size = 0;
	}

	//沒有 body 數據
	if(_datas.empty())
	{
		return false;
	}

	PMESSAGE_HEADER header = (PMESSAGE_HEADER)_data->data();
	char* dist = _data->data() + sizeof(MESSAGE_HEADER) + _size;
	std::size_t need = header->size - _size;

	if(need > _datas.size())
	{
		//讀取部分 消息
		memcpy(dist,_datas.data(),_datas.size());
		//記錄 讀取量
		_size +=  _datas.size();

		//刪除 已讀數據
		_datas.clear();

		return false;
	}
	else
	{
		//讀取 數據
		memcpy(dist,_datas.data(),need);

		//刪除 已讀數據
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
			//刪除 已讀數據
			++iter;
			_datas.erase(_datas.begin(),iter);

			p_msg->_data = _data;

			//清空讀取記錄
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

	//數據 小於 數據頭 等待新 數據
	if(_datas.size() < sizeof(MESSAGE_HEADER))
	{
		return data;
	}

	//讀取 分片頭
	MESSAGE_HEADER header;
	memcpy((char*)&header,_datas.data(),sizeof(MESSAGE_HEADER));
	//std::copy(_datas.begin(),_datas.begin() + sizeof(MESSAGE_HEADER),(char*)&header);
	std::size_t size = sizeof(MESSAGE_HEADER) + header.size;
	data = boost::make_shared<std::vector<char>>(size,0);
	memcpy(data->data(),&header,sizeof(MESSAGE_HEADER));

	//刪除 已讀數據
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
			//刪除 頭 之前的 錯誤 數據
			_datas.erase(_datas.begin(),iter);
			return true;
		}
	}

	//不存在 頭 顯示是 錯誤數據 直接 丟棄
	if(_datas.size() > 4)
	{
		_datas.erase(_datas.begin(),_datas.begin() + (_datas.size() - 4));
	}
	return false;
}