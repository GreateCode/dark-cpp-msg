#include "StdAfx.h"
#include "error_t.h"
using namespace dk::net;

error_t::error_t()
{
	value = 0;
}

error_t::error_t(const error_t& copy)
{
	value = copy.value;
	emsg = copy.emsg;
}

error_t& error_t::operator=(const error_t& copy)
{
	value = copy.value;
	emsg = copy.emsg;
	return *this;
}

