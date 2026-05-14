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
            try // 使用try-catch块来捕获可能发生的异常，防止程序崩溃
            {
                snprintf(buf, 10, "%d", rand());
                // 生成一个随机数，将其转换为字符串，存储在buf中，最多10个字符，包括终止符\0
                c.push_back(string(buf));
                // 将字符串添加到vector中
            }
            catch (exception &p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                // 如果发生异常，输出当前的索引i和异常信息，然后终止程序
                abort(); // 终止程序的执行，通常用于在发生严重错误时立即退出程序
            }
        }
        clock_t timeEnd = clock();
        cout << "Time taken: " << (timeEnd - timeStart) << endl;
        cout << "size=" << c.size() << endl;
        cout << "front=" << c.front() << endl;
        cout << "back=" << c.back() << endl;
        cout << "data=" << c.data() << endl;
        // data()函数返回一个指向vector内部数组的指针，可以直接访问vector中的元素，但需要注意不要越界访问。
        cout << "capacity=" << c.capacity() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto Item = ::find(c.begin(), c.end(), target);
            // 使用全局命名空间中的find函数，在vector c的范围内查找目标字符串target，返回一个迭代器指向找到的元素，如果没有找到则返回c.end()
            // find函数是C++标准库中的算法，适用于任何容器，使用线性搜索算法，时间复杂度为O(n)。具体来说，find函数会从c.begin()开始逐个比较元素与target是否相等，直到找到匹配的元素或者遍历完整个vector。
            timeEnd = clock();
            if (Item != c.end())
                cout << "Found " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            else
                cout << "Did not find " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
        }
        {
            timeStart = clock();
            sort(c.begin(), c.end());
            string *Item = (string *)bsearch(&target, c.data(), c.size(), sizeof(string), compareStrings);
            timeEnd = clock();
            if (Item != nullptr)
                cout << "Found " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            else
                cout << "Did not find " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
        }
        // find 和 bsearch 都是用来查找元素的函数。
        // find是C++标准库中的算法，适用于任何容器，而bsearch是C标准库中的函数，适用于数组。
        // find使用线性搜索算法，时间复杂度为O(n)，而bsearch使用二分搜索算法，时间复杂度为O(log n)，但需要数组已经排序。
        // 在这个测试中，首先使用find函数在vector中查找目标字符串，记录查找所需的时间，然后使用bsearch函数在排序后的vector中查找目标字符串，记录查找所需的时间，并输出结果。
        // 理论上，bsearch应该比find更快，因为它使用了二分搜索算法。但我们的程序还统计了排序的时间，所以bsearch总的时间会更长，特别是像这样当vector中的元素较多时。
    }
}

#include <list>
namespace stl3
{
    void test_list(long &value)
    {
        cout << "\nTesting list...\n";
        list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try // 使用try-catch块来捕获可能发生的异常，防止程序崩溃
            {
                snprintf(buf, 10, "%d", rand());
                // 生成一个随机数，将其转换为字符串，存储在buf中，最多10个字符，包括终止符\0
                c.push_back(string(buf));
                // 将字符串添加到list中
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
        cout << "max_size=" << c.max_size() << endl;
        cout << "front=" << c.front() << endl;
        cout << "back=" << c.back() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto Item = ::find(c.begin(), c.end(), target);
            timeEnd = clock();
            if (Item != c.end())
                cout << "Found " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            else
                cout << "Did not find " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
        }
        {
            timeStart = clock();
            c.sort();
            // list容器有自己的sort成员函数，可以直接对list进行排序，而不需要像vector那样使用全局的sort算法。
            // 为什么要专门为list提供一个sort成员函数呢？因为list是一个双向链表，使用归并排序算法来排序是非常高效的，而全局的sort算法通常使用快速排序或堆排序，这些算法在链表结构上效率较低。
            timeEnd = clock();
            cout << "Time taken to sort: " << (timeEnd - timeStart) << endl;
        }
    }
}

#include <forward_list>
namespace stl4
{
    void test_forward_list(long &value)
    {
        cout << "\nTesting forward_list...\n";
        forward_list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try // 使用try-catch块来捕获可能发生的异常，防止程序崩溃
            {
                snprintf(buf, 10, "%d", rand());
                // 生成一个随机数，将其转换为字符串，存储在buf中，最多10个字符，包括终止符\0
                c.push_front(string(buf));
                // 将字符串添加到forward_list的前面
                // push_front()函数是forward_list容器特有的成员函数，用于在forward_list的前面插入元素。由于forward_list是一个单向链表，不能像list那样在后面插入元素，所以只能使用push_front()来添加元素。
            }
            catch (exception &p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        clock_t timeEnd = clock();
        cout << "Time taken: " << (timeEnd - timeStart) << endl;
        cout << "max_size=" << c.max_size() << endl;
        cout << "size=" << distance(c.begin(), c.end()) << endl;
        // forward_list没有size()成员函数，但可以使用distance函数来计算元素个数
        cout << "front=" << c.front() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto Item = ::find(c.begin(), c.end(), target);
            timeEnd = clock();
            if (Item != c.end())
                cout << "Found " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            else
                cout << "Did not find " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
        }
    }
}

#include <deque>
namespace stl5
{
    void test_deque(long &value)
    {
        cout << "\nTesting deque...\n";
        deque<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try // 使用try-catch块来捕获可能发生的异常，防止程序崩溃
            {
                snprintf(buf, 10, "%d", rand());
                // 生成一个随机数，将其转换为字符串，存储在buf中，最多10个字符，包括终止符\0
                c.push_back(string(buf));
                // 将字符串添加到deque中
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
        cout << "max_size=" << c.max_size() << endl;
        cout << "front=" << c.front() << endl;
        cout << "back=" << c.back() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto Item = ::find(c.begin(), c.end(), target);
            timeEnd = clock();
            if (Item != c.end())
                cout << "Found " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            else
                cout << "Did not find " << target << " in " << (timeEnd - timeStart) << " ticks.\n";
            timeStart = clock();
            sort(c.begin(), c.end());
            cout << "Time taken to sort: " << (clock() - timeStart) << endl;
        }
    }
}

#include <stack>
namespace stl6
{
    void test_stack(long &value)
    {
        cout << "\nTesting stack...\n";
        stack<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try // 使用try-catch块来捕获可能发生的异常，防止程序崩溃
            {
                snprintf(buf, 10, "%d", rand());
                // 生成一个随机数，将其转换为字符串，存储在buf中，最多10个字符，包括终止符\0
                c.push(string(buf));
                // 将字符串添加到stack中
            }
            catch (exception &p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "Time taken: " << (clock() - timeStart) << endl;
        cout << "size=" << c.size() << endl;
        cout << "top=" << c.top() << endl;
        c.pop();
        cout << "After pop, size=" << c.size() << endl;
        cout << "New top=" << c.top() << endl;
    }
}

#include <ext\slist>
namespace stl10
{
}

int main()
{
    long value = 1000000;           // 要测试的元素个数，可以根据需要修改
    stl2::test_vector(value);       // 调用stl2命名空间中的test_vector函数，并传入value参数
    stl3::test_list(value);         // 调用stl3命名空间中的test_list函数，并传入value参数
    stl4::test_forward_list(value); // 调用stl4命名空间中的test_forward_list函数，并传入value参数
    stl5::test_deque(value);        // 调用stl5命名空间中的test_deque函数，并传入value参数
    stl6::test_stack(value);        // 调用stl6命名空间中的test_stack函数，并传入value参数
    return 0;
}