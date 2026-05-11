#include "Point.h"
#include <iostream>
// 名字空间namespace,不能在函数或类的内部定义
//  namespace A
//  {
//      int x;
//  }
using namespace std;

Point::Point(int a, int b) : x(a), y(b)
{
}

Point::Point()
{
    cout << "Input x and y" << endl;
    cin >> x >> y;
}

void Point::set1(int a, int b)
{
    x = a;
    y = b;
}

void Point::show() const // “Const Correctness”原则： 只要一个成员函数不需要修改成员变量，就请务必把它声明为 const。
// show(const Point * this) 自动产生的隐含对象指针，不能被显式声明，局部const指针
{
    cout << "(" << x << "," << y << ")" << endl;
    // cout<<this->x<<","<<this->y<<endl;
}

Point::Point(const Point &p)
{
    // 深拷贝：申请了新的内存空间以用于拷贝，这样独立的内存更安全
    x = p.x;
    y = p.y;
    cout << "copying..." << endl;
}

// 析构函数不带返回值，不带参数，不能重载
Point::~Point()
{
    cout << "Oops!" << endl;
}

Point &Point::fun1()
{
    return *this; // 类的方法需要返回当前对象的引用时，考虑this指针
}
