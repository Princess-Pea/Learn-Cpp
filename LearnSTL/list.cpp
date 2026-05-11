#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<double> l;             // 创建一个空的list，语法是list<元素类型> 变量名;
    l.push_front(1.1);          // 在list的末尾添加元素1，语法是push_back(元素值);
    l.push_back(2.2);           // 在list的末尾添加元素2
    l.push_front(3.3);          // 在list的开头添加元素3，语法是push_front(元素值);
    l.push_front(4.4);          // 在list的开头添加元素4
    l.insert(++l.begin(), 5.5); // 在索引为1的位置插入元素5
    l.erase(++l.begin());       // 删除索引为1的元素

    list<double>::iterator i; // 定义一个list的迭代器，语法是list<元素类型>::iterator 变量名;

    for (i = l.begin(); i != l.end(); i++)
    {
        cout << *i << " "; // 输出list中的元素
    }

    l.sort(); // 对list中的元素进行排序，语法是sort();

    for (i = l.begin(); i != l.end(); i++)
    {
        cout << *i << " "; // 输出list中的元素
    }

    return 0;
}