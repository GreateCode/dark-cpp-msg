#include "StdAfx.h"
#include "file.h"
#include <boost/lexical_cast.hpp>
#include <vector>
file::file(std::size_t id)
{
	_id = id;
	_sum = _size = 0;
	_tmp = 0;

	_file_size = 0;
}


file::~file(void)
{
}
bool file::write(PFILE_DATA ptr)
{
	if(!_f.is_open())
	{
		open_file();
	}

	seek(ptr);

	_f.write(ptr->data,ptr->size);
	if(ptr->offset == _size)
	{
		_size += ptr->size;
	}
	_sum += ptr->size;
	if(_sum && _file_size >= _sum)
	{
		close_file();
		return true;
	}
	return false;
}
void file::seek(PFILE_DATA ptr)
{
	if(ptr->offset <= _size)
	{
		_f.seekp(ptr->offset);
	}
	else
	{
		_f.seekp(0,std::ios::end);
		std::size_t sum = ptr->offset - _size;
		_size = ptr->offset;

		std::size_t chunk = 1024*10;
		std::vector<char> fill(chunk,0);
		while(sum)
		{
			std::size_t need = chunk;
			if(need > sum)
			{
				need = sum;
			}
			_f.write(fill.data(),need);
			sum -= need;
		}
	}
}
bool file::write(PFILE_INFO ptr)
{
	_name = std::string(ptr->name,ptr->len);
	_file_size = ptr->size;

	if(_sum && _file_size >= _sum)
	{
		close_file();
		return true;
	}
	return false;
}
void file::close_file()
{
	_f.close();

	std::string name = boost::lexical_cast<std::string>(_tmp);
	name += "-";
	name += boost::lexical_cast<std::string>(_id);

	MoveFileA(name.c_str(),(name + "-" + _name).c_str());
}

void file::open_file()
{
	std::string name = boost::lexical_cast<std::string>(_tmp);
	name += "-";
	name += boost::lexical_cast<std::string>(_id);

	_f.open(name,std::ios::binary | std::ios::trunc | std::ios::out);
}