////////////////////////////////////////////////////////////////
// GAME1011 Lab 6
////////////////////////////////////////////////////////////////

/////// Topic: Template Classes part 2
// https://www.cplusplus.com/reference/vector/vector/
// https://www.geeksforgeeks.org/linear-search/

/////// Keywords to note
/*
template
typename
auto
"T"
"Template meta-programming"
*/

/////// Lab activities
// This lab, we will be developing a SimpleVector template class, and extend it to create a SearchableVector which allows us to look up element index by value

/////// 1: Setup
// Clone the repo, set this Lab as "Startup Project", or start a new project with a main function                                                                                     

/////// 2: Make a "SimpleVector" class. This is an Array List container, similar to std::vector - https://www.cplusplus.com/reference/vector/vector/
// This class needs: 
// Constructor which takes a maximum size to start with
// Destructor (virtual)
// Store an ordered array of elements allocated with new
// Provide read/write access to elements with []
// Provide number of elements inside with a Size() function

/////// 3: Make SimpleVector a Template class
// Make sure SimpleVector can contain any object type
// Test it with some different types!
// We will instantiate objects of type SimpleVector with a type name. e.g. SimpleVector<int> stores ints.

/////// 4: Make a SearchableVector class
// Extend SimpleVector with an extra function size_t Find(T value) that allows us to linear search for an index by value 
// Yes, we could add this as a function of SimpleVector, or add it as an external function...
// ...but this helps us practice our inheritance

/////// 5: Updates to base class
// SimpleVector could use a couple of useful additions to work 
// Copy constructor
// Assignment operator = 

// For your Templates assignment, you will extend these classes and make a SortableVector.
// For this, you'll want to read up on sorting algorithms. https://www.geeksforgeeks.org/sorting-algorithms/#algo
// They can range in difficulty. Some of the easiest are Selection Sort, and Bubble Sort. Merge sort is efficient, and interesting... https://www.youtube.com/watch?v=kPRA0W1kECg

#include <iostream>
#include <assert.h>

template<typename T>
class SimpleVector
{
protected:
	//pointer to array of data
	T* m_pData = nullptr;
	//size of data
	size_t m_size = 0;

public:
	SimpleVector(size_t size)
	{
		m_size = size;

		// allocate new memory of type T with our new size
		m_pData = new T[m_size];
	}

	// Copy constructor. Called when we create based on another
	SimpleVector(const SimpleVector& other)
	{
		delete[] m_pData;
		m_size = other.m_size; // copying this is ok

		m_pData = new T[m_size];

		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = other.m_pData[i];
		}
	}

	// Our destructor should be virtual because we plan to inherit from this class later, and we want this destructor to be called
	virtual ~SimpleVector()
	{
		delete[] m_pData;
	}

	// Returns number of elements allocated
	size_t Size()
	{
		return m_size;
	}

	// Return a reference so that it can be assigned e.g. mySimpleVector[5] = 7;
	T& operator[] (size_t index)
	{
		assert(index >= 0 && index < m_size);
		return m_pData[index];
	}

	//Operator overload for assignment operator '='
	void operator=(const SimpleVector& valueToAssign)
	{
		m_size = valueToAssign.m_size; // copying size is ok

		delete[] m_pData; // we need to clean up the data before we replace it. Don't want to leave orphans... therefore. we DESTROY IT
		m_pData = new T[m_size]; // create a new block of memory for the copy

		//copy all the data!
		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = valueToAssign.m_pData[i];
		}
	}
};



// Stream insertion operator, to make it convenient to print
template<typename T>
std::ostream& operator<<(std::ostream& out, SimpleVector<T>& toPrint)
{
	out << "{";
	for (size_t i = 0; i < toPrint.Size(); i++)
	{
		out << " " << toPrint[i];
	}
	out << "}";

	return out;
}


template <typename T>
class SearchableVector : public SimpleVector<T>
{
public:
	SearchableVector(size_t size) : SimpleVector<T>(size)
	{
	}

	~SearchableVector() override
	{
	}

	// This Find function takes a value, searches for the first matching one in the array, then returns its index.
	// If the value is not found, it returns the size of the array, i.e. the last element index + 1.
	size_t Find(T value)
	{
		// look through every element in the array, in order
		// if it is equal to the value we want, return the index we were just checking at
		for (size_t i = 0; i < this->Size(); i++)
		{
			if (this->m_pData[i] == value)
			{
				return i;
			}
		}

		return this->Size();
	}
};


int main()
{
	//////////// Populating our SimpleVector
	SimpleVector<int> myClassInstance = SimpleVector<int>(8);
	myClassInstance[0] = -10;
	myClassInstance[1] = 0;
	myClassInstance[2] = 10;
	//myClassInstance[3] = 20; // out of range!
	std::cout << "SimpleVector Contents: " << myClassInstance << std::endl;
	////////////

	//////////// Testing our SimpleVector's copy constructor
	// Create another SimpleVector based on the first one
	SimpleVector<int> anotherSimpleVector = myClassInstance;
	myClassInstance[2] = 100; // modify the first one. This should not affect the contents of the first
	std::cout << "SimpleVector Contents: " << myClassInstance << std::endl;
	std::cout << "AnotherSimpleVector Contents: " << anotherSimpleVector << std::endl;
	anotherSimpleVector = myClassInstance;
	std::cout << "AnotherSimpleVector Contents: " << anotherSimpleVector << std::endl;
	////////////

	//////////// Searching our Searchable Vector
	// Populating our SearchableVector
	size_t arraySize = 20;
	SearchableVector<int> mySearchableClassInstance = SearchableVector<int>(arraySize);
	for (int i = 0; i < arraySize; i++)
	{
		mySearchableClassInstance[i] = i * 2;
	}
	// Searching for the index of a given value...
	std::cout << "SearchableVector Contents: " << mySearchableClassInstance << std::endl;
	int valueToFind = 30;
	std::cout << "Index found in SearchableVector while looking for value " << valueToFind << ": " << mySearchableClassInstance.Find(valueToFind) << std::endl;
	//////////// 


	//////////// Testing our SearchableVector's copy constructor
	SearchableVector<int> mySearchableCopy = mySearchableClassInstance;
	mySearchableClassInstance[2] = 100;
	std::cout << "mySearchableClassInstance Contents: " << mySearchableClassInstance << std::endl;
	std::cout << "mySearchableCopy Contents: " << mySearchableCopy << std::endl;
	////////////


	//Ideally, for the Templates assignment, one would be able to extend the size of their SimpleVector however they want...
	// e.g. mySimpleVector.push_back(1) would always work. Would always increase the size of the array... 
	// So if you call push_back() on a SimpleVector of size 4, it will be size 5 after...


	getchar();
}




// When we create a variable of type SimpleVector<int>, the compiler will see that, 
// and generate a new version of SimpleVector automatically with the type int replacing everywhere it said 'T'
// Same with SimpleVector<float>, and so on...

//class SimpleVectorInt
//{
//private:
//	//pointer to array of data
//	int* m_pData;
//	//size of data
//	size_t m_size;
//public:
//
//	SimpleVectorInt(size_t size)
//	{
//		m_size = size;
//
//		// allocate new memory of type T with our new size
//		m_pData = new int[m_size];
//	}
//};
//
//class SimpleVectorFloat
//{
//private:
//	//pointer to array of data
//	float* m_pData;
//	//size of data
//	size_t m_size;
//public:
//
//	SimpleVectorFloat(size_t size)
//	{
//		m_size = size;
//
//		// allocate new memory of type T with our new size
//		m_pData = new float[m_size];
//	}
//};