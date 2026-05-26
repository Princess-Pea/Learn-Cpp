#include <iostream>

#define LOG(x) std::cout << x << std::endl;

namespace pointer
{
	void main()
	{
		int var = 8;
		// int* ptr = &var;
		// double* q = (double*)&var;
		//*ptr = 10;
		// LOG(var);

		char *buffer = new char[8]; // buffer is a pointer pointing to a block of memory of 8 bytes, which is enough to hold 8 chars
		// memset(buffer, 0, 8);		// fill the memory block with 0s, or '\0' in the case of char

		char **ptr = &buffer;

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

	void Increment_ptr(int *value)
	{
		(*value)++;
	}

	void Increment_ref(int &value)
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
		int &ref = a;
		ref = b; // a = b; => a=8,b=8,ref=8.

		// int* b = &a;
		// int& ref = a; // create an alias for a, ref is another name for a, it refers to the same memory location as a
		// ref = 2;

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

		void Print(Entity *e) // 通过传入一个Entity对象指针来访问静态成员变量。虽然静态成员变量不属于对象实例，但可以通过对象实例来访问它们，因为它们在内存中只有一份，所有对象实例共享同一份内存。
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
		static Singleton *s_Instance; // 静态成员变量，属于类本身，在内存中只有一份，所有对象实例共享同一份内存。
	public:
		static Singleton &Get_ref() { return *s_Instance; } // 返回一个引用
		static Singleton *Get_ptr() { return s_Instance; }	// 返回一个指针
		static Singleton &Get()
		{
			Singleton instance;
			return instance; // 返回的引用成为悬垂引用，因为变量instance在函数结束时被销毁，后续任何通过该引用访问对象的行为都是未定义行为。
		}
		void Hello() { std::cout << "Hello Singleton!" << std::endl; }
	};

	Singleton *Singleton::s_Instance; // 定义静态成员变量，必须在类外定义。

	void Function()
	{
		static int i = 0; // 局部静态变量，虽然在函数内部定义，但它的生命周期贯穿整个程序运行期间，只有一份内存，不管调用多少次Function函数，s_LocalStatic都共享同一份内存，并且只会被初始化一次。
		// 这种办法主要是在函数内部维护一个状态时，避免使用全局变量，同时又不需要每次调用函数都重新初始化变量。
		std::cout << i << std::endl;
		i++;
	}
	void main()
	{
		// for (int i = 0; i < 5; i++)
		// Function();
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
		Entity e{1, 2};
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
		const char *Name;

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
		Player(const std::string &name) : m_Name(name) {}
		std::string GetName() override { return m_Name; } // 重写基类的虚函数，告诉编译器在运行时调用这个函数时，如果对象的实际类型是Player，就调用Player类中的GetName函数，而不是Entity类中的GetName函数。
	};

	void main()
	{
		Entity *e = new Entity();
		std::cout << e->GetName() << std::endl;

		Player *p = new Player("Stranger");
		std::cout << p->GetName() << std::endl; // 为什么输出Stranger？因为Player类重写了Entity类的GetName函数，当通过Player对象调用GetName函数时，实际调用的是Player类中的GetName函数，而不是Entity类中的GetName函数，所以输出Stranger。

		Entity *q = p;
		std::cout << q->GetName() << std::endl; // 为什么输出Stranger？因为Entity类的GetName函数是虚函数，当通过Entity指针调用GetName函数时，编译器会根据对象的实际类型来决定调用哪个函数，而q指向的是一个Player对象，所以实际调用的是Player类中的GetName函数，而不是Entity类中的GetName函数，所以输出Stranger。
	}
}

namespace interface
{
	class Printable
	{
	public:
		virtual std::string GetClassName() = 0; // 纯虚函数
		virtual ~Printable() = default;			// 虚析构
	};

	class Entity : public Printable
	{
	public:
		virtual std::string GetName() { return "Entity"; } // 提供默认实现
		std::string GetClassName() override { return "Entity"; }
	};

	class Player : public Entity
	{
	private:
		std::string m_Name;

