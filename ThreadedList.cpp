#include <iostream>
#include <string>
using namespace std;

// 站点信息
struct Station {
    string name;
    double distance;//本站与上一站之间的距离
};

// 链表节点
struct Node {
    Station data;//保存当前节点的站点信息
    Node *next;
    //next是指向Node类型对象的指针
    //保存下一个节点的地址
};

// 初始化链表，创建头节点
void initList(Node *&head) {
    //*&引用和指针结合
    //&引用声明符 把头节点的地址传递进来
    head = new Node;
    //在动态内存中申请一个 Node 类型的节点
    //把节点的地址保存到head中
    head->next = nullptr;
    //通过指针访问node中的成员next nullptr是空
    //把
}

// 显示站点
void showList(Node *head) {
    Node *p = head->next;
    int i = 1;

    if (p == nullptr) {
        cout << "当前线路没有站点！\n";
        return;
    }

    while (p != nullptr) {
        cout << i << ". "
             << p->data.name
             << "，距离上一站 "
             << p->data.distance << " km\n";

        p = p->next;
        i++;
    }
}

// 查找站点，返回节点指针
Node *findStation(Node *head, string name) {
    Node *p = head->next;

    while (p != nullptr) {
        if (p->data.name == name) {
            return p;
        }
        p = p->next;
    }

    return nullptr;
}

// 插入站点，位置从 1 开始
void insertStation(Node *head, int pos,
                   string name, double distance) {
    if (pos < 1) {
        cout << "插入位置不合法！\n";
        return;
    }

    Node *p = head;

    // 找到插入位置的前一个节点
    for (int i = 1; i < pos && p != nullptr; i++) {
        p = p->next;
    }

    if (p == nullptr) {
        cout << "插入位置不合法！\n";
        return;
    }

    Node *s = new Node;
    s->data.name = name;
    s->data.distance = distance;

    // 将新节点插入链表
    s->next = p->next;
    p->next = s;

    cout << "增加成功！\n";
}

// 删除站点
void deleteStation(Node *head, string name) {
    Node *p = head;

    // 找到目标节点的前一个节点
    while (p->next != nullptr &&
           p->next->data.name != name) {
        p = p->next;
    }

    if (p->next == nullptr) {
        cout << "没有找到该站点！\n";
        return;
    }

    Node *temp = p->next;

    // 跳过目标节点
    p->next = temp->next;

    // 释放被删除节点
    delete temp;
    cout << "删除成功！\n";
}

// 修改站点
void updateStation(Node *head, string oldName,
                   string newName, double distance) {
    Node *p = findStation(head, oldName);

    if (p == nullptr) {
        cout << "没有找到该站点！\n";
        return;
    }

    p->data.name = newName;
    p->data.distance = distance;

    cout << "修改成功！\n";
}

// 释放整个链表
void destroyList(Node *head) {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

// 输出从 start 到 end 的乘车路线
// start、end 均为实际站点的节点指针
void showPath(Node *head, Node *start, Node *end) {
    Node *p = head->next;
    bool printing = false;

    while (p != nullptr) {
        if (p == start) {
            printing = true;
        }

        if (printing) {
            cout << p->data.name;

            if (p == end) {
                cout << endl;
                return;
            }

            cout << " -> ";
        }

        p = p->next;
    }
}

// 提高功能：从第一条线路换乘到第二条线路
void transfer(Node *a, Node *b) {
    string startName, endName;

    cout << "请输入出发站（第一条线路）：";
    cin >> startName;

    cout << "请输入目的站（第二条线路）：";
    cin >> endName;

    Node *start = findStation(a, startName);
    Node *end = findStation(b, endName);
    //将站点名转化为对应的站点指针

    if (start == nullptr || end == nullptr) {
        //没有指向有效节点
        cout << "出发站或目的站不在线路中！\n";
        return;
    }

    // 从出发站的下一站开始寻找换乘站
    Node *p = start->next;

    while (p != nullptr) {
        // 在第二条线路中查找相同站点
        Node *q = b->next;

        while (q != nullptr && q != end) {
            if (p->data.name == q->data.name) {
                cout << "\n推荐换乘方案：\n";

                cout << "第一段：乘坐线路1\n";
                showPath(a, start, p);

                cout << "在 " << p->data.name
                     << " 站换乘线路2。\n";

                cout << "第二段：乘坐线路2\n";
                showPath(b, q, end);

                return;
            }
            q = q->next;
        }
        p = p->next;
    }

    cout << "没有找到符合当前行驶方向的换乘方案！\n";
}

int main() {
    Node *bus1;
    Node *bus2;

    initList(bus1);
    initList(bus2);

    // 示例线路1：P1 -> P2 -> P3 -> P4
    insertStation(bus1, 1, "P1", 0);
    insertStation(bus1, 2, "P2", 1.2);
    insertStation(bus1, 3, "P3", 2.0);
    insertStation(bus1, 4, "P4", 1.5);

    // 示例线路2：Q1 -> Q2 -> P3 -> Q4
    insertStation(bus2, 1, "Q1", 0);
    insertStation(bus2, 2, "Q2", 1.0);
    insertStation(bus2, 3, "P3", 2.2);
    insertStation(bus2, 4, "Q4", 1.8);

    int choice, line, pos;
    string name, newName;
    double distance;

    do {
        cout << "\n===== 公交线路管理（链表）=====\n";
        cout << "1. 显示站点\n";
        cout << "2. 增加站点\n";
        cout << "3. 删除站点\n";
        cout << "4. 修改站点\n";
        cout << "5. 查询站点\n";
        cout << "6. 换乘查询\n";
        cout << "0. 退出\n";
        cout << "请选择：";
        cin >> choice;

        // 基本管理功能需要选择线路
        if (choice >= 1 && choice <= 5) {
            cout << "请选择线路（1 或 2）：";
            cin >> line;

            if (line != 1 && line != 2) {
                cout << "线路编号错误！\n";
                continue;
            }

            Node *head = (line == 1) ? bus1 : bus2;

            switch (choice) {
            case 1:
                showList(head);
                break;

            case 2:
                cout << "输入插入位置、站点名称、与上一站的距离：";
                cin >> pos >> name >> distance;
                insertStation(head, pos, name, distance);
                break;

            case 3:
                cout << "输入要删除的站点名称：";
                cin >> name;
                deleteStation(head, name);
                break;

            case 4:
                cout << "输入原站点名称、新名称、新距离：";
                cin >> name >> newName >> distance;
                updateStation(head, name, newName, distance);
                break;

            case 5: {
                cout << "输入要查询的站点名称：";
                cin >> name;

                Node *p = findStation(head, name);

                if (p == nullptr) {
                    cout << "没有找到该站点！\n";
                } else {
                    cout << "找到站点：" << p->data.name
                         << "，距离上一站："
                         << p->data.distance << " km\n";
                }
                break;
            }
            }
        } else {
            switch (choice) {
            case 6:
                transfer(bus1, bus2);
                break;

            case 0:
                cout << "退出系统。\n";
                break;

            default:
                cout << "输入有误！\n";
            }
        }

    } while (choice != 0);

    // 释放两条链表占用的内存
    destroyList(bus1);
    destroyList(bus2);

    return 0;
}
 //chcp 936
// g++ -finput-charset=UTF-8 -fexec-charset=GBK ThreadedList.cpp -o ThreadedList.exe
// .\ThreadedList.exe