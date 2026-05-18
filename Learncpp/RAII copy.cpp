#include <cstddef> // 包含C++标准库头文件，提供size_t类型的定义
#include <iostream>
using namespace std;

class Screen
{
private:
    int i;
    Screen *next; // 指向下一个Screen对象的指针，用于构建一个链表来管理空闲的Screen对象。
    // 但是，这种设计会多占用一些内存空间，因为每个Screen对象都需要一个指针来链接到下一个对象。这可能会导致内存浪费，尤其是当Screen对象的数量较多时。此外，这种设计也增加了代码的复杂性，因为我们需要管理链表的结构和维护链表的正确性。
    static Screen *freeStore; // 静态成员变量freeStore，一个指向Screen类型的指针，用于管理空闲的Screen对象链表。
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

void *Screen::operator new(size_t size)
{
    Screen *p;
    if (freeStore == nullptr)
    {
        // 如果freeStore为空，表示没有空闲对象可用，我们需要分配新的对象。
        size_t chunk = screenChunk * size;
        // 计算一次性分配的内存大小，等于screenChunk个Screen对象的大小。
        freeStore = p = reinterpret_cast<Screen *>(new char[chunk]);
        // 使用new char[]来分配一块连续的内存，大小为chunk字节，并将返回的指针转换为Screen类型的指针，赋值给freeStore和p。

        // 将分配的内存划分为screenChunk个Screen对象，并将它们链接成一个链表，以便下次分配时可以快速地从链表中取出一个对象。
        for (; p != &freeStore[screenChunk - 1]; ++p)
            p->next = p + 1; // 将分配的对象链接成一个链表，每个对象的next指针指向下一个对象。
        p->next = nullptr;   // 最后一个对象的next指针设置为nullptr，表示链表的末尾。
    }
    p = freeStore;               // 从freeStore中取出一个对象，赋值给p。
    freeStore = freeStore->next; // 更新freeStore指向下一个空闲对象。
    return p;                    // 返回分配的对象的地址。
}

void Screen::operator delete(void *p, size_t)
{
    // 将释放的对象添加到freeStore链表中，以便下次分配时可以重用这个对象。
    Screen *temp = static_cast<Screen *>(p); // 将传入的指针转换为Screen类型的指针，赋值给temp。
    temp->next = freeStore;                  // 将temp的next指针指向当前的freeStore，形成链表。
    freeStore = temp;                        // 更新freeStore指向temp，表示temp现在是链表的头部。
}

int main()
{
    cout << "sizeof(Screen) = " << sizeof(Screen) << endl; // 输出Screen类的大小，单位为字节。
    size_t const N = 100;
    Screen *p[N]; // 定义一个Screen类型的指针数组p，大小为N，用于存储分配的Screen对象的地址。
    for (size_t i = 0; i < N; ++i)
        p[i] = new Screen(i); // 使用new运算符分配N个Screen对象，并将它们的地址存储在指针数组p中。
    for (size_t i = 0; i < N; ++i)
        cout << p[i] << " "; // 输出分配的Screen对象的地址，单位为字节。查看一下分配的对象是否连续，以及freeStore链表的结构。
    for (size_t i = 0; i < N; ++i)
        delete p[i]; // 使用delete运算符释放之前分配的Screen对象，确保资源在对象生命周期内被正确管理和释放。
    return 0;
}
