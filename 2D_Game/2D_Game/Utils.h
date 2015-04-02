#ifndef	__UTILS_HPP__
#define	__UTILS_HPP__

#include	<sstream>
#include	<string>
#include	<vector>

#define	ABS(x)	(x > 0) ? x : -x

std::string		IntToString(int);
int			StringToInt(std::string);
int			Case(int);

void init_randomize(std::vector<int> & randomize);

#endif
