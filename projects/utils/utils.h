#include "apr-1/apr.h"
#include <utility>
#include <vector>
#include <iostream>

typedef std::pair<apr_uint32_t, apr_uint32_t> Position; 

double distance(Position p1, Position p2);

Position findClosest(Position p1, Position p2, apr_uint32_t movement);

static apr_int32_t DummyInvokeService(const apr_byte_t * serviceName, void * serviceParams)
{
	if (serviceName == NULL /*|| serviceParams == NULL*/)
	{
		return -1;
	}
	std::cout << "----------------------" << std::endl;
	std::cout << "##" << serviceName << "##" << std::endl;
	std::cout << "----------------------" << std::endl;
	return 0;
}
