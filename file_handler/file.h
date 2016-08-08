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

	//�ь��� ����
	std::size_t _sum;

	//��ǰ �ļ� ��С
	std::size_t _size;

	//�ļ���
	std::string _name;
	//�ļ� ��С
	std::size_t _file_size;

	//�����ļ���
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