#include <iostream>

class Base {
public:
	int i;

	virtual void test_function1() { std::cout << "Base::test_function1()" << std::endl; }
	virtual void test_function2() { std::cout << "Base::test_function2()" << std::endl; }
	virtual void test_function3() { std::cout << "Base::test_function3()" << std::endl; }
};

class Derived : public Base {
	void test_function1() { std::cout << "Derived::test_function1()" << std::endl; };
	void test_function2() { std::cout << "Derived::test_function1()" << std::endl; };
	void test_function3() { std::cout << "Derived::test_function1()" << std::endl; };
};

Base base;
Derived derived;

int main()
{
	int ilen1 = sizeof(base);
	int ilen2 = sizeof(derived);

	std::cout << ilen1 << std::endl;
	std::cout << ilen2 << std::endl;

	return 0;
}

