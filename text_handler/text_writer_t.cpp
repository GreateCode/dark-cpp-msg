#include "StdAfx.h"
#include "text_writer_t.h"
using namespace dk::net::protocol;

const std::string g_hash = "e5600412de0ad3cd63c0cc823ecdaa1d";
text_writer_t::text_writer_t(const char* str,std::size_t size)
{
	if(str && size)
	{
		_ok = true;
		_writer.push_data(g_hash.data(),g_hash.size());
		_writer.push_data(str,size);
	}
	else
	{
		_ok = false;
	}
}


text_writer_t::~text_writer_t(void)
{
}
const std::string& text_writer_t::get_hash()const
{
	return g_hash;
}
				
bool text_writer_t::get_message(std::size_t id,dk::net::message_t* p_msg)
{
	if(_ok)
	{
		_writer.create_message(id,p_msg);
		_ok = false;
		return true;
	}
	return false;
}