#include "workerManager.h"

WorkerManager::WorkerManager()
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);
	//文件不存在
	if( !ifs.is_open() )
	{
		std::cout << "文件不存在" << std::endl;
		w_num = 0;
		w_array = nullptr;
		isempty = true;
		ifs.close();

		return;
	}
	//文件存在但为空
	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		std::cout << "文件为空" << std::endl;
		w_num = 0;
		w_array = nullptr;
		isempty = true;
		ifs.close();

		return;
	}
//文件存在不为空
	w_num = get_num();
	w_array = new Worker* [w_num];
	isempty = false;
	ifs.close();
	Init();

}

WorkerManager::~WorkerManager()
{
	if (w_array != nullptr)
	{
		for (int i = 0; i < w_num; i++)
			delete w_array[i];
		delete[]w_array;
		w_array = nullptr;
		w_num = 0;
		isempty = true;
	}
}

void WorkerManager::showmenu()
{
	std::cout << "欢迎使用职工管理系统" << std::endl;
	std::cout << "0.退出	" << std::endl;
	std::cout << "1.增加	" << std::endl;
	std::cout << "2.显示信息" << std::endl;
	std::cout << "3.删除	" << std::endl;
	std::cout << "4.修改	" << std::endl;
	std::cout << "5.查找	" << std::endl;
	std::cout << "6.排序	" << std::endl;
	std::cout << "7.清空	" << std::endl;
	
}

void WorkerManager::ExitSystem()
{
	std::cout << "欢迎下次使用" << std::endl;

	std::cin.get();
	exit(0);
}

void WorkerManager::addworker()
{
	std::cout << "请输入要添加职工数" << std::endl;
	int num = 0;
	std::cin >> num;
	if (num > 0)
	{
		int new_size = w_num + num;
		Worker** new_array = new Worker* [new_size];
		if (w_array != nullptr)
		{
			for (int i = 0; i < w_num; i++)
			{
				new_array[i] = w_array[i];
			}
		}//原数据迁移
		for (int i = 0; i < num; i++)
		{
			int id;
			std::string name;
			int deptid;
			Worker* worker = nullptr;
			
			while (true)
			{
				std::cout << "请输入第" << i + 1 << "职工工号" << std::endl;
				bool flag = 0;
				std::cin >> id;
				for (int j = 0; j < w_num; ++j)
				{
					if (w_array[j]->w_id == id)
					{
						std::cout << "职工号已存在" << std::endl;
						flag = 1;
					}
				}
				if (flag == 0)
					break;
			}
			std::cout << "请输入第" << i + 1 << "职工姓名" << std::endl;
			std::cin >> name;
			std::cout << "请输入第" << i + 1 << "职工岗位" << std::endl;
			std::cout << "1.员工2.经理3.董事长" << std::endl;
			std::cin >> deptid;
			switch (deptid)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			}
			new_array[w_num + i] = worker;
			
		}//加新数据
		w_num += num;
		delete[]w_array;
		w_array = new_array;
		isempty = false;
		//保存
		save();
		std::cout << "添加成功" << std::endl;
	}
	else
		std::cout << "输入有误" << std::endl;
	
	std::cin.get();
	std::cin.get();
	system("cls");

}

void WorkerManager::save()
{
	std::ofstream ofs;
	ofs.open(FILENAME, std::ios::out);
	
	for (int i = 0; i < w_num; i++)
	{
		ofs << w_array[i]->w_id << " ";
		ofs << w_array[i]->w_name << " ";
		ofs << w_array[i]->w_deptid << std::endl;
	}
	ofs.close();
}

int WorkerManager::get_num()
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);

	int num = 0;
	int id;
	std::string name;
	int dtid;
	while (ifs >> id && ifs >> name && ifs >> dtid)
		num++;
	ifs.close();
	return num;
}

void WorkerManager::Init()
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);

	int id;
	std::string name;
	int dpid;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dpid)
	{
		Worker* worker = nullptr;

		if (dpid == 1)
		{
			worker = new Employee(id, name, dpid);
		}
		else if (dpid == 2)
		{
			worker = new Manager(id, name, dpid);
		}
		else
		{
			worker = new Boss(id, name, dpid);
		}
		w_array[index] = worker;
		++index;
	}
	ifs.close();
}

void WorkerManager::show_info()
{
	if (!isempty)
	{
		for (int i = 0; i < w_num; i++)
			w_array[i]->showinfo();
	}
	else
		std::cout << "记录为空" << std::endl;

	std::cin.get();
	std::cin.get();
	system("cls");
}

