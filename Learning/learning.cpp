/*
 *（1）const是函数类型的一部分，在实现部分也要带该关键字。

 *（2）const关键字可以用于对重载函数的区分。

 *（3）常成员函数不能更新类的成员变量，也不能调用该类中没有用const修饰的成员函数，只能调用常成员函数。

 *（4）非常量对象也可以调用常成员函数，但是如果有重载的非常成员函数则会调用非常成员函数。
 */

//#include<iostream>
//using namespace std;
//
//class Test {
//protected:
//	int x;
//public:
//	Test(int i) : x(i) {}
//	void fun() const
//	{
//		cout << "fun() const called " << endl;
//	}
//	void fun()
//	{
//		cout << "fun() called " << endl;
//	}
//};
//
//int main()
//{
//	Test t1(10);
//	const Test t2(20);
//	t1.fun();
//	t2.fun();
//	return 0;
//}
/*
 fun() called
 fun() const called
 */

// case 1
//#include<iostream>
//using namespace std;
//
//void fun(const int i)
//{
//	cout << "fun(const int) called ";
//}
//void fun(int i)
//{
//	cout << "fun(int ) called ";
//}
//int main()
//{
//	const int i = 10;
//	fun(i);
//	return 0;
//}

/*
 Redefinition of 'fun' : 50
 */

//// case 2
//#include<iostream>
//using namespace std;
//
//void fun(char *a)
//{
//	cout << "non-const fun() " << a;
//}
//
//void fun(const char *a)
//{
//	cout << "const fun() " << a;
//}
//
//int main()
//{
//	const char *ptr = "hello world";
//	fun(ptr);
//	return 0;
//}

/*
 函数 'fun' 从未使用
 */

// case 3
//#include<iostream>
//using namespace std;

//void fun(char *a)
//{
//	cout << "non-const fun() " << a;
//}
//
//void fun(char *const a)
//{
//	cout << "const fun() " << a;
//}
//

//int main()
//{
//	char ptr[] = "hello world";
//	fun(ptr);
//	return 0;
//}

/*
 Redefinition of 'fun' : 98
 */