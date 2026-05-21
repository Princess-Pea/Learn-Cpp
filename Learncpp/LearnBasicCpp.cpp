#include <iostream>

#define LOG(x) std::cout << x << std::endl;

namespace pointer
{
	void main()
	{
		int var = 8;
		//int* ptr = &var;
		//double* q = (double*)&var;
		//*ptr = 10;
		//LOG(var);

		char* buffer = new char[8]; // buffer is a pointer pointing to a block of memory of 8 bytes, which is enough to hold 8 chars
		memset(buffer, 0, 8); // fill the memory block with 0s, or '\0' in the case of char

		char** ptr = &buffer;

		delete[] buffer;
		std::cin.get();
	}
}

namespace reference
{
	void Increment(int value)
	{
		value++;
	}

	void Increment_ptr(int* value)
	{
		(*value)++;
	}

	void Increment_ref(int& value)
	{
		value++;
	}

	void main()
	{
		int a = 5;
		Increment(a);
		Increment_ptr(&a);
		Increment_ref(a);

		int b = 8;
		int& ref = a;
		ref = b; // a = b; => a=8,b=8,ref=8.


		//int* b = &a;
		//int& ref = a; // create an alias for a, ref is another name for a, it refers to the same memory location as a
		//ref = 2;

		LOG(a);

		std::cin.get();
	}

}

// extern int s_Variable; // 通过extern关键字声明一个外部变量，告诉编译器这个变量在其他地方定义过了，编译器会去链接阶段找到这个变量的定义并链接到当前文件中。

// extern void Function(); // 通过extern关键字声明一个外部函数

namespace Static
{
	struct Entity
	{
		static int x, y; // 声明static成员变量。它们属于类本身，而不是类的实例，所以在内存中只有一份，不管创建多少个Entity对象，x和y都共享同一份内存。

		static void static_Print() // 声明static成员函数。它们也属于类本身，可以直接通过类名调用，而不需要创建对象。静态成员函数只能访问静态成员变量，不能访问非静态成员变量，因为非静态成员变量属于对象实例，而静态成员函数没有this指针，无法访问对象实例。
		{
			std::cout << x << "," << y << std::endl;
		}

		void Print()
		{
			std::cout << x << "," << y << std::endl;
		}

		// 非静态成员函数，本质上传入了一个隐式的this指针，指向调用该函数的对象实例，所以可以访问非静态成员变量和静态成员变量。

		void Print(Entity* e) // 通过传入一个Entity对象指针来访问静态成员变量。虽然静态成员变量不属于对象实例，但可以通过对象实例来访问它们，因为它们在内存中只有一份，所有对象实例共享同一份内存。
		{
			std::cout << e->x << "," << e->y << std::endl;
		}
	};

	int Entity::x; // 定义static成员变量，必须在类外定义。如未指定初值，静态成员变量会被默认初始化为0。
	int Entity::y;
	
	void main()
	{
		Entity e, e1;
		e.x = 2;
		e.y = 3;

		//! Entity e1 = { 5,8 }; // 默认构造函数，不能用列表初始化来初始化静态成员变量，因为静态成员变量不属于类的实例，而是属于类本身，所以它们不能通过对象来初始化，只能通过类名来初始化。
		e1.x = 5;
		e1.y = 8;

		e.Print();
		e1.Print();
		Entity::static_Print(); // 通过类名调用静态成员函数，静态成员函数直接访问静态成员变量，输出5,8，不依赖于对象实例。
	}
}

namespace local_static
{
	class Singleton
	{
	private:
		static Singleton* s_Instance; // 静态成员变量，属于类本身，在内存中只有一份，所有对象实例共享同一份内存。
	public:
		static Singleton& Get_ref() { return *s_Instance; } // 返回一个引用
		static Singleton* Get_ptr() { return s_Instance; } // 返回一个指针
		static Singleton &Get()
		{
			Singleton instance;
			return instance; // 返回的引用成为悬垂引用，因为变量instance在函数结束时被销毁，后续任何通过该引用访问对象的行为都是未定义行为。
		}
		void Hello() { std::cout << "Hello Singleton!" << std::endl; }
	};

	Singleton* Singleton::s_Instance; // 定义静态成员变量，必须在类外定义。

	void Function()
	{
		static int i = 0; // 局部静态变量，虽然在函数内部定义，但它的生命周期贯穿整个程序运行期间，只有一份内存，不管调用多少次Function函数，s_LocalStatic都共享同一份内存，并且只会被初始化一次。
		// 这种办法主要是在函数内部维护一个状态时，避免使用全局变量，同时又不需要每次调用函数都重新初始化变量。
		std::cout << i << std::endl;
		i++;
	}
	void main()
	{
		//for (int i = 0; i < 5; i++)
			//Function();
		Singleton::Get_ref().Hello();
		Singleton::Get_ptr()->Hello();
		Singleton::Get().Hello();
	}
}

namespace Ctor_Dtor
{
	class Entity
	{
	public:
		float X, Y;

		void Print()
		{
			std::cout << X << ", " << Y << std::endl;
		}
	};


	void main()
	{
		Entity e{1,2};
		e.Print();
	}
}

#include <string>
namespace inheritance
{
	class Entity
	{
	public:
		float X, Y;

