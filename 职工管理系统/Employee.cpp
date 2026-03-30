//员工类
#include <iostream>
#include"Emploee.h"

Employee::Employee(int id, std::string name, int dpid)
{
	this->w_id = id;
	this->w_name = name;
	this->w_deptid = dpid;
}

std::string Employee::showdeptname()
{
	return "员工";
}
void Employee::showinfo()
{
	std::cout << "工号" << w_id << "\t";
	std::cout << "名字" << w_name << "\t";
	std::cout << "岗位" << this->showdeptname() << std::endl;
}
