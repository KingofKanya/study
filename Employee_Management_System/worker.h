#pragma once
#include<string>
#include<iostream>
using namespace std;

class worker {
public:
    virtual void showInfo() = 0;
    virtual string getDeptName() = 0;//==获取职工岗位

    int m_id;//职工编号
    string m_name;
    int m_DeptId;//部门编号
};