	public:
		Player(const std::string &name) : m_Name(name) {}
		std::string GetName() override { return m_Name; }
		std::string GetClassName() override { return "Player"; }
	};

	void Print(Printable *obj)
	{
		std::cout << obj->GetClassName() << std::endl;
	}

	int main()
	{
		Entity *e = new Entity;
		Print(e);
		delete e;

		Player *p = new Player("Stranger");
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
		int *example = new int[5];
		for (int i = 0; i < 5; i++)
			example[i] = i;

		static int size3 = 5; // static关键字告诉编译器size3是一个静态变量，虽然它在程序运行期间只有一份内存，但它的值在运行时才确定，因此不能用来定义数组的大小。
		//! int c[size3]; [error] expression must have a constant value
		// 只有当size3是编译时常量时，才能用来定义数组的大小，因为数组的大小必须在编译时确定，而不能在运行时动态分配。

		const int size = 5; // const关键字告诉编译器size是一个常量，虽然它在程序运行期间只有一份内存，但它的值在编译时就确定了，因此可以用来定义数组的大小。
		int a[size];		// 定义一个大小为size的数组，size是一个编译时常量，可以在编译阶段就确定它的值，因此可以用来定义数组的大小。

		static const int size1 = 5; // static const关键字告诉编译器size1是一个静态常量，虽然它在程序运行期间只有一份内存，但它的值在编译时就确定了，因此可以用来定义数组的大小。
		int b[size1];

		static constexpr int size2 = 5; // constexpr关键字告诉编译器size2是一个编译时常量，可以在编译阶段就确定它的值，因此可以用来定义数组的大小。
		int c[size2];
		// const 和 static constexpr 都可以用来定义编译时常量，但constexpr更严格，要求变量必须在编译时就能确定值，而const只要求变量的值在运行时不变，所以constexpr更适合用来定义数组大小等需要编译时常量的场景。

		std::array<int, 5> another; // std::array是一个模板类，提供了一个固定大小的数组，大小在编译时确定，元素类型由模板参数指定。std::array提供了更丰富的成员函数和操作符重载，使得使用起来更方便和安全，同时也支持范围for循环等现代C++特性。
	}
}

#include <string>
namespace String
{
	void main()
	{
		const char *str = "Syalis"; // C style way to define a string, a is a pointer pointing to a string literal "Syalis" stored in read-only memory. C style strings are null-terminated, meaning they end with a '\0' character to indicate the end of the string. C style strings are not safe to use because they can lead to buffer overflows and other memory issues if not handled carefully.
		// name[2] = 'a'; // [error] assignment of read-only location 'name[2]'
		char s[] = "Syalis";
		//! std::cout << s[]; // [error]
		std::string name = "Syalis";
		std::cout << name << std::endl; // string 类实现了对输入输出流的操作符重载
		name += ",hi!";					// string 类实现了操作符重载
		std::cout << name << std::endl;
		name = std::string("Syalis") + ",hi!"; // string 类实现了操作符重载，允许我们直接使用 + 操作符来连接字符串，而不需要像 C 风格字符串那样使用 strcat 函数来连接字符串，这使得代码更简洁和易读。
		std::cout << name << std::endl;
		name.find("is") != std::string::npos; // string 类提供了丰富的成员函数来操作字符串，例如find函数可以用来查找子字符串，返回子字符串在字符串中的位置，如果找不到则返回std::string::npos。
	}

	void PrintString_pass_by_value(std::string s) // 传值方式传递字符串，函数内部会创建一个新的字符串对象，并将实参字符串的内容复制到新对象中，这可能会导致性能问题，尤其是当字符串较大时，因为复制操作需要分配新的内存并复制数据。
	{
		std::cout << s << std::endl;
	}
	void PrintString_pass_by_reference(const std::string &s) // 传引用方式传递字符串，函数内部不会创建新的字符串对象，而是直接使用实参字符串的引用，这样可以避免不必要的复制操作，提高性能，尤其是当字符串较大时，因为它只需要传递一个指针而不是复制整个字符串。
	{
		std::cout << s << std::endl;
	}
}

