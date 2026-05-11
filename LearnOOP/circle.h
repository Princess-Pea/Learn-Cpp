#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>

class circle
{
    double radius;

public:
    void set(double r);
    double Area();
};

inline void circle::set(double r)
{
    radius = r;
}

inline double circle::Area()
{
    return radius * radius * 3.1416;
}