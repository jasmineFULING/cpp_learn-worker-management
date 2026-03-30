//经理
#include <iostream>
#include"Manager.h"

Manager::Manager(int id, std::string name, int dpid)
{
	this->w_id = id;
	this->w_name = name;
	this->w_deptid = dpid;
}

std::string Manager::showdeptname()
{
	return "经理";
}
void Manager::showinfo()
{
	std::cout << "工号" << w_id << "\t";
	std::cout << "名字" << w_name << "\t";
	std::cout << "岗位" << this->showdeptname() << std::endl;
}
