#include<iostream>
#include"workerManager.h"
using namespace std;

int main() {
    //将终端的字符集设置为 UTF-8,并清屏.解决终端显示中文乱码问题
    system("chcp 65001");
    system("cls");

	workerManager wm;
	int choice = 0;
	while (true) {
		wm.show_menu();
		wm.init_Emp();
		cout << "请输入你的选择：" << endl;
		cin >> choice;

		switch (choice) {
			case 0:
				wm.exitSystem();
				break;
			case 1:
				wm.Add_Emp();
				break;
			case 2:
				wm.show_emp();
				break;
			case 3:
				wm.del_emp();
				break;
			case 4:
				wm.change_Emp();
				break;
			case 5:
				wm.Find_Emp();
				break;
			case 6:
				wm.sort_id();
				break;
			case 7:
				wm.clean_file();
				break;
			default:
				system("cls");
				break;
		}
	}

	system("pause");
	return 0;
}