#include <stdlib.h>
namespace string_literals
{
	void main()
	{
		const char *name = "Syalis";
		//! s[2] = 'a'; // [error] assignment of read-only location 's[2]'.
		//! char* n = "Syalis"; // [error] 未定义行为，因为字符串字面值 "Syalis" 存储在只读内存中。
		char *n = (char *)"Syalis"; // 这种方式定义的字符串是一个指针，指向一个字符串字面值 "Syalis" 存储在只读内存中，虽然编译器允许这样定义，但在运行时修改字符串内容会导致未定义行为，因为它试图修改只读内存中的数据。
		n[2] = 'a';					// 这种方式定义的字符串是一个指针，指向一个字符串字面值 "Syalis" 存储在只读内存中，虽然编译器允许这样定义，但在运行时修改字符串内容会导致未定义行为，因为它试图修改只读内存中的数据。
		char s[] = "Syalis";
		s[2] = 'a'; // 这种方式定义的字符串是一个字符数组，存储在可读写的内存中，可以修改其中的字符，因为它是一个数组，而不是一个指针指向的字符串字面值。

		const wchar_t *wname = L"Syalis";	 // L前缀表示宽字符字符串字面值，wname是一个指针，指向一个宽字符字符串字面值 "Syalis".
		const char16_t *u16name = u"Syalis"; // u前缀表示UTF-16字符串字面值，u16name是一个指针，指向一个UTF-16字符串字面值 "Syalis".
		const char32_t *u32name = U"Syalis"; // U前缀表示UTF-32字符串字面值，u32name是一个指针，指向一个UTF-32字符串字面值 "Syalis".

		using namespace std::string_literals; // 引入字符串字面值命名空间，允许我们使用s后缀来定义std::string类型的字符串字面值。
		std::string name1 = "Syalis"s;		  // s后缀实际上是调用了std::string的构造函数，将字符串字面值 "Syalis" 转换为一个std::string对象，这样我们就可以直接使用字符串字面值来初始化std::string对象，而不需要显式地调用构造函数。
		name1 = "Syalis"s + ",hi!";			  // s后缀允许我们直接使用 + 操作符来连接字符串字面值和std::string对象，这样可以更方便地构建字符串，而不需要像 C 风格字符串那样使用 strcat 函数来连接字符串。

		const char *example = R"(line1
	Line2
	Line3
	Line4)";							   // R前缀表示原始字符串字面值，R"( ... )"中的内容会被原样保留，包括换行符和制表符等特殊字符，这使得定义多行字符串变得非常方便，而不需要使用转义字符来表示换行符或其他特殊字符。
		std::cout << example << std::endl; // 输出时会保留原始字符串中的格式，包括换行符和制表符等特殊字符���因此输出结果会按照原始字符串的格式显示
	}
	const char *ex = "Line1\n"
					 "Line2\n"
					 "Line3\n"; // 这种方式定义的字符串是一个指针，指向一个字符串字面值 "Line1\nLine2\nLine3\n" 存储在只读内存中，虽然��译器允许这样定义，但在运行时修改字符串内容会导致未定义行为，因为它试图修改只读内存中的数据。
}

namespace Const
{
	class Entity
	{
	private:
		int X, Y;
		int *m_X, m_Y;	 // 注意这里m_X是一个指针，m_Y是一个整数，虽然它们在同一行声明，但它们的类型不同，m_X是一个指向整数的指针，而m_Y是一个整数。
		mutable int var; // mutable关键字告诉编译器这个成员变量可以在const成员函数中被修改，即使这个成员变量属于一个const对象。这是因为有些成员变量可能需要在对象的生命周期内被修改，但又不应该影响对象的外部状态，例如缓存、统计信息等。使用mutable关键字可以允许这些成员变量在const成员函数中被修改，而不会违反const对象的不可变性原则。
	public:
		int GetX() const // const成员函数，表示这个函数不会修改对象的状态，可以在const对象上调用。
		{
			//! m_X = 5; // [error] assignment of member 'Const::Entity::m_X' in read-only object
			var = 2; // mutable成员变量可以在const成员函数中被修改，即使这个成员变量属于一个const对象。
			return X;
		}
		void SetX(int x) { X = x; }		// 非const成员函数，表示这个函数可能会修改对象的状态，不能在const对象上调用。
		const int *const Getm_X() const // const成员函数，返回一个指向常量的常量指针，表示这个函数不会修改对象的状态，并且返回的指针指向的内容也是一个常量，不能通过这个指针来修改它所指向的内容。
		{
			return m_X;
		}
	};

