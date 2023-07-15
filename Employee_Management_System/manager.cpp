#pragma once
#include"manager.h"

manager::manager(int id, string name, int dId) {
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = dId;
}

string manager::getDeptName() {
    return string("经理");
}

void manager::showInfo() {
    cout << "职工编号：" << this->m_id
         << "  职工姓名：" << this->m_name
         << "  岗位：" << this->getDeptName()
         << "  岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}