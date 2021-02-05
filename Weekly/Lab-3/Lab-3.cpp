#include <iostream>

////////////////////////////////////////////////////////////////
// GAME1011 Lab 3
////////////////////////////////////////////////////////////////

/////// Topic: Operator overloading!
//"Overload" means defining a function to replace an existing function in some cases
//https://en.cppreference.com/w/cpp/language/operators

/////// 1: Setup
// Clone repo to get lab 3 code                                                                                                  

/////// 2: overloads inside class    
//Recall Lab 2 Example 2, when we tried to assign a copy of our Document class
//		docMemberwise = doc;
//this actually created a memory leak, because the default assignment operator = copied the data from doc to docMemberwise, which includes the pointer.
//it copied the pointer, not the data, which caused them both to be pointing to the same data. Meanwhile, docMemberwise's old data was "orphaned" meaning no pointers point to it anymore...
//if we overload = we can fix this!
//fix the leak by defining a new member function overload for = so you can do
//		Document1 = Document2
//and get the intuitively expected result

//Note: lvalues & rvalues. What are they? https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c
// Why can't you do... 
//		myInt = 10;
//		5 = myInt;

/////// 3: Type conversion https://en.cppreference.com/w/cpp/language/cast_operator
// Define an implicit/explicit conversion of Document to string so you can do:  
//		Document doc = Document(5, 'w');
//		std::string strConvertedFromDoc = doc
// HINT: operator std::string() const


/////// 4: overloads outside class           
// For some operations like matrix multiplication, rotations, or string concatentions, order matters
// A * B != B * A                 
//Make a string constructor Document(string) to help with the next step
//Overload the + operator to concatenate for two cases:                                         
//1. string + Document (make it return a Document)
//2. Document + string (make it return a Document)
//Hint: Document operator+( const Document& s1, const std::string& s2 )

//Desired behavior: 
//if A is "hello" and B is " world" 
//then A + B should return "hello world"
//B + A should return " worldhello" 
// should be able to print "hello" + <some document here>



class Document
{
private: // Hidden from everyone else!
	char* m_pData; // dynamic array of data. Will be a pointer to the beginning of an array... but it does not know how many there are in the array
	size_t m_size; // how many elements in the array? // size_t is a typedef for another type

public:

	// Copy constructor. Called when we create a Document based on another
	Document(const Document& other)
	{
		CleanupData();
		m_size = other.m_size; // copying this is ok

		// what happens by default; which is not ideal, 
		//and causes lots of issues including our double-delete crash
		//m_pData = other.m_pData; 

		m_pData = new char[m_size];

		//SetAllData(*other.m_pData); // copy the first element of other into all of ours.... which is technically ok for now, but not ideal
		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = other.m_pData[i];
		}
	}

	//Constructs a document with its data filled out with size copies of data
	Document(size_t size, char data)
	{
		// let us know how many elements our array will have
		m_size = size;

		// the "new[]" keyword says to find some space to put new data, then return the address of the first element.
		// in this case, we are looking for space for allocating new memory for "size" number of char data types
		// This creates a block of memory that is the size of one element (char) 
		// multiplied by the number of elements (size)
		// The block of memory is stored somewhere else. It doesn't live with the class. It has a different lifetime. 
		// Instead, we just get a pointer to the place it is stored.
		m_pData = new char[size];

		SetAllData(data);
	}

	void CleanupData()
	{
		//std::cout << "Deleting " << m_pData << std::endl;
		delete[] m_pData;
		m_pData = nullptr;
		m_size = 0;
	}

	size_t Size() const // const after the function means it is guaranteed not to modify anything
	{
		return m_size;
	}

	char GetDataAtIndex(size_t index) const
	{
		return m_pData[index];
	}

	// Sets all the data in the whole array to be the same...
	void SetAllData(char data)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = data;
		}
	}

	~Document()
	{
		CleanupData();
	}

	///////////////////////////////////////////////////////
	// Lab 3 code
	///////////////////////////////////////////////////////


	//Operator overload for assignment operator '='
	void operator=(const Document &valueToAssign)
	{
		// When we use = we want to assign the left side to have the data of the right side.
		// So, a document A with "Hello" can be assigned the value of document B with "Hi"
		// Then, A would have "Hi"
		// We should also be able to change B without changing A.
		// If we then reassign B to "Howdy" we do NOT expect A to also say "Howdy". We expect it to still say "Hi"

		// char* m_pData; 
		// size_t m_size;

		//What normally happens in =
		//m_pData = valueToAssign.m_pData; // this is not ok for us. We don't want a copy of the pointer. We want a copy of the data
		m_size = valueToAssign.m_size; // copying size is ok

		delete[] m_pData; // we need to clean up the data before we replace it. Don't want to leave orphans... therefore. we DESTROY IT
		m_pData = new char[valueToAssign.m_size]; // create a new block of memory for the copy

		//copy all the data!
		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = valueToAssign.m_pData[i];
		}

	}


	// Type Conversion from Document to std::string
	operator std::string() const
	{
		std::string convertedString;
		convertedString.resize(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			convertedString[i] = m_pData[i];
		}

		return convertedString;
	}

	// Constructor of document with string, also serves as type conversion
	Document(const std::string &value)
	{
		m_size = value.length();
		m_pData = new char[m_size];

		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = value[i];
		}
	}

	void operator +=(const std::string& rhs)
	{
		// Solution A: copy everyithing!

		//copy our old data
		std::string oldData = static_cast<std::string>(*this);
		CleanupData(); // clear memory

		//make new space for larger size (size of both combined)
		m_size = oldData.length() + rhs.length();
		m_pData = new char[m_size];
		
		// add in old data
		for (size_t i = 0; i < oldData.length() ; i++)
		{
			m_pData[i] = oldData[i];
		}

		// add in new data
		for (size_t i = 0; i < rhs.length(); i++)
		{
			m_pData[i + oldData.length()] = rhs.at(i);
		}

	}

}; // End of Document

