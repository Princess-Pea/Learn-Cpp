#include <cstdlib>              // 包含C标准库头文件，提供malloc和free函数的声明
#include <complex>              // 包含C++标准库头文件，提供complex类模板的声明
#include <ext/pool_allocator.h> // 包含GNU C++库中的pool_allocator类模板的声明

using namespace std;

template <typename T>
class Complex
{
public:
    T real, imag;
    Complex(T r, T i) : real(r), imag(i) {}
};

int main()
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
