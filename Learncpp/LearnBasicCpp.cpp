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
		memset(buffer, 0, 8);		// fill the memory block with 0s, or '\0' in the case of char

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

// extern int s_Variable; // ͨ��extern�ؼ�������һ���ⲿ���������߱�������������������ط�������ˣ���������ȥ���ӽ׶��ҵ���������Ķ��岢���ӵ���ǰ�ļ��С�

// extern void Function(); // ͨ��extern�ؼ�������һ���ⲿ����

namespace Static
{
	struct Entity
	{
		static int x, y; // ����static��Ա���������������౾�������������ʵ�����������ڴ���ֻ��һ�ݣ����ܴ������ٸ�Entity����x��y������ͬһ���ڴ档

		static void static_Print() // ����static��Ա����������Ҳ�����౾��������ֱ��ͨ���������ã�������Ҫ�������󡣾�̬��Ա����ֻ�ܷ��ʾ�̬��Ա���������ܷ��ʷǾ�̬��Ա��������Ϊ�Ǿ�̬��Ա�������ڶ���ʵ��������̬��Ա����û��thisָ�룬�޷����ʶ���ʵ����
		{
			std::cout << x << "," << y << std::endl;
		}

		void Print()
		{
			std::cout << x << "," << y << std::endl;
		}

		// �Ǿ�̬��Ա�����������ϴ�����һ����ʽ��thisָ�룬ָ����øú����Ķ���ʵ�������Կ��Է��ʷǾ�̬��Ա�����;�̬��Ա������

		void Print(Entity *e) // ͨ������һ��Entity����ָ�������ʾ�̬��Ա��������Ȼ��̬��Ա���������ڶ���ʵ����������ͨ������ʵ�����������ǣ���Ϊ�������ڴ���ֻ��һ�ݣ����ж���ʵ������ͬһ���ڴ档
		{
			std::cout << e->x << "," << e->y << std::endl;
		}
	};

	int Entity::x; // ����static��Ա���������������ⶨ�塣��δָ����ֵ����̬��Ա�����ᱻĬ�ϳ�ʼ��Ϊ0��
	int Entity::y;

	void main()
	{
		Entity e, e1;
		e.x = 2;
		e.y = 3;

		//! Entity e1 = { 5,8 }; // Ĭ�Ϲ��캯�����������б���ʼ������ʼ����̬��Ա��������Ϊ��̬��Ա�������������ʵ�������������౾�����������ǲ���ͨ����������ʼ����ֻ��ͨ����������ʼ����
		e1.x = 5;
		e1.y = 8;

		e.Print();
		e1.Print();
		Entity::static_Print(); // ͨ���������þ�̬��Ա��������̬��Ա����ֱ�ӷ��ʾ�̬��Ա���������5,8���������ڶ���ʵ����
	}
}

#include <string>
namespace virtual_function
{
	class Entity
	{
	public:
		std::string GetName() { return "Entity"; }
	};

	class Player : public Entity
	{
	private:
		std::string m_Name;

	public:
		Player(const std::string &name) : m_Name(name) {}
		std::string GetName() { return m_Name; }
	};
}

int main()
{
	// pointer::main();
	// reference::main();
	// std::cout << s_Variable << std::endl;
	Static::main();
	std::cin.get();
}