#include "StdAfx.h"
#include "writer.h"
using namespace dk::net;

writer::writer(void)
{
}


writer::~writer(void)
{
}
void writer::push_data(const char* data,std::size_t size)
{
	buffer_ptr_t buf(new char[size]);
	memcpy(buf.get(),data,size);
	_buffers.push_back(std::make_pair(size,buf));
}

void writer::create_message(std::size_t id,message* p_msg)
{
	std::size_t sum = 0;
	BOOST_FOREACH(const buffer_t& node,_buffers)
	{
		sum += node.first;
	}
	std::size_t size = sizeof(MESSAGE_HEADER) + sum;
	
	message_data_ptr_t data = boost::make_shared<std::vector<char>>(size,0);
	p_msg->_data = data;

	PMESSAGE_HEADER header = (PMESSAGE_HEADER)data->data();
	header->flag[0] = DK_MESSAGE_HEADER_FLAG_0;
	header->flag[1] = DK_MESSAGE_HEADER_FLAG_1;
	header->flag[2] = DK_MESSAGE_HEADER_FLAG_2;
	header->flag[3] = DK_MESSAGE_HEADER_FLAG_3;
	header->id = id;
	header->size = sum;

	std::size_t pos = sizeof(MESSAGE_HEADER);

	BOOST_FOREACH(const buffer_t& node,_buffers)
	{
		std::copy(node.second.get(),node.second.get() + node.first,data->data() + pos);
		pos += node.first;
	}

	_buffers.clear();
}