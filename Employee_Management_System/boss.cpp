#pragma once
#include"boss.h"

boss::boss(int id, string name, int dId) {
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = dId;
}

string boss::getDeptName() {
    return string("老板");
}

void boss::showInfo() {
    cout << "职工编号：" << this->m_id
         << "  职工姓名：" << this->m_name
         << "  岗位：" << this->getDeptName()
         << "  岗位职责：管理公司所有职务" << endl;
}