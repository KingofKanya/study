#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include<fstream>
#define FILENAME "empFile.txt"
using std::cout;

workerManager::workerManager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在的情况
    if (!ifs.is_open()) {
        //cout << "文件不存在" << endl;
        m_EmpNum = 0;
        m_EmpArray = NULL;
        m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在但没有数据
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        //cout << "文件为空" << endl;
        m_EmpNum = 0;
        m_EmpArray = NULL;
        m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在&有数据
    int num = get_EmpNum();
    m_EmpNum = num;
    this->m_EmpArray = new worker * [m_EmpNum];
    init_Emp();


}

workerManager::~workerManager() {
    if (this->m_EmpArray != NULL) {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

//统计文件中的人数
int workerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        num++;
    }
    return num;
}

//获取数据并存入
void workerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;
    if (m_FileIsEmpty == true) {
        return;
    }
    else {
        int num = 0;
        while (ifs >> id && ifs >> name && ifs >> dId) {
            worker* worker = NULL;
            if (dId == 1) {
                worker = new employee(id, name, dId);
            }
            else if (dId == 2) {
                worker = new manager(id, name, dId);
            }
            else {
                worker = new boss(id, name, dId);
            }
            this->m_EmpArray[num] = worker;
            num++;
        }
    }


    ifs.close();
}

/**
* @brief 职工管理系统的欢迎页面
*/
void workerManager::show_menu() {
    cout << "****************************" << endl;
    cout << "****欢迎使用职工管理系统****" << endl;
    cout << "*******0.退出管理系统*******" << endl;
    cout << "*******1.增加职工信息*******" << endl;
    cout << "*******2.显示职工信息*******" << endl;
    cout << "*******3.删除离职职工*******" << endl;
    cout << "*******4.修改职工信息*******" << endl;
    cout << "*******5.查找职工信息*******" << endl;
    cout << "*******6.按照编号排序*******" << endl;
    cout << "*******7.清空所有文档*******" << endl;
    cout << "****************************" << endl;
    //cout << "若要保存数据修改，请通过 0 来退出程序" << endl;
    cout << endl;

}

//交换m和n编号员工的数据
void workerManager::exchange_info(int m,int n) {
    int i;
    i = m_EmpArray[n]->m_DeptId;
    m_EmpArray[n]->m_DeptId = m_EmpArray[m]->m_DeptId;
    m_EmpArray[m]->m_DeptId = i;

    i = m_EmpArray[n]->m_id;
    m_EmpArray[n]->m_id = m_EmpArray[m]->m_id;
    m_EmpArray[m]->m_id = i;

    string name = m_EmpArray[n]->m_name;
    m_EmpArray[n]->m_name = m_EmpArray[m]->m_name;
    m_EmpArray[m]->m_name = name;
}

//按照编号排序
void workerManager::sort_id() {
    if (m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    }
    else {
        //selection sort
        cout << "升序？y/n:" << endl;
        string flag;
        cin >> flag;
        int count = 0;
        if (flag == "y") {
            //cout << "flag=\"y\"";

            while (count != m_EmpNum ) {
                int m = count;
                for (int i = count+1;i < m_EmpNum;i++) {
                    if (m_EmpArray[i]->m_id < m_EmpArray[m]->m_id)m = i;
                }
                //cout << "this is a test" << endl;
                exchange_info(m, count);
                count++;
            }

            cout << "升序排序成功" << endl;
        }
        else {

            while (count != m_EmpNum) {
                int m = count;
                for (int i = count+1;i < m_EmpNum;i++) {
                    if (m_EmpArray[i]->m_id > m_EmpArray[m]->m_id)m = i;
                }
                exchange_info(m, count);
                count++;
            }

            cout << "降序排序成功" << endl;
        }
    }
    save();
    system("pause");
    system("cls");
}

//清空数据
void workerManager::clean_file() {
    cout << "确认清空数据？y/n   " << endl;
    string s;
    cin >> s;
    if (s == "y") {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if (m_EmpArray != NULL) {
            //删除堆区的每个职工对象
            for (int i = 0;i < m_EmpNum;i++) {
                delete m_EmpArray[i];
                m_EmpArray[i] = NULL;
            }

            //删除堆区指针数组
            delete[] m_EmpArray;

            m_EmpArray = NULL;
            m_EmpNum = 0;
            m_FileIsEmpty = true;
        }

        cout << "清空成功" << endl;
    }
    else {
        return;
    }
    system("pause");
    system("cls");
}

//查找职工
void workerManager::Find_Emp()const {
    int select;
    if (m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    }
    else {
        cout << "请输入查找方式：" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按职工姓名查找" << endl;
        cin >> select;
    }

    if (select == 1) {
        int id;
        cout << "请输入要查找的职工编号：" << endl;
        cin >> id;
        int ret = IsExist(id);
        if (ret == -1) {
            cout << "查无此人" << endl;
        }
        else {
            cout << "查找到第 " << id << " 号职工，信息如下：" << endl;
            m_EmpArray[ret]->showInfo();
        }
    }
    else if (select == 2) {
        string name;
        cout<< "请输入要查找的职工姓名：" ;
        cin >> name;

        int count = 0;
        for (int i = 0;i < m_EmpNum;i++) {
            if (m_EmpArray[i]->m_name == name) {
                m_EmpArray[i]->showInfo();
                count++;
            }
        }
        cout << "共查找到 "<<count<<" 符合要求的职工" << endl;
    }
    else {
        cout << "输入错误"<<endl;
    }
    system("pause");
    system("cls");

}