Document operator+(const std::string &lhs, const Document &rhs)
{
	std::string concatenated = lhs + static_cast<std::string>(rhs);
	return static_cast<Document>(concatenated);
}

Document operator+(const Document &lhs, const std::string& rhs)
{
	std::string concatenated = static_cast<std::string>(lhs) + rhs;
	return static_cast<Document>(concatenated);
}

std::ostream& operator<<(std::ostream& out, Document& toPrint)
{
	return out << static_cast<std::string>(toPrint);
}



class DocumentReader
{
public:
	// static means the function cannot be called on an instance of the class, instead it belongs to the class itself. It also means no 'this' pointer
	static void PrintDocumentToConsole(const Document& docToPrint)
	{
		for (size_t i = 0; i < docToPrint.Size(); i++)
		{
			std::cout << docToPrint.GetDataAtIndex(i) << " ";
		}

		std::cout << std::endl;
	}
};


int main()
{
	// Example of Double-Delete problem
	//int* aPtr = new int(50);
	//int* bPtr = new int(40);
	//std::cout << "address of a: " << aPtr << std::endl;
	//std::cout << "address of b: " << bPtr << std::endl;

	//std::cout << "assigning b the value of a" << std::endl;
	//bPtr = aPtr;
	//// what happened to the data at b? It's leaked. Gone. "Orphaned"

	//std::cout << "address of a: " << aPtr << std::endl;
	//std::cout << "address of b: " << bPtr << std::endl;

	//std::cout << "deleting a" << std::endl;
	//delete aPtr; // free the memory at a's pointed address so other applications can use it.
	//aPtr = nullptr;
	//delete aPtr; // deleting nullptr is ok.

	//std::cout << "deleting b" << std::endl;
	//delete bPtr; // deleting already deleted memory is NOT OK because someone else might be using it
	//bPtr = nullptr;

	
	{
		Document doc(16, 'L');
		std::cout << "\nContents of doc at creation" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// copy constructor not called here! This is the parametrized Constructor. In this one we are allocating new memory...
		Document docMemberwise(10, 'Q');
		std::cout << "\nContents of docMemberwise at creation" << std::endl;
		DocumentReader::PrintDocumentToConsole(docMemberwise);

		docMemberwise = doc;
	
		std::cout << "\nAssigning data in doc (but NOT docMemberwise)..." << std::endl;

		doc.SetAllData('g');
		std::cout << "\nContents of doc" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// Changing the data to 'g's in doc also changes the data to 'g's in docMemberwise, since they are pointing to the same thing.
		// In some cases that could be desired. But in this case, maybe not...
		std::cout << "\nContents of docMemberwise" << std::endl;
		DocumentReader::PrintDocumentToConsole(docMemberwise);

		getchar(); // "wait for user to enter any character". It returns the character entered, but can also be used similar to System("Pause")
	}

	{
		std::cout << "\n======= Example: Conversion ========" << std::endl;
		Document doc = Document(15, 'w');

		// assignment operator for string = Document does not exist.
		// compiler looks for alternatives. It finds it can do string = string, and it finds that it can convert doc to string!
		// So it assumes that is what we mean. This is called an implicit cast
		std::string strConvertedFromDoc = static_cast<std::string>(doc);

		// we know we can cout a string. That means std::string has an overload for the << operator
		std::cout << strConvertedFromDoc << std::endl;
	}

	{
		std::cout << "\n======= Example: Overloading + ========" << std::endl;
		Document doc = Document(3, 'n');

		std::string toConcatenate = "wi";

		std::cout << static_cast<std::string>(toConcatenate + doc) << std::endl;

		std::cout << "\n======= Example: Overloading += ========" << std::endl;

		Document doc2 = Document("hello ");
		doc2 += "world";

		std::cout << static_cast<std::string>(doc2) << std::endl;


		std::cout << "\n======= Example: Overloading << ========" << std::endl;
		std::cout << doc2 << std::endl;


		//Print numbers 0-9
		int i = 0;
		while (i < 10);
		{
			std::cout << i << std::endl;
			i++;
		}

	}

	getchar();
}