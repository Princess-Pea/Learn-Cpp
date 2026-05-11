#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <cmath>
#include "Point.h"
#include "Person.h"
#include "Stu.h"
#include "Shape.h"
#include "Complex.h"

using namespace std;

// int maxab;
// int &maxRef(int x, int y)
// {
//     maxab = (x > y) ? x : y;
//     return maxab;
// }

void fun(Point &point)
{
    point.set1(10, 10);
    point.show();
}

void fun(Point *point)
{
    point->set1(10, 10);
    point->show();
}

class Square
{
private:
    Point p1, p2;

public:
    Square(int x1, int y1, int x2, int y2) : p1(x1, y1), p2(x2, y2)
    {
    }
};

double distance(const Point &p1, const Point &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/*
class Student
{
public:
    static int count;
    static double total;
    Student()
    {
    }
    Student(double score)
    {
        this->score = score;
        count++;
        total += score;
    }
    static double average()
    {
        return total / count;
    }

private:
    double score;
};

int Student::count = 0;
double Student::total = 0.0;
*/

int main()
{
    // Complex z1(1, 2);
    // z1.show();
    // Complex z3;
    // z3 = z1 - 2; // 隐式调用
    // // 显式调用，即函数性的本质：z3 = operator-(z1, z1);
    // z3 = z1 + z3;
    // z3.show();
    // cout << (z1 == z3) << endl;
    Complex z1;
    cin >> z1;
    Complex z2;
    z2 = z1++;
    cout << z2 << endl;
    cout << (z1 == z2);

    // // Shape s1, s2(2, 2);
    // // s1 = s2;
    // // s1.show();
    // // Shape *s3 = &s2;
    // // s3->show();
    // Circle O(1, 1, 1);
    // // s1 = O;
    // // s1.show();
    // Shape *O1 = &O;
    // O1->show();
    // O1->Area(); // 运行时多态 (1)符合继承赋值 (2)指针或引用
    // // Shape &s5 = s2;
    // // s5.show();
    // Shape &s6 = O;
    // s6.Area();
    // Shape *p = new Circle;
    // delete p;

    // Student s("Mao", 10, 4, 2025, 9, 1);
    // s.showStudent();
    // StuhasJob man("Jack", "Barber", "2018");
    // man.show();

    // Point p1(0, 0), p2(1, 1);
    // const Point p(0, 0); // 常对象，必须声明时初始化
    // p.show();            // 常对象必须用常成员函数
    // cout << distance(p1, p2) << endl;
    // Student s[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    // cout << Student::count << endl;
    // cout << Student::total << endl;
    // cout << Student::average() << endl;
    // Point A(0, 0);
    // fun(A);
    // A.show();
    // (A.fun1()).show();
    // A.show();
    // Point B(A);
    // Point C = A;
    // Point B;
    // B.show();

    // Point *p = new Point(1, 1);
    // delete p;

    //  malloc 只划出一块空间,它不会调用构造函数，因此 pA->x 和 pA->y 里的值是“随机垃圾值” ，并且 malloc 申请的内存空间必须用 free 释放
    // Point *pA = (Point *)malloc(sizeof(Point));

    // new 可以自动调用 Point 类的构造函数。这意味着 x 和 y 能被正确初始化。 其申请的内存空间必须用 delete 释放
    // Point *ptrA = new Point;

    // inline 空间换时间（不开新栈） 但只能先定义后使用，且不能是递归函数
}

// 类：具有相同属性和方法的一类对象集合，包括数据抽象（数据成员）和行为抽象（成员函数）
// 定义类的过程就是进行抽象化和封装的过程

// class Point
// {
// private:
//     int x, y;

// public:
//     void set1(int a, int b)
//     {
//         x = a;
//         y = b;
//     }
//     void show();
// };

// int main()
// {
//     Point p1; // 声明Point类的对象p1
//     Point p[3];
//     for (int i = 0; i < 3; i++)
//     {
//         p[i].set1(i, i + 1);
//         p[i].show();
//     }
//     Point *point_p1 = &p1;
//     point_p1->set1(2, 2);
//     point_p1->show();
//     Point &rp = p1;
//     p1.set1(1, 1);
//     p1.show();
// }

// inline void Point::show()
// {
//     cout << "(" << x << "," << y << ")" << endl;
// }

// class circle
// {
//     double radius;

// public:
//     void set(double r);
//     double Area();
// };

// inline void circle::set(double r)
// {
//     radius = r;
// }

// inline double circle::Area()
// {
//     return radius * radius * 3.1416;
// }

// int main()
// {
//     circle O;
//     O.set(1.0);
//     cout << O.Area();
// }

// 类结构常被分为两部分：类的界面和类的实现

//------------------------------------
// int Max(int x, int y)
// {
//     return x > y ? x : y;
// }
// // 传值调用，当不需改变实参的值时使用

// void Swap(int &x, int &y)
// {
//     int temp = x;
//     x = y;
//     y = x;
// }
// // 传引用调用，函数里面操作的就是实参

// int main()
// {
//     // 整数的二进制表示方法有三种：原码、反码和补码
//     // 有符号整数的原码、反码和补码二进制表示中均由符号位与数值位两部分组成。在2进制序列中，最高1位被当做符号位，剩余的都是符号位
//     // 无符号整数、正整数的原码、反码和补码都相同，且为原码
//     // 对于（有符号）负整数：
//     // 反码是将原码的符号位不变，数值位依次取反所得
//     // 补码在反码的基础上+1
//     int a = 10;
//     // 00000000 00000000 00000000 00001010 -- 原码、反码和补码

//     int b = -10;
//     // 10000000 00000000 00000000 00001010 -- 原码
//     // 11111111 11111111 11111111 11110101 -- 反码
//     // 11111111 11111111 11111111 11110110 -- 补码

//     int num = -9;
//     int n = num >> 1; // num的值不会变
//     cout << n;
// }

// int a = 0, b = 0;
// cin >> a >> b;
// int m = Max(a, b);
// cout << m << endl;
// Swap(a, b);
// cout << a << endl;
// void set_arr(int arr[], int sz)
// {
//     for (int i = 0; i < sz; i++)
//     {
//         arr[i] = -1;
//     }
// }
// void print_arr(int arr[], int sz)
// {
//     for (int i = 0; i < sz; i++)
//     {
//         cout << arr[i] << " ";
//     }
// }
// // **数组传参**的特殊性：形参操作的数组和实参是同一数组
// int main()
// {
//     int arr[10] = {0};
//     set_arr(arr, 10);
//     print_arr(arr, 10);
// }

// int x;
// cin >> x;
// string s = to_string(x);

// string s;
// cin >> s;
// int t1 = clock();
// for (string::iterator i = s.begin(); i < s.end(); i++)
// {
//     int j = *i - '0';
//     if (j % 2 == 0)
//         *i = '0';
//     else
//         *i = '1';
// }

// int x = stol(s);
// int t2 = clock();
// cout << x << endl;
// cout << t2 - t1 << endl;

// return 0;

//    ios::sync_with_stdio(false);
//    cin.tie(0);

// string s = to_string(3.14);
// cout << s << endl;
// return 0;
// string s1("113You are bad.");
// size_t pos = 0;
// int i = stoi(s1, &pos, 8);
// cout << i << endl;

// string s2("I'm good. ");
// string::iterator i = s1.begin();
// s1.push_back('.');

// for (i = s1.end(); i >= s1.begin(); i--)
// {
//     cout << *i;
// }
// s1.pop_back();
// cout << s1 + s2 << endl;
// int i;
// s1.insert(5, 2, 'x');
// i = s1.find("x", 10);
// cout << s1 << endl;
// cout << i << endl;
// if (i == string::npos)
//     cout << "failed" << endl;
// return 0;