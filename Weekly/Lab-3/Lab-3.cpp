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
	}

};


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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Example 2: memberwise copy (assignment operator) with a memory leak and funky behaviour
	{
		std::cout << "\n======================== Example: Memberwise Assignment (MEMORY LEAK) ========================\n" << std::endl;

		Document doc(16, 'L');
		std::cout << "\nContents of doc at creation" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// copy constructor not called here! This is the parametrized Constructor. In this one we are allocating new memory...
		Document docMemberwise(10, 'Q');
		std::cout << "\nContents of docMemberwise at creation" << std::endl;
		DocumentReader::PrintDocumentToConsole(docMemberwise);

		// This is memberwise assignment. Not a constructor!
		// C++ doesn't think it needs new memory for new Documents
		// It's trying to just copy them in place using the default behaviour of the assignment operator '=' 
		docMemberwise = doc;
		// Now, docMemberwise's m_pData pointer is a copy of doc's m_pData pointer. They point to the same data.
		// docMemberwise's old pointer is gone, which means the memory it used to point to (all the 'Q')s are lost as well.
		// Even though nobody knows where the Q's are stored anymore, your computer also doesn't know it's free to use
		// Those Q's are now taking up space in RAM, even though nobody can use them or delete them
		// this is a memory leak
		// Fixes for the leak could be... 
				//A: override the assignment operator '=' to do what we expect instead, and make sure there are no memory leaks
				//B: don't use the assignment operator (not ideal, since anyway may accidentally use it and create a leak)
				//C: refactor the Document class to use something safer than a raw pointer, like a Smart Pointer

		std::cout << "\nAssigning data in doc (but NOT docMemberwise)..." << std::endl;

		// If we modify the data in doc, we are telling it to change the stuff at the address its m_pData pointer points to.
		doc.SetAllData('g');
		std::cout << "\nContents of doc" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// Changing the data to 'g's in doc also changes the data to 'g's in docMemberwise, since they are pointing to the same thing.
		// In some cases that could be desired. But in this case, maybe not...
		std::cout << "\nContents of docMemberwise" << std::endl;
		DocumentReader::PrintDocumentToConsole(docMemberwise);

		//doc.CleanupData(); // we can clean up the memory that doc and docMemberwise point to: the 'g's
		// but we can never clean up the memory we already leaked. Those 'Q's are gone forever

		getchar(); // "wait for user to enter any character". It returns the character entered, but can also be used similar to System("Pause")
	}
	getchar();
}