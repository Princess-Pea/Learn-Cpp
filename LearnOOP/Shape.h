#include <iostream>

using namespace std;

class Shape // 包含有纯虚函数的类是抽象类，不能实例化
{
    int x, y;

public:
    Shape(int xx = 0, int yy = 0) : x(xx), y(yy) // 构造函数不能被声明为虚函数，因为构造函数在调用时，对象还没有完成建立，遑论函数与对象的绑定
    {
    }
    virtual void show()
    {
        cout << "Center at (" << x << "," << y << ")" << endl;
    }
    virtual void Area() = 0; // 纯虚函数
    // {
    //     cout << "ERROR! Cannot calculate area without knowing what shape it is" << endl;
    // }
    virtual ~Shape() // 只要一个类可能会被作为基类（即它有子类），那么它的析构函数就必须声明为 virtual
    {
        cout << "Oops!" << endl;
    }
};

class Circle : public Shape
{
    int radius;

public:
    Circle(int x = 0, int y = 0, int r = 0) : Shape(x, y), radius(r)
    {
    }
    virtual void show()
    {
        cout << "A Circle, ";
        Shape::show();
    }
    virtual void Area()
    {
        cout << "The Area of the Circle is " << 3.14 * radius * radius << endl;
    }
    virtual ~Circle() // 只要一个类可能会被作为基类（即它有子类），那么它的析构函数就必须声明为 virtual
    {
        cout << "Oops!!" << endl;
    }
};