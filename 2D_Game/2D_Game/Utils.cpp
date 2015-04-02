#include	"Settings.h"
#include	"Utils.h"

std::string		IntToString(int number)
{
  std::ostringstream	oss;

  oss << number;
  return (oss.str());
}

int			StringToInt(std::string str)
{
  int			number;
  std::istringstream	iss(str);

  iss >> number;
  return (number);
}

int			Case(int n)
{
  return (n * Settings::CASE_SIZE);
}

void init_randomize(std::vector<int> & randomize)
{
	randomize.push_back(1);
	randomize.push_back(2);
	randomize.push_back(3);
	randomize.push_back(4);
	randomize.push_back(5);
	randomize.push_back(6);
	randomize.push_back(7);
	randomize.push_back(8);
	randomize.push_back(9);
	randomize.push_back(10);
}