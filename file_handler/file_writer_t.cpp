#include "StdAfx.h"
#include "file_writer_t.h"
#include <boost/smart_ptr.hpp>
#include <boost/filesystem.hpp>
#include "header.h"

using namespace dk::net::protocol;

const std::string g_hash = "e785578f13afe28afd77527f7177db22";
file_writer_t::file_writer_t(std::size_t chunk,const std::string& file,std::size_t fid)
{
	_size = 0;
	_chunk = chunk;
	_fid = fid;
	_f.open(file,std::ios::binary | std::ios::in);

	if(_f.is_open())
	{
		boost::filesystem::path path =  file;
		_name = path.filename().string();
	}
}


file_writer_t::~file_writer_t(void)
{
}

const std::string& file_writer_t::get_hash()const
{
	return g_hash;
}

bool file_writer_t::get_message(std::size_t id,dk::net::message_t* p_msg)
{
	if(!_f.is_open())
	{
		return false;
	}
	if(_f.eof())
	{
		dk::net::writer_t write;
		write.push_data(g_hash.data(),g_hash.size());

		boost::scoped_array<char> buf (new char[_name.size() + sizeof(DWORD) * 4]);
		PFILE_INFO header = (PFILE_INFO)buf.get();
		header->code = DK_FILE_HANDLER_CODE_FILE_INFO;
		header->id = _fid;
		header->size = _size;
		header->len = _name.size();
		memcpy(buf.get() + sizeof(DWORD) * 4,_name.data(),_name.size());

		write.push_data(buf.get(),_name.size() + sizeof(DWORD) * 4);
		write.create_message(id,p_msg);

		_f.close();
	}
	else
	{
		dk::net::writer_t write;
		write.push_data(g_hash.data(),g_hash.size());

		boost::scoped_array<char> buf (new char[_chunk + sizeof(DWORD) * 4]);
		PFILE_DATA header = (PFILE_DATA)buf.get();
		header->code = DK_FILE_HANDLER_CODE_FILE_DATA;
		header->id = _fid;
		header->offset = _f.tellg();
		_f.read(buf.get() + sizeof(DWORD) * 4,_chunk);
		header->size = _f.gcount();
		_size += header->size;

		write.push_data(buf.get(),header->size + sizeof(DWORD) * 4);

		write.create_message(id,p_msg);
	}
	return true;
}