	void PrintEntity(const Entity &e) // 传递一个const Entity对象的引用，表示这个函数不会修改传入的Entity对象，但可以接受const对象和非const对象作为实参。
	{
		std::cout << e.GetX() << std::endl; // 在函数内部调用Entity对象的const成员函数GetX()，因为这个函数不会修改对象的状态，所以可以在const对象上调用。
	}

	void main()
	{
		const int MAX = 100;
		//! MAX = 1000; // [error] assignment of read-only variable 'a'.
		int *a = new int;
		*a = 5;
		a = (int *)&MAX;
		std::cout << *a << std::endl;

		const int *b = new int; // 等价于 int const* b.  const修饰指针指向的内容，表示指针b指向的内容是一个常量，不能通过b来修改它所指向的内容，但可以改变b本身的值，让它指向其他地址。
		//! *b = 5; // [error] assignment of read-only location '*b'.
		b = &MAX; // 这种方式定义的指针b是一个指向常量的指针，虽然编译器允许这样定义，但在运行时修改指针b的值会导致未定义行为，因为它试图修改只读内存中的数据。

		int *const c = new int; // const修饰指针本身，表示指针c是一个常量指针，必须在定义时初始化，并且之后不能改变它的值，即不能让c指向其他地址，但可以通过c来修改它所指向的内容。
		*c = 5;
		//! c = &MAX; // [error] assignment of read-only variable 'c'.

		const int *const d = new int; // const修饰指针本身和指针指向的内容，表示指针d是一个常量指针，必须在定义时初始化，并且之后不能改变它的值，即不能让d指向其他地址，同时d指向的内容也是一个常量，不能通过d来修改它所指向的内容。
	}
}

namespace Initializer_list
{
	class Example
	{
	public:
		Example()
		{
			std::cout << "created Example!" << std::endl;
		}

		Example(int x)
		{
			std::cout << "created Example with value: " << x << std::endl;
		}
	};

	class Entity
	{
	private:
		std::string name;
		Example exp;

	public:
		Entity()
		{
			name = std::string("Unknowm");
			exp = Example(8);
		}
	};

	class entity
	{
	private:
		std::string name;
		Example exp;

	public:
		entity() : exp(8) // 等价于写成 exp = Example(8)
						  // 使用成员初始化列表来初始化exp成员变量，直接调用Example类的构造函数来创建一个Example对象，并将其赋值给exp成员变量，这样可以避免在构造函数体内先调用默认构造函数创建一个临时对象，然后再通过赋值操作来修改它的状态，这样做更高效，因为它直接在成员变量上构造对象，而不是先构造一个临时对象再赋值。
		{
			name = std::string("Unknowm");
		}
	};

	void main()
	{
		Entity E;
		std::cout << "--------------------------" << std::endl;
		entity e;
	}
}

namespace CREATE_INSTANTIATE_OBJECT
{
	using string = std::string;

	class Entity
	{
	private:
		string name;

	public:
		Entity() : name("Unknown") {}
		Entity(const string &name) : name(name) {}

		const string &GetName() const { return name; }
	};

	void Function()
	{
		int a = 2;
		Entity entity; // 在栈上创建了一个Entity对象，当Function函数结束时，entity对象会自动销毁，释放它占用的内存。
	}

	void main()
	{
		Entity *e;
		// 演示在栈上创建对象和在堆上创建对象的区别
		{
			Entity entity("Syalis");
			// 能在栈上创建对象就在栈上创建对象，因为栈上的对象会在离开作用域时自动销毁，避免了内存泄漏的问题;
			// 同时，栈上的对象访问速度更快，因为它们的内存分配和释放由编译器自动管理，不需要像堆上的对象那样进行动态内存分配和释放。
			std::cout << entity.GetName() << std::endl;
			e = &entity;
		}
		{
			Entity *entity = new Entity("Syalis");
			// 在堆上创建对象需要使用new运算符来动态分配内存，并且需要手动释放内存，否则会导致内存泄漏。
			std::cout << entity->GetName() << std::endl;
			e = entity;
			delete entity; // 手动释放内存，避免内存泄漏。
		}
		delete e;
	}
}

