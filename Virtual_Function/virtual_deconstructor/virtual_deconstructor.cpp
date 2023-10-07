//
// Created by 30205 on 2023/2/19.
//

#include <iostream>

struct Data {};
struct Base {
	Data* data_ptr_;
	Data data_obj_;
	Base()
	{ 							// 编译器在 Base() 最开头自动调用 Data() 初始化非指针成员 data_obj_
		data_ptr_ = new Data(); // 手动初始化 指针成员 data_ptr_
	}

	virtual ~Base()
	{
		delete data_ptr_; 					// 手动释放 指针成员 data_ptr_
		::std::cout << "~Base() call!\n";	// 编译器 在 ~Base() 最末尾 自动调用 ~Data() 释放 非指针成员 data_obj_
	}

//	~Base()
//	{
//		delete data_ptr_; 					// 手动释放 指针成员 data_ptr_
//		::std::cout << "~Base() call!\n";	// 编译器 在 ~Base() 最末尾 自动调用 ~Data() 释放 非指针成员 data_obj_
//	}
};
struct Derived : public Base {
	// 继承 Base类 意味着 得到 父类Base 所有的成员变量
	// 从父类 Base 继承得到 的 成员变量如下：
	// Data* data_ptr_;
	// Data  data_obj_;
	// 派生类 独有的 成员变量：
	Data* data_ptr_2_;
	Data data_obj_2_;
	Derived()
	{ // 编译器 在 Derived() 最开头 自动调用 Base() 初始化 从父类继承得到的成员变量
		// 编译器 之后 自动调用 Data() 初始化 派生类独有的 非指针成员 data_obj_2_
		data_ptr_2_ = new Data(); // 手动初始化 派生类独有的 指针成员 data_ptr_2_
	}
	~Derived()
	{ // C++ 语法糖：父类的析构函数为虚函数时，派生类析构函数即便不写virtual关键字，也是虚函数
		// 这个语法糖的实质：实现多态时，派生类虚函数表中virtual~Derived()的函数指针覆盖了virtual~Base()的函数指针
		delete data_ptr_2_;
		::std::cout << "~Derived() call!\n";
		// 编译器 在 ~Derived() 最末尾 自动调用 ~Data() 来 释放 派生类 独有的 data_obj_2_
		// 仅当父类Base的析构函数~Base()为虚函数 时, 编译器 之后 才会自动调用 Base() 释放 从父类继承得到的成员变量
	}
};

int main()
{
	[]() {
		Base base_obj;
		Derived derived_obj;
		// 编译器自动调用 ~Derived() 释放 derived_obj
		// 编译器自动调用 ~Base() 释放 base_obj
	}();

	std::cout << std::endl;

	[]() {
		Base* ptr = new Base();
		delete ptr; // 编译器在delete 中自动调用 ~Base() 释放 ptr
	}();

	std::cout << std::endl;

	[]() {
		Derived* ptr = new Derived();
		delete ptr; // 编译器在delete 中自动调用 ~Derived() 释放 ptr
	}();

	std::cout << std::endl;

	[]() {
		Base* ptr = new Derived();
		delete ptr; // 编译器在delete 中自动调用 ~Derived() 释放 ptr
		/*
		思考：如果Base的析构函数 ~Base() 不是虚函数的话，这里自动调用的函数是谁？
		答案是：~Base()，如此一来，派生类某些独有的成员变量就无法释放了，会造成未知的内存泄漏
		*/
	}();

	return 0;
}

/*
#include <iostream>

struct Base {
	// 虚函数在虚函数表中的下标位置与虚函数在第一次定义时的先后顺序有关，因为 Base 只含有一个虚函数 ~Base(), 所以 ~Base() 在虚函数表中的位置为下标0
	virtual ~Base()
	{
		::std::cout << "~Base() call!\n";
	}
};
struct Derived : public Base {
	~Derived()
	{	// C++ 语法糖：父类的析构函数为虚函数时，派生类析构函数即便不写virtual关键字，也是虚函数
		// 这个语法糖的实质：实现多态时，派生类虚函数表中virtual~Derived()的函数指针覆盖了virtual~Base()的函数指针
		::std::cout << "~Derived() call!\n";
	}
};
int main()
{
	[]() {
		Base* base_ptr = new Base();
		using vfptr = void (*)(Base*); 					// Base*：C++调用类成员函数的函数签名的底层实现是在函数参数列表多传入一个类对象的指针当作this。
		vfptr** vfptr_table_ptr = (vfptr**)base_ptr;	// 类对象的地址指向该对象的虚函数表的首地址
		vfptr* vfptr_table = *vfptr_table_ptr;			// 得到该对象的虚函数表
		vfptr_table[0](base_ptr); 						// 调用下标为0的虚函数，此语句相当于base_ptr->vfptr_table[0]();
		// 调用结果：
		// ~Base() call!
	}();

	std::cout << "\n";

	[]() {
		Derived* derived_ptr = new Derived();
		using vfptr = void (*)(Derived*);
		vfptr** vfptr_table_ptr = (vfptr**)derived_ptr;
		vfptr* vfptr_table = *vfptr_table_ptr;
		vfptr_table[0](derived_ptr);
		// 调用结果：
		// ~Derived() call!
		// ~Base() call!
	}();

	std::cout << "\n";

	[]() {
		Base* dynamic_ptr = new Derived();
		using vfptr = void (*)(Base*);
		vfptr** vfptr_table_ptr = (vfptr**)dynamic_ptr;
		vfptr* vfptr_table = *vfptr_table_ptr;
		vfptr_table[0](dynamic_ptr);
		// 调用结果：
		// ~Derived() call!
		// ~Base() call!
		// 上述结果 可以清晰的看到，C++的虚析构函数就是在类对象指针指向的虚函数表中，用派生类的析构函数指针覆盖掉原先的基类虚析构函数指针。
	}();

	return 0;
}*/
