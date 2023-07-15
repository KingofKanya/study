#pragma once
#include<iostream>
#include<string>
#include "worker.h"
using namespace std;

class workerManager {
public:
    workerManager();
    ~workerManager();

    void show_menu();
    void exitSystem();

    //增加新员工
    void Add_Emp();

    //交换m和n编号员工的数据
    void exchange_info(int m,int n);

    //保存数据
    void save()const;

    //显示员工
    void show_emp()const;

    //统计文件中的人数
    int get_EmpNum();

    //删除职工
    void del_emp();

    //判断职工是否存在
    int IsExist(int id)const;

    //获取数据并存入
    void init_Emp();

    //查找职工
    void Find_Emp()const;

    //修改职工信息
    void change_Emp();

    //按照编号排序
    void sort_id();

    //清空数据
    void clean_file();

private:
    worker** m_EmpArray;
    int m_EmpNum;
    bool m_FileIsEmpty;
};

