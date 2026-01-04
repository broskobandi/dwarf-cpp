#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

#ifndef NDEBUG
#define DBG(msg)\
	std::cout << (msg) << "\n"
#else
#define DBG(msg)
#endif

#endif
