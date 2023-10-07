#include <iostream>
#include <utility>
#include <type_traits>

int& lvalue();
int&& xvalue();
int prvalue();

int main()
{
	std::cout << std::is_same<decltype(lvalue()), int&>::value << std::endl;    // yields true because result is lvalue
	std::cout << std::is_same<decltype(xvalue()), int&&>::value << std::endl;   // yields true because result is xvalue
	std::cout << std::is_same<decltype(prvalue()), int>::value << std::endl;    // yields true because result is prvalu

	int& lref1 = lvalue(); 		// OK: lvalue reference can bind to an lvalue
	int& lref2 = prvalue(); 	// ERROR: lvalue reference cannot bind to a prvalue
	int& lref3 = xvalue(); 		// ERROR: lvalue reference cannot bind to an xvalue
	int&& rref1 = lvalue(); 	// ERROR: rvalue reference cannot bind to an lvalue
	int&& rref2 = prvalue(); 	// OK: rvalue reference can bind to a prvalue
	int&& rref3 = xvalue(); 	// OK: rvalue reference can bind to an xrvalue

	return 0;
}