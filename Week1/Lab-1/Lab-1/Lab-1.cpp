// Lab-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//Shapes
//Circle
//Rectangle
//Get area function
//Constructors
//Member variables/ data members



class Circle
{
private:
	double m_radius; // double-precision floating point type

	const double PI = 3.141592654;

public:
	Circle()
	{
		m_radius = 1.0;
	}

	Circle(double radius) : m_radius(radius)
	{
	}

	//Mutator changes  things
	void setRadius(double newRadius)
	{
		m_radius = newRadius;
	}

	// Accessor gets things
	double getRadius()
	{
		return m_radius;
	}

	double getArea()
	{
		double area = PI * (m_radius * m_radius);
		return area;
	}
};

class Rectangle
{
private:
	double m_width, m_height;

public:
	Rectangle()
	{
	}

	void setDimensions(double width, double height)
	{
		m_width = width;
		m_height = height;
	}

	double getArea()
	{
		return m_width * m_height;
	}
};


Circle g_Circle0 = Circle();
Circle g_Circle1 = Circle(5.0);
Circle g_Circle2 = Circle(2.0);


//pointer
double* radii;

//array -- a pointer to a list of elements in memory of the same type, with consistent spacing between.
double radiiArray[] = { 0.0, 5.0, 2.0 };

// & address of
// * pointer OR dereference

int main()
{
	std::cout << "Circles\n";
	std::cout << g_Circle0.getArea() << std::endl;
	std::cout << g_Circle1.getArea() << std::endl;
	std::cout << g_Circle2.getArea() << std::endl;

	std::cout << "Array\n";
	std::cout << &radiiArray[0] << std::endl; //[] array access by index (offsets the pointer by the number entered * size of the data type
	std::cout << &radiiArray[1] << std::endl;
	std::cout << &radiiArray[2] << std::endl;

	radii = new double[3]{ 0.0, 5.0, 2.0 };
	std::cout << "Dynamic Array\n";
	std::cout << radii[0] << std::endl; //[] array access by index (offsets the pointer by the number entered * size of the data type
	std::cout << radii[1] << std::endl;
	std::cout << radii[2] << std::endl;


	for (int i = 0; i < 3; i++)
	{
		double element = radii[i];
		double* elementPointer = &element;

		delete elementPointer;
	}
	radii = nullptr;

	Circle* pMyDynamicCircle = new Circle(4.0); // allocate memory for a Circle, store address in a pointer variable (pointer is allocated on the stack)
	// Pointer goes out of scope!!!

	delete pMyDynamicCircle;
	pMyDynamicCircle = nullptr;

	std::getchar(); //Similar to System("Pause") but more robust
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
