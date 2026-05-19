#include <cstddef> // 包含C++标准库头文件，提供size_t类型的定义
#include <iostream>
using namespace std;

namespace Ator1
{

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

    void test()
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
    }
}

namespace Ator2
{
    class Airplane
    {
    private:
        struct AirplaneRep
        {
            unsigned long miles;
            char type;
        };

        union
        {
            AirplaneRep rep;
            Airplane *next;
        };
        // 利用 union 实现一个embodded pointer，节省内存空间。
        // 在同一时间内，Airplane对象要么存储AirplaneRep数据，要么存储指向下一个空闲对象的指针，所以我们可以使用union来共享这两种数据结构的内存空间，从而减少每个Airplane对象的内存占用。

        static const int BLOCK_SIZE;     // 定义一个静态常量成员变量BLOCK_SIZE，表示每次分配的Airplane对象数量。
        static Airplane *headOfFreeList; // 定义一个静态成员变量headOfFreeList，一个指向Airplane类型的指针，用于管理空闲的Airplane对象链表。

    public:
        unsigned long getMiles() const { return rep.miles; }
        char getType() const { return rep.type; }
        void set(unsigned long m, char t)
        {
            rep.miles = m;
            rep.type = t;
        }

        static void *operator new(size_t size);
        static void operator delete(void *deadObject, size_t size);
    };

    const int Airplane::BLOCK_SIZE = 512;
    Airplane *Airplane::headOfFreeList = nullptr;

    void *Airplane::operator new(size_t size)
    {
        // 如果请求的大小不等于Airplane对象的大小，调用全局的operator new来分配内存。
        if (size != sizeof(Airplane))
            return ::operator new(size);

        Airplane *p = headOfFreeList;
        if (p)
            headOfFreeList = p->next; // headOfFreeList不是空指针，说明有空闲对象，遂直接把list的头节点更新为下一个空闲对象。
        else
        {
            // 如果空闲链表为空，需分配一块新的内存来存储BLOCK_SIZE个Airplane对象，并将它们链接成一个链表。
            Airplane *newBlock = reinterpret_cast<Airplane *>(::operator new(BLOCK_SIZE * sizeof(Airplane)));

            for (int i = 1; i < BLOCK_SIZE - 1; ++i) // 跳过第一个对象，因为它将被返回给调用者去使用。
                newBlock[i].next = &newBlock[i + 1];
            newBlock[BLOCK_SIZE - 1].next = nullptr;
            p = newBlock;
            headOfFreeList = &newBlock[1]; // 更新headOfFreeList指向新分配的内存块中未使用的第二个对象。
        }
        return p;
    }

    void Airplane::operator delete(void *deadObject, size_t size)
    {
        // 如果传入的指针为nullptr，直接返回，不进行任何操作。（因为释放一个空指针是安全的）
        if (deadObject == nullptr)
            return;
        // 如果请求的大小不等于Airplane对象的大小，调用全局的operator delete来释放内存。
        if (size != sizeof(Airplane))
        {
            ::operator delete(deadObject);
            return;
        }

        Airplane *carcass = static_cast<Airplane *>(deadObject);
        carcass->next = headOfFreeList; // 将释放的对象添加到空闲链表的头部，以便下次分配时可以重用这个对象。
        headOfFreeList = carcass;       // 更新headOfFreeList指向刚刚释放的对象。
    }

    void test()
    {
        cout << "sizeof(Airplane) = " << sizeof(Airplane) << endl; // 输出Airplane类的大小，单位为字节。
        size_t const N = 100;
        Airplane *p[N]; // 定义一个Airplane类型的指针数组p，大小为N，用于存储分配的Airplane对象的地址。
        for (size_t i = 0; i < N; ++i)
            p[i] = new Airplane; // 使用new运算符分配N个Airplane对象，并将它们的地址存储在指针数组p中。
        p[1]->set(1000, 'A');    // 设置p[1]对象的miles为1000，type为'A'。
        p[5]->set(2000, 'B');    // 设置p[5]对象的miles为2000，type为'B'。
        p[9]->set(500000, 'C');  // 设置p[9]对象的miles为3000，type为'C'。
        for (size_t i = 0; i < 10; ++i)
            cout << p[i] << endl; // 输出分配的Airplane对象的地址，单位为字节。
        for (size_t i = 0; i < N; ++i)
            delete p[i]; // 使用delete运算符释放之前分配的Airplane对象，确保资源在对象生命周期内被正确管理和释放。
    }
}

