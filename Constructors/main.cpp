#include <iostream>

int main()
{
	class Vector{
	public:
		Vector()
		{
			std::cout << "Default constructor" << std::endl;
		}
		Vector(int m_value):m_int(m_value)
		{
			std::cout << "Constructor with a parameter" << std::endl;
		}
	private:
		int m_int;
	};

	Vector v1;
	Vector v2{};
	Vector v3(1);
	Vector v4{1};

	std::cout << "Well done!" << std::endl;
	return 0;
}
