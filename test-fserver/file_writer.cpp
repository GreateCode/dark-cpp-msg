#include "StdAfx.h"
#include "file_writer.h"

#include <boost/lexical_cast.hpp>
#include <vector>
file_writer::file_writer(std::size_t id,std::size_t size)
{
	_sum = 0;

	_id = id;
	_size = size;

	_out.open("f_" + boost::lexical_cast<std::string>(id),std::ios::binary|std::ios::out|std::ios::trunc);

	std::size_t sum = size;

	std::size_t node = 1024 * 10;
	std::vector<char> tmp(node,0);

	while(sum)
	{
		std::size_t need = sum;
		if(need > node)
		{
			need = node;
		}

		_out.write(tmp.data(),need);

		sum -= need;
	}
}


file_writer::~file_writer(void)
{
}

bool file_writer::write_file(std::size_t pos,const char* data,std::size_t size)
{
	if(!_out.is_open())
	{
		return false;
	}

	_out.seekp(pos,std::ios::beg);
	_out.write(data,size);

	_sum += size;

	if(_sum >= _size)
	{
		_out.close();
		return true;
	}
	return false;
}