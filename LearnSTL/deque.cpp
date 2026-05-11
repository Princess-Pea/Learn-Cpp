#include <iostream>
#include <deque>

using namespace std;

// deque（double-ended queue）是一种双端队列数据结构，它允许在两端进行插入和删除操作. deque的底层实现通常是一个动态数组或链表，具体取决于实现细节.

// deque提供了丰富的成员函数来操作元素，如push_back()、push_front()、pop_back()、pop_front()、size()、capacity()等，使得我们可以方便地添加、删除和访问元素.

// deque还支持迭代器，使得我们可以使用范围for循环或标准算法来遍历和操作元素.

// deque在需要频繁在两端进行插入和删除操作的场景中非常有用，例如实现队列、栈等数据结构.

int main()
{
    deque<char> d;                // 创建一个空的deque，语法是deque<元素类型> 变量名;
    d.push_back('a');             // 在deque的末尾添加元素'a'，语法是push_back(元素值);
    d.push_back('b');             // 在deque的末尾添加元素'b'
    d.push_front('c');            // 在deque的开头添加元素'c'，语法是push_front(元素值);
    d.push_front('d');            // 在deque的开头添加元素'd'
    d.insert(d.begin() + 2, 'e'); // 在索引为2的位置插入元素'e'
    d.pop_back();                 // 删除deque末尾的元素，语法是pop_back();
    d.pop_front();                // 删除deque开头的元素，语法是pop_front();
    for (int i = 0; i < d.size(); i++)
    {
        cout << d[i] << " "; // 输出deque中的元素
    }
    cout << endl;
    cout << d.size() << endl;     // 输出deque当前的储量
    cout << d.max_size() << endl; // 输出deque的最大容量

    return 0;
}