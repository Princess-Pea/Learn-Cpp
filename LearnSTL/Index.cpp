// 标准库以header files的形式提供

#include <stdio.h>
// 旧式的C语言头文件，提供了输入输出函数，如printf()、scanf()等，有.h后缀
#include <cstdio>
// C++标准库头文件，提供了输入输出函数，如std::printf()、std::scanf()等，没有.h后缀
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
// 新式header files中的函数和对象都封装在std命名空间中，使用using namespace std;可以直接使用std命名空间中的全部函数和对象，而不需要每次都加上std::前缀。
// 旧式的C语言头文件中的函数和对象不在std命名空间中。
using std::cout;
// 也可以单独引入需要的函数或对象，语法是using std::函数名; 或 using std::对象名;

// int main()
//  {
//      int ia[5] = {1, 2, 3, 4, 5};
//      // 定义一个包含5个整数的数组ia，并初始化为1到5
//      vector<int> vi(ia, ia + 5);
//      // 一个vector<int>对象vi，使用数组ia的前5个元素来初始化。ia是数组的首地址，ia + 5是数组的末尾地址。
//      cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 4)));
//      // 使用count_if算法来统计vi中满足条件的元素个数。条件是使用not1和bind2nd组合起来的函数对象，表示不满足小于4的条件，即大于等于4的元素个数。

//     vector<double> vd;
//     for (auto elem : vd) // 使用范围for循环来遍历vd中的元素，每次迭代将当前元素赋值给elem变量
//     {
//         cout << elem << endl;
//     }
//     for (auto &elem : vd) // 使用引用，可以修改vd中的元素
//     {
//         elem *= 2; // 将vd中的每个元素乘以2
//     }

//     array<int, 5> a = {1, 2, 3, 4, 5};
//     int a[5] = {1, 2, 3, 4, 5};
//     // 这两种方式都定义了一个包含5个整数的数组a，并初始化为1到5。第一种方式使用了std::array容器，第二种方式使用了传统的C风格数组。std::array提供了更多的成员函数和安全性，而C风格数组更简单但缺乏一些功能和安全性。
// }

// iterator：迭代器是一种对象，提供了一种访问容器中元素的方式。迭代器可以看作是指向容器中元素的指针，可以通过迭代器来遍历容器中的元素。常见的迭代器类型有输入迭代器、输出迭代器、前向迭代器、双向迭代器和随机访问迭代器等。

long get_a_target_long()
{
    long target = 0;
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string()
{
    long target = 0;
    char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target); // 将target转换为字符串，存储在buf中，最多10个字符，包括终止符\0
    return string(buf);
}

int compareLongs(const void *a, const void *b) // const void* a和const void* b是两个指向常量的void指针，表示要比较的两个元素的地址
{
    return (*(long *)a - *(long *)b); // 将void指针a和b转换为long指针，并返回它们的差值，用于比较两个long值的大小
}

int compareStrings(const void *a, const void *b)
{
    if (*(string *)a < *(string *)b) // 将void指针a和b转换为string指针，并比较它们指向的字符串的大小
        return -1;                   // 如果a指向的字符串小于b指向的字符串，返回-1
    else if (*(string *)a > *(string *)b)
        return 1; // 如果a指向的字符串大于b指向的字符串，返回1
    else
        return 0; // 如果a指向的字符串等于b指向的字符串，返回0
}

#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <algorithm>

namespace stl2
// 定义一个命名空间stl2，包含一个测试vector的函数，这样可以避免与其他命名空间中的函数重名，并且可以更好地组织代码。
// 要运行的话，需要在main函数中调用stl2::test_vector()，并传入一个long类型的参数，表示要测试的元素个数。
{
    void test_vector(long &value)
    {
        cout << "\nTesting vector...\n";
        vector<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch (exception &p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        clock_t timeEnd = clock();
        cout << "Time taken: " << (timeEnd - timeStart) << endl;
        cout << "size=" << c.size() << endl;
        cout << "front=" << c.front() << endl;
        cout << "back=" << c.back() << endl;
        cout << "data=" << c.data() << endl;
        cout << "capacity=" << c.capacity() << endl;
    }
}

// main函数调用stl2::test_vector()函数，并传入一个long类型的参数，表示要测试的元素个数。
// int main()
// {
//     long value = 1000000;     // 要测试的元素个数，可以根据需要修改
//     stl2::test_vector(value); // 调用stl2命名空间中的test_vector函数，并传入value参数
//     return 0;
// }