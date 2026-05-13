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

int main()
{
    int ia[5] = {1, 2, 3, 4, 5}; // 定义一个包含5个整数的数组ia，并初始化为1到5
    vector<int> vi(ia, ia + 5);  // 这是什么？
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
}
