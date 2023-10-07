//
// Created by 30205 on 2023/2/22.
//

#include <iostream>

using namespace std;

class Base {
public:
	void f1()
	{
		cout << "The function f1 in class Base" << endl;
	}

	virtual void f2()
	{
		cout << "The function f2 in class Base" << endl;
	}

	virtual void f3()
	{
		cout << "The function f3 in class Base" << endl;
	}

	virtual void f5()
	{
		cout << "The function f5 in class Base" << endl;
	}
};

class Derived : public Base {
public:
	virtual void f1()
	{
		cout << "The function f1 in class Derived" << endl;
	}
	virtual void f2() override
	{
		cout << "The function f2 in class Derived" << endl;
	}
	virtual void f4()
	{
		cout << "The function f4 in class Derived" << endl;
	}
	virtual void f5(int x)
	{
		cout << "The function f5 in class Derived" << endl;
	}
};

int main()
{
	Base* base_pointer_1 = new Base;
	base_pointer_1->f1();
	base_pointer_1->f2();
	base_pointer_1->f3();
//	base_pointer_1->f4(); 		// error: No member named 'f4' in 'Base'
	base_pointer_1->f5();

	cout << endl;

	Base* base_pointer_2 = new Derived;
	base_pointer_2->f1();
	base_pointer_2->f2();
	base_pointer_2->f3();
//	base_pointer_2->f4(); 		// error: No member named 'f4' in 'Base'
	base_pointer_2->f5();
//	base_pointer_2->f5(10); 	// error: Too many arguments to function call, expected 0, have 1

	cout << endl;

	Derived* derived_pointer = new Derived;
	derived_pointer->f1();
	derived_pointer->f2();
	derived_pointer->f3();
	derived_pointer->f4();
//	derived_pointer->f5(); 		// error: Too few arguments to function call, expected 1, have 0; did you mean 'Base::f5'?
	derived_pointer->f5(10);
}