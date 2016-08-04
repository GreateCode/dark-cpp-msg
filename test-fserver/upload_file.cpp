#include "StdAfx.h"
#include "upload_file.h"


upload_file::upload_file(void)
{
	_id = 0;
}


upload_file::~upload_file(void)
{
}
std::size_t upload_file::new_file(std::size_t size)
{
	++_id;
	file_writer_ptr_t ptr = boost::make_shared<file_writer>(_id,size);
	_files[_id] = ptr;
	return _id;
}

bool upload_file::write_file(std::size_t id,std::size_t pos,const char* data,std::size_t size)
{
	auto find = _files.find(id);
	if(find == _files.end())
	{
		return false;
	}

	return find->second->write_file(pos,data,size);
}