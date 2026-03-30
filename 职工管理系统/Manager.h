//æ≠¿Ì¿‡
#pragma once
#include "worker.h"

class Manager :public Worker
{
public:
	Manager(int, std::string, int);
	void showinfo();
	std::string showdeptname();
};