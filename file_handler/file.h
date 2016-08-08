#pragma once
#include "header.h"
class file
{
public:
	file(std::size_t id);
	~file(void);

protected:
	std::ofstream _f;
	std::size_t _id;

	//已寫入 數據
	std::size_t _sum;

	//當前 文件 大小
	std::size_t _size;

	//文件名
	std::string _name;
	//文件 大小
	std::size_t _file_size;

	//緩存文件名
	std::size_t _tmp;
public:
	bool write(PFILE_DATA ptr);
	bool write(PFILE_INFO ptr);
protected:
	void close_file();
	void open_file();
	void seek(PFILE_DATA ptr);
};

typedef boost::shared_ptr<file> file_ptr_t;