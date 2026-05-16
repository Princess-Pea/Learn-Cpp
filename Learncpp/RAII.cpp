#include <cstdlib>              // 包含C标准库头文件，提供malloc和free函数的声明
#include <complex>              // 包含C++标准库头文件，提供complex类模板的声明
#include <ext/pool_allocator.h> // 包含GNU C++库中的pool_allocator类模板的声明
#include <iostream>

using namespace std;

template <typename T>
class Complex
{
public:
    T real, imag;
    Complex(T r, T i) : real(r), imag(i) {}
};

class A
{
public:
    int id;
    A() : id(0) { cout << "default ctor.this = " << this << "id = " << id << endl; }
    A(int i) : id(i) { cout << "ctor.this = " << this << "id = " << id << endl; }
    ~A() { cout << "dtor.this = " << this << "id = " << id << endl; }
};

namespace RAII1
{
    void test()
    {
        // 这段代码演示了C++中的RAII（资源获取即初始化）原则。RAII是一种编程习惯，确保资源在对象的生命周期内被正确管理和释放。
        // 在这个例子中，我们使用malloc和free来分配和释放内存，使用new和delete来分配和释放对象，以及使用全局命名空间中的operator new和operator delete来分配和释放内存。这些操作都遵循RAII原则，确保资源在不再需要时被正确释放，避免内存泄漏和其他资源管理问题。

        void *p1 = malloc(512);
        free(p1);
        // 这里使用了C标准库中的malloc函数来分配512字节的内存，并将返回的指针存储在p1中。然后使用free函数来释放之前分配的内存。

        complex<int> *p2 = new complex<int>;
        delete p2;
        // 这里使用了C++标准库中的new运算符来分配一个complex<int>对象，并将返回的指针存储在p2中。然后使用delete运算符来释放之前分配的对象。

        Complex<double> *pc = new Complex<double>(1.0, 2.0);
        // 编译器会转为：
        // Complex<double> *pc; 这是定义一个指向Complex<double>类型的指针pc。
        // try
        // {
        //     void *mem = operator new(sizeof(Complex<double>));
        //     使用全局命名空间中的operator new来分配足够大小的内存来存储一个Complex<double>对象，并将返回的指针存储在mem中。
        //     pc = static_cast<Complex<double> *>(mem);
        //     将分配的内存转换为Complex<double>类型的指针，并赋值给pc。
        //     pc->Complex<double>::Complex(1.0, 2.0);
        //     调用Complex<double>类的构造函数来初始化pc指向的对象，传入实部1.0和虚部2.0作为参数。
        // }
        // catch (std::bad_alloc){
        // 处理内存分配失败的情况，例如输出错误信息或终止程序
        // }
        delete pc;
        // 编译器会转为：
        // pc->~Complex<double>();
        // 调用pc指向的对象的析构函数来销毁对象，释放对象占用的资源。
        // operator delete(pc);
        // 使用全局命名空间中的operator delete来释放之前分配的内存，传入pc作为参数。
        // 析构函数的调用和内存的释放是分开的，这也是C++中RAII原则的一部分，确保资源在对象生命周期结束时被正确管理和释放。

        void *p3 = ::operator new(512);
        ::operator delete(p3);
        // 这里使用了全局命名空间中的operator new和operator delete来分配和释放内存，本质上调用的就是malloc和free函数，与前面使用malloc和free的效果相同，但更符合C++的风格和习惯。

        // 下面的代码演示了在Borland C++和GNU C++编译器中，allocator类的使用。
        // 实际上，现在很少使用allocator类来直接管理内存，因为C++标准库中的容器已经使用了allocator来管理内存，并且提供了更高层次的接口来操作容器中的元素。当然，在某些特殊情况下，可能确实需要直接使用allocator来分配和释放内存。
#ifdef __BORLANDC__

        // 以下两个函数都是 non-static 成员函数，必须通过 object 来调用。
        int *p4 = allocator<int>().allocate(5);
        allocator<int>().deallocate(p4, 5);

#endif

#ifdef __GNUC__

        // 以下两个函数都是 non-static 成员函数，必须通过 object 来调用。
        int *p4 = allocator<int>().allocate(7);
        allocator<int>().deallocate((int *)p4, 7);

        void *p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
        __gnu_cxx::__pool_alloc<int>().deallocate((int *)p5, 9);

#endif
    }
}

namespace RAII2
{
    void test_basic_string()
    {
        string *pstr = new string;
        cout << "pstr = " << *pstr << endl;
        //! pstr->string::string("Hello, World!"); //[error] class std::basic_string<char> has no member named 'string'
        //! pstr->~string(); // crash, double free or corruption (out)
        cout << "pstr = " << *pstr << endl;
    }

