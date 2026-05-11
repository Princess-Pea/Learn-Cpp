class Point
{
private:
    int x, y;
    int &rx = x;
    const float pi = 3.14;
    friend double distance(const Point &p1, const Point &p2);

public:
    void set1(int a, int b);
    void show() const;
    // 构造函数
    Point();
    Point(int a, int b);
    ~Point();
    Point(const Point &p);
    Point &fun1();
};