#pragma once

enum e_type
{
	BLOCK,
	DAMAGE,
	NONE
};

class Case
{
private:
	e_type type;

public:
	Case(void);
	~Case(void);
};

