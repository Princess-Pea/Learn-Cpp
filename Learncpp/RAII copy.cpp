#include <cstddef> // 包含C++标准库头文件，提供size_t类型的定义
#include <iostream>
using namespace std;

class Screen
{
private:
    int i;
    Screen *next;
    static Screen *freeStore;
    // 静态成员变量freeStore，一个指向Screen类型的指针，用于管理空闲的Screen对象链表。
    // 当我们需要分配一个新的Screen对象时，我们首先检查freeStore是否有可用的对象，如果有，我们就从freeStore中取出一个对象并返回；如果没有，我们就使用malloc来分配一个新的Screen对象，并返回它的地址。当我们释放一个Screen对象时，我们将它添加到freeStore链表中，以便下次分配时可以重用这个对象。这种内存管理方式可以提高性能，减少内存碎片，并且符合RAII原则，确保资源在对象生命周期内被正确管理和释放。
    static const int screenChunk;
    // 静态常量成员变量screenChunk，一个整数常量，表示每次分配的Screen对象数量。
    // 当我们需要分配新的Screen对象时，我们会一次性分配screenChunk个对象，并将它们链接成一个链表，以便下次分配时可以快速地从链表中取出一个对象。这种批量分配的方式可以提高性能，减少内存碎片，并且符合RAII原则，确保资源在对象生命周期内被正确管理和释放。

public:
    Screen(int x) : i(x) {};
    int get() { return i; }

    void *operator new(size_t size);
    void operator delete(void *, size_t);
};

Screen *Screen::freeStore = nullptr; // 定义并初始化静态成员变量freeStore，初始值为nullptr，表示没有空闲对象可用。
const int Screen::screenChunk = 24;  // 定义并初始化静态常量，初始值为24，表示每次分配24个Screen对象。