    void test_class_A()
    {
        A *pA = new A(1);
        cout << pA->id << endl;
        //! pA->A::A(3); // [error] cannot call constructor 'A::A' directly
        delete pA;
    }
}

namespace RAII3
{
    void test_complex_array()
    {
        complex<int> *pca = new complex<int>[3];
        // 这将调用三次ctor来构造三个complex<int>对象，并返回指向第一个对象的指针。
        //! delete pca;
        // 这将调用一次dtor来销毁第一个complex<int>对象，并释放分配的内存。
        // 这是不当的，因为我们应该使用delete[]来销毁数组中的所有对象并释放内存。正确的代码应该是：
        delete[] pca;
        // 这将调用三次dtor来销毁数组中的三个complex<int>对象，并释放分配的内存。
    }

    void test_A_array(int size)
    {
        A *buf = new A[size];
        // 这要求A类必须具有默认构造函数，因为new[]运算符需要调用默认构造函数来构造数组中的每个对象。
        A *tmp = buf; // 这里我们将buf指针保存到tmp中，因为我们需要在delete[]之后访问对象的成员变量。
        cout << "buf = " << buf << endl;
        cout << "tmp = " << tmp << endl;
        for (int i = 0; i < size; ++i)
            new (tmp++) A(i);
        cout << "buf = " << buf << endl;
        cout << "tmp = " << tmp << endl;
        delete[] buf;
    }
}

namespace RAII4
{
    void test()
    {
        int *pi = new int[10]; // from heap, not from stack
        // cookie是编译器在分配内存时添加的一些额外信息，用于记录分配的内存块的大小和其他相关信息。当我们使用new[] 运算符分配一个数组时，编译器会在分配的内存块前面添加一个cookie来记录数组的大小，以便在调用delete[] 运算符时能够正确地销毁数组中的每个对象并释放内存。
        delete pi;
        // 对于平凡类型（如 int），内存块可能仍被完整释放（取决于具体实现，因为 delete 和 delete[] 最终都调用 free，而 free 不需要知道元素个数），但对于非平凡类型（如类对象），这将导致未定义行为，因为 delete 只会调用第一个对象的析构函数，而不会正确地销毁数组中的每个对象，也不会正确地释放内存。
        // 当然，即便对于平凡类型，这仍然是未定义行为。我们应该使用delete[] 来销毁数组中的每个对象并释放内存。

        int ia[10]; // from stack, not from heap
        cout << sizeof(ia);

        // 背后的堆内存块布局：
        // 1.开头标记 61h ：编译器在分配内存块时会在开头添加一个标记，用于标识这是一个由new[]运算符分配的内存块。这有助于在调用delete[]运算符时验证内存块的合法性，防止错误地使用delete来释放new[]分配的内存块。
        // 2.Debugger Header（32 字节）：编译器可能会在内存块中添加一个调试器头部，用于存储调试信息和其他相关数据。这有助于调试器在运行时跟踪内存分配和释放的情况，检测内存泄漏和其他内存相关的问题。
        // 3.数组数据区（10 个 int，40 字节）：这是实际存储数组元素的内存区域。在这个例子中，我们分配了一个包含10个int的数组，因此数据区占用40字节（每个int占4字节）。
        // 4.No man land（保护区域，4 字节）：编译器可能会在数组数据区之后添加一个保护区域，用于检测越界访问和其他内存错误。这有助于在运行时捕获和报告内存相关的问题，增强程序的安全性和稳定性。
        // 5.Pad 对齐填充（12 字节）：编译器可能会在内存块的末尾添加一些填充字节，以确保内存块的总大小是某个特定值（通常是16的倍数）。这有助于提高内存访问的效率和性能，因为许多处理器在访问对齐的内存地址时表现更好。
        // 6.结尾标记 61h：编译器可能会在内存块的末尾添加一个标记，用于标识内存块的结束。这有助于在调用delete[]运算符时验证内存块的完整性，防止错误地使用delete来释放new[]分配的内存块。

        // 如果是自定义的类对象数组，内存块的布局可能会有所不同，因为编译器需要为每个对象调用构造函数和析构函数。当类有非平凡析构函数， new Demo[3] 会在数据区前面额外用一块内存记录数组长度 3，运行时 delete[] 要根据这个长度调用 3 次析构函数；如果类有平凡析构函数，那么 new Demo[3] 就不会记录数组长度，运行时 delete[] 也不会调用析构函数。
    }
}

int main()
{
    RAII1::test();
    RAII2::test_basic_string();
    RAII2::test_class_A();
    RAII3::test_A_array(3);

    return 0;
}
