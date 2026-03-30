#include <iostream>
#include "workerManager.h"

int main() {
	WorkerManager wm;

	while (true)
	{
		wm.showmenu();
		std::cout << "请选择功能" << std::endl;

		int choice;
		std:: cin >> choice;

		switch (choice)
		{
		case 0:
			wm.ExitSystem();//退出
			break;
		case 1:
			wm.addworker();
			break;
		case 2:
			wm.show_info();
			break;
		case 3:
			wm.del_Emp();
			break;
		case 4:
			wm.mod_Emp();
			break;
		case 5:
			wm.find();
			break;
		case 6:
			wm.order();
			break;
		case 7:
			wm.clean();
			break;
		default:
			system("cls");
			break;
		}
	}

	std::cin.get();
}