#include "StdAfx.h"
#include "file_handler.h"

using namespace dk::net::protocol;

file_handler::file_handler(void)
{
}


file_handler::~file_handler(void)
{
}
bool file_handler::handler_message(SOCKET s,dk::net::message_t* p_msg)
{
	std::size_t size = 0;
	PFILE_INFO ptr = (PFILE_INFO)(p_msg->get_body(&size) + DK_PROTOCOL_HASH_SIZE);
	if(DK_FILE_HANDLER_CODE_FILE_INFO == ptr->code)
	{
		std::size_t id = ptr->id;
		file_ptr_t f = get_file(id);
		f->write(ptr);
	}
	else
	{
		std::size_t id = ptr->id;
		file_ptr_t f = get_file(id);
		f->write((PFILE_DATA)ptr);
	}
	return true;
}
file_ptr_t file_handler::get_file(std::size_t id)
{
	
	auto iter = _fs.find(id);
	if(iter != _fs.end())
	{
		return iter->second;
	}
	file_ptr_t f = boost::make_shared<file>(id);
	_fs.insert(std::make_pair(id,f));
	return f;
}