//判断职工是否存在,若存在返回下标
int workerManager::IsExist(int id) const{
    for (int i = 0;i < m_EmpNum;i++) {
        if (id == m_EmpArray[i]->m_id) return i;
    }
    return -1;
}

//修改职工信息
void workerManager::change_Emp() {
    if (m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    }
    else {
        int id;
        cout << "请输入要修改的职工编号：";
        cin >> id;
        int ret;
        while ((ret = IsExist(id)) == -1) {
            cout << "此职工编号不存在，请重新输入：";
            cin >> id;
        }

        delete m_EmpArray[ret];
        int newId;
        string newName;
        int newdId;

        cout << "查找到 " << id << " 号员工，请输入新工号：" << endl;
        cin >> newId;
        while (IsExist(newId) != -1) {
            cout << "此职工编号已经被占用，请重新输入：";
            cin >> newId;
        }

        cout << "请输入新姓名：" << endl;
        cin >> newName;

        cout << "请输入新岗位：" << endl;
        cout << "1、普通职工" << endl;
        cout << "2、经理" << endl;
        cout << "3、老板" << endl;
        cin >> newdId;

        worker* worker = NULL;
        switch (newdId)
        {
            case 1:
                worker = new employee(newId, newName, 1);
                break;
            case 2:
                worker = new manager(newId, newName, 2);
                break;
            case 3:
                worker = new boss(newId, newName, 3);
                break;
            default:
                break;
        }

        m_EmpArray[ret] = worker;

        cout << "修改成功" << endl;

    }
    save();
    system("pause");
    system("cls");
}

//删除职工
void workerManager::del_emp() {
    if (m_EmpNum == 0) {
        cout << "没有员工无法删除" << endl;
        system("pause");
        system("cls");
    }
    else {
        a://goto语句
        cout << "输入你要删除员工的编号：";
        int id;
        cin >> id;
        int t = IsExist(id);
        //cout << t << endl;
        if (t == -1) {
            cout << "删除失败，此员工不存在,请重新输入" << endl;
            goto a;//goto语句
        }
        else {
            m_EmpArray[t]->m_id = m_EmpArray[m_EmpNum-1]->m_id;
            m_EmpArray[t]->m_name = m_EmpArray[m_EmpNum-1]->m_name;
            m_EmpArray[t]->m_DeptId = m_EmpArray[m_EmpNum-1]->m_DeptId;
            m_EmpNum--;
            cout << "删除成功" << endl;
            save();
            system("pause");
            system("cls");
        }
    }

}

void workerManager::show_emp()const {
    int n = m_EmpNum;
    if (n== 0) {
        cout << "无职工" << endl;
    }
    else {
        cout << endl;
        for (int i = 0;i < n;i++) {
            //利用多态调用接口
            this->m_EmpArray[i]->showInfo();

        }

    }
    system("pause");
    system("cls");
}

void workerManager::exitSystem() {
    save();
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}


void workerManager::Add_Emp() {
    cout << "请输入增加职工数量：" << endl;

    int addNum;
    cin >> addNum;

    if (addNum > 0) {
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        worker** newSpace = new worker * [newSize];

        //将新空间的地址初始化为NULL，避免野指针
        for (int i = 0; i < newSize; i++) { newSpace[i] = NULL; }

        //将原空间的内容放到新空间下
        if (this->m_EmpArray != NULL) {
            for (int i = 0;i < m_EmpNum;i++) {
                newSpace[i] = m_EmpArray[i];
            }
        }

        //输入新数据
        for (int i = 0;i < addNum;i++) {
            int id;
            string name;
            int dSelect;

            cout << "请输入第 " << i + 1 << " 个新职员编号：" << endl;
            cin >> id;
            while (IsExist(id) != -1) {
                cout << "此职工编号已经被占用，请重新输入：";
                cin >> id;
            }

            cout << "请输入第 " << i + 1 << " 个新职员姓名：" << endl;
            cin >> name;

            cout << "请选择职工岗位：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            worker* worker = NULL;
            switch (dSelect)
            {
                case 1:
                    worker = new employee(id, name, 1);
                    break;
                case 2:
                    worker = new manager(id, name, 2);
                    break;
                case 3:
                    worker = new boss(id, name, 3);
                    break;
                default:
                    break;
            }
            newSpace[this->m_EmpNum + i] = worker;

        }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新新的个数
        this->m_EmpNum = newSize;

        cout << "成功添加" << addNum << "名新员工！" << endl;
        m_FileIsEmpty = false;
        //添加数据到文件中
        save();

        system("pause");
        system("cls");
    }
    else {
        cout << "输入有误" << endl;
    }
}

void workerManager::save()const {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0;i < this->m_EmpNum;i++) {
        ofs << this->m_EmpArray[i]->m_id << " "
            << this->m_EmpArray[i]->m_name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;

    }

    ofs.close();
}