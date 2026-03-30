#pragma once	
#include <iostream>
#include "worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
#include <fstream>
#define FILENAME "empfile.txt"

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	void showmenu();
	void ExitSystem();
	
	int w_num;
	Worker** w_array;
	void addworker();

	void save();
	bool isempty;
	int get_num();
	void Init();

	void show_info();
	void del_Emp();
	int isexist(int);
	void mod_Emp();
	void find();
	void order();
	void clean();
};