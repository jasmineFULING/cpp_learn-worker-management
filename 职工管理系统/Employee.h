//∆’Õ®‘±π§
#pragma once
#include"worker.h"

class Employee :public Worker
{
public:
	Employee(int,std::string,int);
	void showinfo();
	std::string showdeptname();
};