namespace New
{
	using string = std::string;

	class Entity
	{
	private:
		string name;

	public:
		Entity() : name("Unknown") {}
		Entity(const string &name) : name(name) {}

		const string &GetName() const { return name; }
	};

	void main()
	{
		int a = 2;
		int *b = new int;
		int *c = new int[50];

		Entity *e = new Entity("Syalis");
		//! Entity* e = (Entity*)malloc(sizeof(Entity)); // C style 方式使用malloc函数来动态分配内存，但我们在 C++ 中一般不这样写，因为它不会调用构造函数来初始化对象，因此需要手动调用构造函数来初始化对象，这样做比较麻烦，而且容易出错，因为如果忘记调用构造函数或者调用了错误的构造函数，可能会导致对象状态不正确或者内存泄漏等问题。
		delete e;
		delete b;
		delete[] c;
	}
}

namespace Implict_Explicit
{
	using string = std::string;

	class Entity
	{
	private:
		string name;
		int age;
		bool sex;

	public:
		Entity(const string &name) : name(name), age(-1), sex(true) {}
		Entity(int age) : name("Unknown"), age(age), sex(true) {}
		explicit Entity(bool s) : name("Unknown"), age(-1), sex(s) {} // explicit关键字告诉编译器这个构造函数是一个显式构造函数，禁止隐式类型转换，只有当我们显式地调用这个构造函数时才会进行类型转换，而不会在需要Entity对象的地方自动将bool类型转换为Entity对象，这样可以避免一些不必要的类型转换和潜在的错误。

		const string &GetName() const { return name; }
		const int &GetAge() const { return age; }
	};

	void PrintEntity(const Entity &e)
	{
		std::cout << "name: " << e.GetName() << std::endl
				  << "age: " << e.GetAge() << std::endl;
	}

	void main()
	{
		Entity a = string("Syalis"); // 这里发生了隐式类型转换，编译器会自动将string("Syalis")转换为Entity对象，调用Entity类的构造函数来创建一个Entity对象，并将其赋值给a变量，这样我们就可以直接使用字符串字面值来初始化Entity对象，而不需要显式地调用构造函数。
		// 等价于 Entity a("Syalis");
		Entity b = 18;
		// 等价于 Entity b(18);
		PrintEntity(18);
		// 等价于 PrintEntity(Entity(18));
		//! Entity c = true; // [error] 因为Entity类的构造函数Entity(bool s)被声明为explicit，所以编译器禁止隐式类型转换，不能直接将bool类型转换为Entity对象来初始化c变量，必须显式地调用构造函数来创建一个Entity对象，例如 Entity c(true); 这样才能成功编译。
	}
}

namespace OPERATORS_AND_OVERLOAD
{
	struct Vector2
	{
		float x, y;

		Vector2(float x, float y) : x(x), y(y) {}

		Vector2 Add(const Vector2 &other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator+(const Vector2 &other) const // 重载加法运算符，使得我们可以直接使用 + 操作符来进行向量的加法运算，而不需要显式地调用Add函数，这样代码更简洁和易读。
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 Multiply(const Vector2 &other) const
		{
			return Vector2(x * other.x, y * other.y);
		}
		Vector2 operator*(const Vector2 &other) const // 重载乘法运算符，使得我们可以直接使用 * 操作符来进行向量的乘法运算，而不需要显式地调用Multiply函数，这样代码更简洁和易读。
		{
			return Vector2(x * other.x, y * other.y);
		}

		bool operator==(const Vector2 &other) const // 重载等于运算符，使得我们可以直接使用 == 操作符来比较两个Vector2对象是否相等，而不需要显式地调用一个函数来进行比较，这样代码更简洁和易读。
		{
			return x == other.x && y == other.y;
		}

		// 本质上操作符就是函数，当我们使用 + 操作符时，编译器会将其转换为对 operator+ 函数的调用，例如 a + b 会被转换为 a.operator+(b)，同样的，a * b 会被转换为 a.operator*(b)，这样我们就可以通过重载这些运算符来定义它们在我们自定义类型上的行为，使得代码更自然和易读。

		void show()
		{
			std::cout << x << ", " << y << std::endl;
		}
	};

