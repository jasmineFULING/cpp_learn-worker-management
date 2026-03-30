//¶­ÊÂ³¤Àà
#pragma once
#include "worker.h"

class Boss :public Worker
{
public:
	Boss(int, std::string, int);
	void showinfo();
	std::string showdeptname();
}; 
