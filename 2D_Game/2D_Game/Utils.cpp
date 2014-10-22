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
