#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class manager :public worker {
public:
    manager(int id, string name, int dId);

    virtual void showInfo();//重写父类中的纯虚函数
    virtual string getDeptName();
};