	std::ostream &operator<<(std::ostream &stream, const Vector2 &other)
	{
		stream << other.x << ", " << other.y;
		return stream;
	}

	void main()
	{
		Vector2 pos(3.0f, 4.0f);
		Vector2 speed(0.5f, 1.0f);
		Vector2 powerup(1.1f, 1.1f);

		Vector2 result = pos.Add((speed).Multiply(powerup)); // 先计算speed和powerup的乘积，得到一个新的Vector2对象，然后再将这个对象与pos进行加法运算，得到最终的结果。
		Vector2 result2 = pos + speed * powerup;			 // 由于我们重载了加法和乘法运算符，所以我们可以直接使用 + 和 * 操作符来进行向量的加法和乘法运算

		result.show();
		if (result2 == result)
			std::cout << result2 << std::endl; // 由于我们重载了输出流运算符，所以我们可以直接使用 << 操作符来输出Vector2对象，这样代码更简洁和易读。
	}
}

namespace This
{
	class Entity
	{
	public:
		int x, y;

		Entity(int x, int y)
		{
			//! x = x; // 这里的x和y是成员变量，但由于参数名和成员变量名相同，所以编译器会优先使用参数名来解析x和y,因此这里的x和y实际上是指向参数的，而不是成员变量，所以这段代码没有正确地初始化成员变量。
			this->x = x; // this指针是一个隐式参数，指向调用成员函数的对象实例，通过this指针可以访问对象的成员变量和成员函数，在构造函数中使用this指针来区分成员变量和参数名相同的情况，正确地初始化成员变量。
			this->y = y;
			// 相当于 Entity* e = this; e->x = x; e->y = y;
		}

		int GetX() const
		{
			//! Entity *e = this; // [error] invalid use of 'this' outside of a non-static member function
			const Entity *e = this;
			return x;
		}
	};
}

#include <memory>		// memory头文件包含了智能指针，例如std::unique_ptr, std::shared_ptr, std::weak_ptr等智能指针类型.这些智能指针提供了自动内存管理的功能，可以帮助我们避免内存泄漏和悬空指针等问题，同时也提供了更安全和方便的内存管理方式。
namespace Smart_Pointer // std::unique_ptr, std::shared_ptr, std::weak_ptr
{
	class Entity
	{
	public:
		Entity()
		{
			std::cout << "Entity created!" << std::endl;
		}
		~Entity()
		{
			std::cout << "Entity destroyed!" << std::endl;
		}
		void Print() {}
	};