void WorkerManager::del_Emp()
{
	if (isempty)
		std::cout << "文件不存在或记录为空" << std::endl;
	else
	{
		std::cout << "请输入要删除的职工号" << std::endl;
		int id = 0;
		std::cin >> id;
		int index = isexist(id);
		if (index != -1)
		{
			delete w_array[index];
			for (int i = index; i < w_num - 1; ++i)
			{
				w_array[i] = w_array[i + 1];
			}
			--w_num;
			save();

			std::cout << "删除成功" << std::endl;
		}
		else
			std::cout << "职工不存在" << std::endl;
	}
	std::cin.get();
	system("cls");
}
int WorkerManager::isexist(int id)
{
	int index = -1;

	for (int i = 0; i < w_num; i++)
	{
		if (w_array[i]->w_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::mod_Emp()
{
	if (isempty)
		std::cout << "文件不存在或文件清空" << std::endl;
	else
	{
		std::cout << "请输入要修改的职工号" << std::endl;
		int id = 0;
		std::cin >> id;
		int index = isexist(id);
		if (index != -1)
		{
			delete w_array[index];

			int m_id;
			std::string m_name;
			int  m_dpid;
			while (true)
			{
				std::cout << "请输入第" << id << "号新职工工号" << std::endl;

				bool flag = 0;
				std::cin >> m_id;

				for (int j = 0; j < w_num; ++j)
				{
					if (j != index && w_array[j]->w_id == id)
					{
						std::cout << "职工号已存在" << std::endl;
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					break;
			}
			std::cout << "请输入第" << id << "号新职工姓名" << std::endl;
			std::cin >> m_name;
			std::cout << "请输入第" << id << "号新职工岗位" << std::endl;
			std::cout << "1.员工2.经理3.董事长" << std::endl;
			std::cin >> m_dpid;
			Worker* worker = nullptr;
			switch (m_dpid)
			{
			case 1:
				worker = new Employee(m_id, m_name, 1);
				break;
			case 2:
				worker = new Manager(m_id, m_name, 2);
				break;
			case 3:
				worker = new Boss(m_id, m_name, 3);
				break;
			}
			w_array[index] = worker;
			save();
			std::cout << "修改成功" << std::endl;
		}
		else
			std::cout << "职工不存在" << std::endl;
	}
	std::cin.get();
	system("cls");
}

void WorkerManager::find()
{
	if(isempty)
		std::cout << "文件不存在或文件清空" << std::endl;
	else
	{
		std::cout << "请选择查找方式" << std::endl;
		std::cout << "1.按职工号	2.按姓名" << std::endl;
		int num = 0;
		std::cin >> num;
		if (num == 1)
		{
			std::cout << "请输入要查找的职工号" << std::endl;
			int id = 0;
			std::cin >> id;
			int index = isexist(id);
			if (index != -1)
			{
				std::cout << id << "号职工信息为" << std::endl;
				w_array[index]->showinfo();
			}
			else
				std::cout << "查无此人" << std::endl;
		}
		else if (num == 2)
		{
			std::cout << "请输入要查找的职工姓名" << std::endl;
			std::string name;
			std::cin >> name;
			bool flag = 0;
			for (int i = 0; i < w_num; ++i)
			{
				if (w_array[i]->w_name == name)
				{
					std::cout << name << "职工信息为" << std::endl;
					w_array[i]->showinfo();
					flag = 1;
				}
			}
			if (flag == 0)
				std::cout << "查无此人" << std::endl;
		}
	}
	std::cin.get();
	std::cin.get();
	system("cls");
}

void WorkerManager::order()
{
	if (isempty)
	{
		std::cout << "文件不存在或文件清空" << std::endl;
		std::cin.get();
		system("cls");
	}
	else
	{
		std::cout << "请输入排序方式" << std::endl;
		std::cout << "1.升序	2.降序" << std::endl;
		int select;
		std::cin >> select;
		for (int i = 0; i < w_num; ++i)
		{
			int mainnum = i;
			for (int j = i + 1; j < w_num; ++j)
			{
				if (select == 2)
				{
					if (w_array[j]->w_id > w_array[mainnum]->w_id)
						mainnum = j;
				}
				if (select == 1)
				{
					if (w_array[j]->w_id < w_array[mainnum]->w_id)
						mainnum = j;
				}
			}
			if (mainnum != i)
			{
				Worker* temp = w_array[i];
				w_array[i] = w_array[mainnum];
				w_array[mainnum] = temp;
			}
		}
		std::cout << "排序成功" << std::endl;
		save();
		show_info();
	}
}

void WorkerManager::clean()
{
	std::cout << "确认清空吗" << std::endl;
	std::cout << "1.确认2.返回" << std::endl;
	int select;
	std::cin >> select;
	if (select == 1)
	{
		if (isempty)
			std::cout << "文件不存在或文件清空" << std::endl;
		else
		{
			std::ofstream ofs;
			ofs.open(FILENAME, std::ios::trunc);
			ofs.close();
			if (w_array != nullptr)
			{
				for (int i = 0; i < w_num; i++)
					delete w_array[i];
				delete[]w_array;
				w_array = nullptr;
				w_num = 0;
				isempty = true;
			}
		}
	}
	std::cin.get();
	std::cin.get();
	system("cls");
}