#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// 站点信息
struct Station {
    string name;       // 站点名称
    double distance;  // 与上一站的距离（km）
};

// 顺序表
struct SeqList {
    Station data[MAX];
    //data数组中包含不超过100个数组元素
    //每个元素都是Station类型的站点
    //e.data[0].name可以理解为:先找到数组中的第一个站点，再访问它的 name成员
    int length;
    //表示当前顺序表中实际存储了多少个站点
    //通过 length，程序就知道哪些位置是有效数据，不需要遍历整个数组。
};

// 初始化
void initList(SeqList &list) {
    //加上&是引用传递 不是简单复制数值
    //表示接收一个SeqList类型的变量 并通过引用操作它本身 也就是操作顺序表
    list.length = 0;
    //初始化list中的length为0
}

// 显示线路
void showList(SeqList &list) {
    if (list.length == 0) {
        cout << "线路为空！" << endl;
        return;
    }

    for (int i = 0; i < list.length; i++) {
        cout << list.data[i].name;
        if (i < list.length - 1) cout << " -> ";
    }
    cout << endl;
}

// 查找站点，返回下标；找不到返回 -1
int findStation(SeqList &list, string name) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i].name == name) {
            return i;
        }
    }
    return -1;
}

// 插入站点，pos 从 1 开始
void insertStation(SeqList &list, int pos,
                   string name, double distance) {
    if (list.length >= MAX) {
        cout << "线路已满，无法添加！" << endl;
        return;
    }
    if (pos < 1 || pos > list.length + 1) {
        cout << "插入位置不合法！" << endl;
        return;
    }

    int index = pos - 1;
    //插入位置对应的下标

    for (int i = list.length; i > index; i--) {
        list.data[i] = list.data[i - 1];
        //从后往前挨个移动站点元素 空出插入元素的位置
    }

    list.data[index].name = name;
    list.data[index].distance = distance;
    list.length++;

    cout << "添加成功！" << endl;
}

// 删除站点
void deleteStation(SeqList &list, string name) {
    int index = findStation(list, name);
    //返回查找到站点的下标

    if (index == -1) {
        cout << "没有找到该站点！" << endl;
        return;
    }

    for (int i = index; i < list.length - 1; i++) {
        list.data[i] = list.data[i + 1];
    }
    //从前往后挨个移动站点元素

    list.length--;
    cout << "删除成功！" << endl;
}

// 修改站点名称和与前一站的距离
void updateStation(SeqList &list, string oldName,
                   string newName, double distance) {
    int index = findStation(list, oldName);
    //index是通过findStation查找函数返回的要修改的站点对应的下标
    if (index == -1) {
        cout << "没有找到该站点！" << endl;
        return;
    }
    list.data[index].name = newName;
    list.data[index].distance = distance;
    //distance是修改后的、与前一站之间的距离
    cout << "修改成功！" << endl;
}

// 查询站点
void queryStation(SeqList &list, string name) {
    int index = findStation(list, name);
    if (index == -1) {
        cout << "没有找到该站点！" << endl;
    } else {
        cout << "站点名称：" << list.data[index].name << endl;
        cout << "站点序号：" << index + 1 << endl;
        cout << "与前一站距离：" << list.data[index].distance << endl;
    }
}

// 输出从 start 到 end 的站点
void showPath(SeqList &list, int start, int end) {
    for (int i = start; i <= end; i++) {
        cout << list.data[i].name;
        if (i < end) cout << " -> ";
    }
    cout << endl;
}

// 提高功能：查询从第一条线路换乘到第二条线路的方案
void transfer(SeqList &a, SeqList &b) {
    string startName, endName;

    cout << "请输入出发站（第一条线路）：";
    cin >> startName;
    cout << "请输入目的站（第二条线路）：";
    cin >> endName;

    int start = findStation(a, startName);
    int end = findStation(b, endName);
    //起始位置对应下标
    //a线路中找出发站 b线路中找目的站
    if (start == -1 || end == -1) {
        cout << "出发站或目的站不在线路中！" << endl;
        return;
    }

    // 查找满足行驶方向的公共站点
    for (int i = start + 1; i < a.length; i++) {
        for (int j = 0; j < end; j++) {
            //遍历两条线路，比较站点名称，找出两条线路共有的站点
            if (a.data[i].name == b.data[j].name) {
                cout << "\n推荐换乘方案:" << endl;
                cout << "第一段:乘坐线路1" << endl;
                showPath(a, start, i);

                cout << "在 " << a.data[i].name
                     << " 站换乘线路2。" << endl;

                cout << "第二段:乘坐线路2" << endl;
                showPath(b, j, end);
                return;
            }
        }
    }
    cout << "没有找到符合当前行驶方向的换乘方案！" << endl;
}

int main() {
    SeqList bus1, bus2;
    //初始化顺序表
    initList(bus1);
    initList(bus2);

    //inserStation插入站点信息
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
        //进入循环后 先展示菜单 让用户选择需要执行的功能
        cout << "\n===== 公交线路管理（顺序表）=====" << endl;
        cout << "1.显示线路  2.添加站点  3.删除站点" << endl;
        cout << "4.修改站点  5.查询站点  6.换乘查询" << endl;
        cout << "0.退出程序" << endl;
        cout << "请选择操作：";
        cin >> choice;
        //用户输入choice对应的选项 选择需要执行的功能

        //下面这段代码的作用是先判断当前操作是否需要选择公交线路
        //如果需要，就让用户选择线路 1 或线路 2
        //最后通过指针 bus 指向用户选中的线路
        if (choice >= 1 && choice <= 5) {
            cout << "请选择线路(1 或 2):";
            cin >> line;
            if (line != 1 && line != 2) {
                cout << "线路编号错误！" << endl;
                continue;
            }
        }
        SeqList *bus = (line == 2) ? &bus2 : &bus1;
        //定义一个指针bus 指向公交线路1 2
        //使用指针则后面的增删改查直接修改原来的线路数据
        //而不是简单的复制

        switch (choice) {
            case 1:
                showList(*bus);
                break;
            case 2:
                cout << "输入插入位置、站点名称、与前一站距离：";
                cin >> pos >> name >> distance;
                insertStation(*bus, pos, name, distance);
                break;
            case 3:
                cout << "输入要删除的站点名称：";
                cin >> name;
                deleteStation(*bus, name);
                break;
            case 4:
                cout << "输入原站点名称、新名称、与前一站距离：";
                cin >> name >> newName >> distance;
                updateStation(*bus, name, newName, distance);
                break;
            case 5:
                cout << "输入要查询的站点名称：";
                cin >> name;
                queryStation(*bus, name);
                break;
            case 6:
                transfer(bus1, bus2);
                break;
            case 0:
                cout << "程序结束！" << endl;
                break;
            default:
                cout << "输入错误，请重新选择！" << endl;
        }
    } while (choice != 0);

    return 0;
}

// chcp 936
// g++ -finput-charset=UTF-8 -fexec-charset=GBK ThreadedList.cpp -o ThreadedList.exe
//.\SequenceList2.exe