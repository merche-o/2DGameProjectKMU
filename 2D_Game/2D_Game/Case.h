#pragma once

enum e_type
{
	WALL,
	DAMAGE,
	NONE
};

class Case
{
public:
	e_type type;

private:

public:
	Case(void);
	~Case(void);
};