	void main()
	{
		{
			std::unique_ptr<Entity> entity0(new Entity());
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			// 二者区别在于第一种方式需要手动调用new运算符来创建对象，并且需要手动释放内存，而第二种方式使用了std::make_unique函数来创建对象，std::make_unique函数会自动调用new运算符来创建对象，并且会自动管理内存，当智能指针超出作用域时会自动释放内存，避免了内存泄漏的问题，同时也提供了更安全和方便的内存管理方式。
			//! std::unique_ptr<Entity> e = entity; // [error] use of deleted function 'std::unique_ptr<Entity>::unique_ptr(const std::unique_ptr<Entity>&)'，即它的拷贝构造函数被删除了。
			// std::unique_ptr是一个独占所有权的智能指针，不能被复制，只能被移动，所以我们不能将一个std::unique_ptr对象赋值给另一个std::unique_ptr对象，这样会导致编译错误。
			entity0->Print();
			entity->Print();
		}

		std::shared_ptr<Entity> e0;
		std::weak_ptr<Entity> e_w;
		{
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			e0 = sharedEntity; // std::shared_ptr是一个共享所有权的智能指针，可以被复制和赋值，所以我们可以将一个std::shared_ptr对象赋值给另一个std::shared_ptr对象，这样它们就共享同一个对象的所有权，当最后一个std::shared_ptr对象被销毁时，才会真正释放内存。
			// 本质上使用了一个引用计数机制来管理对象的生命周期，每当一个std::shared_ptr对象被复制时，引用计数会增加，当一个std::shared_ptr对象被销毁时，引用计数会减少，当引用计数为0时，才会真正释放内存。
			e_w = sharedEntity; // std::weak_ptr是一个弱引用的智能指针，它不拥有对象的所有权，只是一个观察者，可以用来观察一个std::shared_ptr对象是否还存在，但不能直接访问它所指向的对象，如果需要访问对象，需要先将std::weak_ptr对象转换为std::shared_ptr对象，这样可以避免循环引用的问题，因为std::weak_ptr不会增加引用计数，所以当最后一个std::shared_ptr对象被销毁时，std::weak_ptr对象也会自动失效，不会导致内存泄漏。
		}
	}
}

#include <string.h>
namespace Copying
{
	class String
	{
	private:
		char *m_Buffer;
		unsigned int m_Size;

	public:
		String(const char *string)
		{
			m_Size = strlen(string);
			m_Buffer = new char[m_Size + 1];
			memcpy(m_Buffer, string, m_Size); // 等价于 for (unsigned int i = 0; i < m_Size; i++) m_Buffer[i] = string[i];
			m_Buffer[m_Size] = '\0';
		}

		// String(const String& other) : m_Buffer(other.m_Buffer), m_Size(other.m_Size) {} // 默认的拷贝构造函数，编译器会自动生成一个默认的拷贝构造函数来进行成员逐个复制，这样就会导致string1和second对象的m_Buffer指针指向同一块内存，当其中一个对象被销毁时，另一个对象的m_Buffer指针就会变成悬空指针，导致未定义行为。

		// String(const String& other)
		//{
		//	memcpy(this, &other, sizeof(String)); // 默认拷贝构造函数的等价实现
		//}

		String(const String &other) : m_Size(other.m_Size)
		// 拷贝构造函数，参数是一个const String对象的引用，表示这个函数不会修改传入的String对象，但可以接受const对象和非const对象作为实参。这就是所谓的深拷贝。
		{
			std::cout << "Copying String!" << std::endl;
			m_Buffer = new char[m_Size + 1];
			memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		}

		~String()
		{
			delete[] m_Buffer;
			m_Buffer = nullptr;
		}

		char &operator[](unsigned int index) // 重载下标运算符，使得我们可以直接使用 [] 操作符来访问字符串中的字符，而不需要显式地调用一个函数来进行访问，这样代码更简洁和易读。
		{
			return m_Buffer[index];
		}

		friend std::ostream &operator<<(std::ostream &stream, const String &str);
	};

	std::ostream &operator<<(std::ostream &stream, const String &str)
	{
		stream << str.m_Buffer;
		return stream;
	}

	void PrintString_by_value(String s)
	{
		std::cout << s << std::endl;
	}

	void PrintString(const String &s)
	{
		std::cout << s << std::endl;
	}

	void main()
	{
		String string1 = "Syalis";
		String second = string1; // 这里发生了隐式的拷贝构造（也就是所谓的浅拷贝），编译器会自动生成一个默认的拷贝构造函数来进行成员逐个复制，这样就会导致string1和second对象的m_Buffer指针指向同一块内存，当其中一个对象被销毁时，另一个对象的m_Buffer指针就会变成悬空指针，导致未定义行为。

		second[2] = 'e';

		PrintString(string1);
		PrintString(second);
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
	// array::main();
	// String::main();
	// string_literals::main();
	// Const::main();
	// Initializer_list::main();
	// CREATE_INSTANTIATE_OBJECT::main();
	// New::main();
	// Implict_Explicit::main();
	// OPERATORS_AND_OVERLOAD::main();
	// This::main();
	// Smart_Pointer::main();
	Copying::main();
	std::cin.get();
}