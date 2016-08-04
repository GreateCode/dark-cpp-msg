#pragma once
#include <boost/serialization/singleton.hpp>
#include "file_writer.h"

class upload_file
	: public boost::serialization::singleton<upload_file>
{
public:
	upload_file(void);
	~upload_file(void);

protected:
	std::size_t _id;
	boost::unordered_map<std::size_t,file_writer_ptr_t> _files;
public:
	std::size_t new_file(std::size_t size);
	bool write_file(std::size_t id,std::size_t pos,const char* data,std::size_t size);
};

