#include"employee.h"

employee::employee(int id, string name, int dId) {
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = dId;
}

string employee::getDeptName() {
    return string("员工");
}

void employee::showInfo() {
    cout << "职工编号：" << this->m_id
         << "  职工姓名：" << this->m_name
         << "  岗位：" << this->getDeptName()
         << "  岗位职责：完成经理交给的任务" << endl;
}