namespace Ator3
{
    class allocator // static allocator class, which can be used by multiple classes to manage memory allocation and deallocation.
    {
    private:
        struct obj
        {
            struct obj *next; // embodded pointer
        };

    public:
        void *allocate(size_t);
        void deallocate(void *, size_t);

    private:
        obj *freeStore = nullptr;
        static const int chunk = 5;
    };

    void *allocator::allocate(size_t size)
    {
        if (size != sizeof(obj))
            return ::operator new(size);

        obj *p;
        if (!freeStore)
        {
            // 没有空闲对象，分配一块新的内存来存储chunk个obj对象，并将它们链接成一个链表。
            size_t chunkSize = chunk * size;
            freeStore = p = (obj *)malloc(chunkSize);
            for (int i = 0; i < chunk - 1; ++i)
            {
                p->next = (obj *)((char *)p + size);
                p = (p->next);
            }
            p->next = nullptr;
        }
        p = freeStore;               // 从freeStore中取出一个对象，赋值给p。
        freeStore = freeStore->next; // 更新freeStore指向下一个空闲对象。
        return p;                    // 返回分配的对象的地址。
    }

    void allocator::deallocate(void *ptr, size_t size)
    {
        ((obj *)ptr)->next = freeStore;
        freeStore = (obj *)ptr;
    }

#define DECLARE_POOL_ALLOC()                            \
public:                                                 \
    static void *operator new(size_t size)              \
    {                                                   \
        return myAlloc.allocate(size);                  \
    }                                                   \
    static void operator delete(void *ptr, size_t size) \
    {                                                   \
        myAlloc.deallocate(ptr, size);                  \
    }                                                   \
                                                        \
protected:                                              \
    inline static allocator myAlloc; // C++17 类内定义

#define IMPLEMENT_POOL_ALLOC(class_name) \
    allocator class_name::myAlloc;

    class Foo
    {
    public:
        long L;
        string str;
        inline static allocator myAlloc; // 可以用inline直接在类内声明并初始化静态成员变量myAlloc，无需在类外定义和初始化。

    public:
        Foo(long l) : L(l) {}
        static void *operator new(size_t size)
        {
            return myAlloc.allocate(size);
        }
        static void operator delete(void *pdead, size_t size)
        {
            myAlloc.deallocate(pdead, size);
        }
    };
    // allocator Foo::myAlloc;

    class Goo
    {
    public:
        double D;
        string str;

        Goo(double d) : D(d) {}

        DECLARE_POOL_ALLOC() // 宏
    };

    class Hoo
    {
    public:
        Hoo() = default;
        Hoo(const Hoo &) = delete;
        Hoo &operator=(const Hoo &) = delete;
        ~Hoo() = default;
    };

    void test()
    {
        Foo *f[100];
        Goo *g[100];

        for (int i = 0; i < 30; ++i)
        {
            f[i] = new Foo(i);
            cout << f[i] << " " << f[i]->L << endl;
        }
        for (int i = 0; i < 30; ++i)
        {
            g[i] = new Goo(i * 0.1);
            cout << g[i] << " " << g[i]->D << endl;
        }
        for (int i = 0; i < 30; ++i)
        {
            delete f[i];
            delete g[i];
        }
    }

    void main()
    {
        Hoo a;
        //! Hoo c = a; // [error] use of deleted function 'Hoo::Hoo(const Hoo&)'
    }
}

#include <new>
#include <iostream>
#include <cassert>

namespace RAII
{
    void noMoreMemory()
    {
        cerr << "Out of memory!" << endl;
        abort();
    }

    void main()
    {
        std::set_new_handler(noMoreMemory);
        // new handler，设置当new操作无法分配内存时调用的函数
        // 要真正发挥作用，new_handler 应该尝试释放可回收的内存（例如清空缓存、释放不用的资源），然后返回，让 operator new 再次尝试分配内存；若未果，则应该抛出 std::bad_alloc 异常，或者调用 std::abort() 来终止程序。
        int *p = new int[1000000000000];
        assert(p != nullptr);
        // p = new int[1000000000000000000];
        // assert(p != nullptr);
    }
}

int main()
{
    // Ator1::test();
    // Ator2::test();
    // Ator3::test();
    RAII::main();
    return 0;
}
