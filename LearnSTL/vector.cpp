#include <iostream>
#include <vector>

using namespace std;

// vector用于容纳不定长的线性序列，它的底层实现是一个动态数组.
// 当vector的容量不足以容纳新元素时，它会自动扩展容量，通常是将当前容量翻倍，以减少频繁扩展的次数.
// vector提供了丰富的成员函数来操作元素，如push_back()、pop_back()、size()、capacity()等，使得我们可以方便地添加、删除和访问元素.
// vector还支持迭代器，使得我们可以使用范围for循环或标准算法来遍历和操作元素.

// 迭代器是一种对象，它提供了一种访问容器中元素的方式，而不需要暴露容器的底层结构. 它可以看作是指向容器中元素的指针，可以通过迭代器来访问和操作容器中的元素. 迭代器支持各种操作，如递增、递减、解引用等，使得我们可以方便地遍历和修改容器中的元素. 迭代器是STL（标准模板库）中非常重要的概念，它使得我们可以使用统一的方式来处理不同类型的容器.

int main()
{
    vector<int> v;              // 创建一个空的vector，语法是vector<元素类型> 变量名;
    v.insert(v.begin(), 1);     // 在vector的开头插入元素1，语法是insert(迭代器位置, 元素值);
    v.insert(v.begin(), 2);     // 在vector的开头插入元素2
    v.insert(v.end(), 3);       // 在vector的末尾插入元素3
    v.push_back(4);             // 在vector的末尾添加元素4，语法是push_back(元素值);
    v.insert(v.begin() + 3, 5); // 在索引为3的位置插入元素5
    v.erase(v.begin() + 1);     // 删除索引为1的元素
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " "; // 输出vector中的元素
    }
    cout << endl;
    cout << v.size() << endl;     // 输出vector当前的储量
    cout << v.max_size() << endl; // 输出vector的最大容量
    cout << v.capacity() << endl; // 输出vector当前的容量
    return 0;
}