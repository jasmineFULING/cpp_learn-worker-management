//员工抽象基类
#pragma once
#include <string>

class Worker
{
public:
	virtual void showinfo() = 0;
	virtual std::string showdeptname() = 0;
	int w_id;
	std::string w_name;
	int w_deptid;
	virtual ~Worker() {}
};
