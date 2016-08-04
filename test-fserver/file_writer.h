#pragma once
class file_writer
{
public:
	file_writer(std::size_t id,std::size_t size);
	~file_writer(void);

protected:
	std::ofstream _out;
	std::size_t _id;
	std::size_t _size;

	std::size_t _sum;

public:
	bool write_file(std::size_t pos,const char* data,std::size_t size);
};
typedef boost::shared_ptr<file_writer> file_writer_ptr_t;

