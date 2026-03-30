//董事长
#include <iostream>
#include"Boss.h"

Boss::Boss(int id, std::string name, int dpid)
{
	this->w_id = id;
	this->w_name = name;
	this->w_deptid = dpid;
}

std::string Boss::showdeptname()
{
	return "董事长";
}
void Boss::showinfo()
{
	std::cout << "工号" << w_id << "\t";
	std::cout << "名字" << w_name << "\t";
	std::cout << "岗位" << this->showdeptname() << std::endl;
}