		void move(float xa, float ya)
		{
			X += xa;
			Y += ya;
		}
	};

	class Player : public Entity
	{
	public:
		const char* Name;

		void PrintName()
		{
			std::cout << Name << std::endl;
		}
	};

	void main()
	{
		std::cout << sizeof(Entity) << std::endl;
		std::cout << sizeof(Player) << std::endl;
		Player player;
		player.move(5, 5);
	}
}

namespace virtual_function
{
	class Entity
	{
	public:
		virtual std::string GetName() { return "Entity"; } // 声明一个虚函数，告诉编译器在运行时根据对象的实际类型来决定调用哪个函数，而不是在编译时就决定了调用哪个函数。虚函数需要在基类中声明，并且在派生类中重写（override）才能实现多态性。
		// 本质上，虚函数在编译时会被编译器处理成一个函数指针表（vtable），每个类都有一个vtable，里面存储了该类的虚函数的地址。当通过基类指针调用虚函数时，编译器会根据对���的实际类型来查找对应的vtable，并调用正确的函数实现。
	};

	class Player : public Entity
	{
	private:
		std::string m_Name;
	public:
		Player(const std::string& name) : m_Name(name) {}
		std::string GetName() override { return m_Name; } // 重写基类的虚函数，告诉编译器在运行时调用这个函数时，如果对象的实际类型是Player，就调用Player类中的GetName函数，而不是Entity类中的GetName函数。
	};

	void main()
	{
		Entity* e = new Entity();
		std::cout << e->GetName() << std::endl;

		Player* p = new Player("Stranger");
		std::cout << p->GetName() << std::endl; // 为什么输出Stranger？因为Player类重写了Entity类的GetName函数，当通过Player对象调用GetName函数时，实际调用的是Player类中的GetName函数，而不是Entity类中的GetName函数，所以输出Stranger。

		Entity* q = p;
		std::cout << q->GetName() << std::endl; // 为什么输出Stranger？因为Entity类的GetName函数是虚函数，当通过Entity指针调用GetName函数时，编译器会根据对象的实际类型来决定调用哪个函数，而q指向的是一个Player对象，所以实际调用的是Player类中的GetName函数，而不是Entity类中的GetName函数，所以输出Stranger。
	}
}

namespace interface {
	class Printable {
	public:
		virtual std::string GetClassName() = 0; // 纯虚函数
		virtual ~Printable() = default;         // 虚析构
	};

	class Entity : public Printable {
	public:
		virtual std::string GetName() { return "Entity"; } // 提供默认实现
		std::string GetClassName() override { return "Entity"; }
	};

	class Player : public Entity {
	private:
		std::string m_Name;
	public:
		Player(const std::string& name) : m_Name(name) {}
		std::string GetName() override { return m_Name; }
		std::string GetClassName() override { return "Player"; }
	};

	void Print(Printable* obj) {
		std::cout << obj->GetClassName() << std::endl;
	}

	int main() {
		Entity* e = new Entity;
		Print(e);
		delete e;

		Player* p = new Player("Stranger");
		Print(p);
		delete p;
		return 0;
	}
}

#include <array>
namespace array
{
	void main()
	{
		int* example = new int[5];
		for (int i = 0; i < 5; i++)
			example[i] = i;

		static int size3 = 5; // static关键字告诉编译器size3是一个静态变量，虽然它在程序运行期间只有一份内存，但它的值在运行时才确定，因此不能用来定义数组的大小。
		//! int c[size3]; [error] expression must have a constant value
		// 只有当size3是编译时常量时，才能用来定义数组的大小，因为数组的大小必须在编译时确定，而不能在运行时动态分配。

		const int size = 5; // const关键字告诉编译器size是一个常量，虽然它在程序运行期间只有一份内存，但它的值在编译时就确定了，因此可以用来定义数组的大小。
		int a[size]; // 定义一个大小为size的数组，size是一个编译时常量，可以在编译阶段就确定它的值，因此可以用来定义数组的大小。

		static const int size1 = 5; // static const关键字告诉编译器size1是一个静态常量，虽然它在程序运行期间只有一份内存，但它的值在编译时就确定了，因此可以用来定义数组的大小。
		int b[size1];

		static constexpr int size2 = 5; // constexpr关键字告诉编译器size2是一个编译时常量，可以在编译阶段就确定它的值，因此可以用来定义数组的大小。
		int c[size2];
		// const 和 static constexpr 都可以用来定义编译时常量，但constexpr更严格，要求变量必须在编译时就能确定值，而const只要求变量的值在运行时不变，所以constexpr更适合用来定义数组大小等需要编译时常量的场景。

		std::array <int, 5> another; // std::array是一个模板类，提供了一个固定大小的数组，大小在编译时确定，元素类型由模板参数指定。std::array提供了更丰富的成员函数和操作符重载，使得使用起来更方便和安全，同时也支持范围for循环等现代C++特性。
		}
}

int main()
{
	// pointer::main();
	// reference::main();
	// std::cout << s_Variable << std::endl;
	// Static::main();
	// local_static::main();
	// Ctor_Dtor::main();
	// inheritance::main();
	// virtual_function::main();
	// interface::main();
	array::main();


	
	std::cin.get();
}