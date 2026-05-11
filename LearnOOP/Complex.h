#include <iostream>

using namespace std;

class Complex
{
private:
    double real; // 实部
    double imag; // 虚部

public:
    // 1. 构造函数：带默认参数，合并了无参构造和有参构造
    Complex(double r = 0, double i = 0) : real(r), imag(i)
    {
        // 使用初始化列表提高效率
    }

    // 2. 显示函数
    void show() const
    {
        if (imag >= 0)
            cout << real << " + " << imag << "i" << endl;
        else
            cout << real << " - " << -imag << "i" << endl; // 处理虚部为负数的情况
    }

    Complex Add(const Complex &z)
    {
        Complex temp;
        temp.real = this->real + z.real;
        temp.imag = imag + z.imag;
        return temp;
    }

    // ============================================================
    // 【练习 1】成员函数重载：实现复数加法 (c1 + c2)
    // 提示：编译器会将 c1 + c2 解释为 c1.operator+(c2)
    // 其中 c1 是 this 指向的对象，c2 是传入的参数
    // ============================================================
    // Complex operator+(const Complex &other)

    // 成员函数，缺点是对称性问题
    Complex operator+(const Complex &z)
    {
        Complex temp = *this;
        temp.real += z.real;
        temp.imag += z.imag;
        return temp;
    }

    Complex operator++() // 前置
    {
        this->real++;
        this->imag++;
        return *this;
    }

    Complex operator++(int) // 后置
    {
        Complex temp = *this; // 用临时对象储存自增前的值
        this->real++;
        this->imag++;
        return temp;
    }

    Complex operator=(const Complex &c)
    {
        this->real = c.real;
        this->imag = c.imag;
        cout << "Hey!" << endl;
        return *this;
    }

    friend Complex operator-(const Complex &c1, const Complex &c2);

    friend bool operator==(const Complex &c1, const Complex &c2)
    {
        if (c1.real == c2.real && c2.imag == c1.imag)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &zout, const Complex &c);
    friend istream &operator>>(istream &zin, Complex &c);
};

// 在类外实现友元重载（注意不需要加 Complex:: 前缀，因为它不是成员）
// 友元函数降低了类的独立性，一定程度上也破坏了类的封装性
// 但友元函数实现方式使得运算符重载的灵活程度更高，因为它支持自动隐式转换
// 输入输出<<和>>运算符**只能通过友元函数方式实现重载**，因标准类(istream类和ostream类)成员函数不能自行添删改
Complex operator-(const Complex &c1, const Complex &c2)
{
    Complex temp;
    temp.real = c1.real - c2.real;
    temp.imag = c1.imag - c2.imag;
    return temp;
}

ostream &operator<<(ostream &zout, const Complex &c)
{
    if (c.imag >= 0)
        cout << c.real << " + " << c.imag << "i";
    else
        cout << c.real << " - " << -c.imag << "i";
    return zout;
}

istream &operator>>(istream &zin, Complex &c) // 注意这里 c 不能用 const
{
    cin >> c.real >> c.imag;
    return zin;
}