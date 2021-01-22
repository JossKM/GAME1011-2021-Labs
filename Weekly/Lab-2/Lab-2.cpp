#include <iostream>

////////////////////////////////////////////////////////////////
// GAME1011 Lab 2
////////////////////////////////////////////////////////////////

// Dynamic Arrays
// new[]
// delete[]
// const
// this
// Memberwise Copy
// Copy Constructor

// Let's make a "Document" class
// A separate class, "Document Reader" will be used to interface with the document
// Document Reader will just need to print the data
// The App won't actually feature save/load or editing functionality
// We may want to be able to copy documents--to be able to save different versions

class Document
{
private: // Hidden from everyone else!
	char* m_pData; // dynamic array of data. Will be a pointer to the beginning of an array... but it does not know how many there are in the array
	size_t m_size; // how many elements in the array? // size_t is a typedef for another type

public:
	Document()
	{
		std::cout << "Document Default Constructor " << this << std::endl;
	}

	// Copy constructor. Called when we create a Document based on another
	Document(Document& other)
	{
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
		std::cout << "Document Parametrized Constructor " << this << std::endl;
		// pointer holds an address to some data in memory. It's just a number.
		std::cout << "size of our pointer " << sizeof(m_pData) << std::endl;
		// our size variable is an unsigned int of some kind.
		std::cout << "size of our \"size counter\" " << sizeof(m_size) << std::endl;


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

	void Cleanup()
	{
		//std::cout << "Deleting " << m_pData << std::endl;
		delete[] m_pData;
		m_pData = nullptr;
		m_size = 0;
	}

	// Destructor
	~Document()
	{
		//std::cout << "Document Destructor " << this << std::endl;
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Example 1: Crating and printing a document normally
	{
		std::cout << "\n======================== Example 1: Constructing and Printing ========================\n" << std::endl;

		// Declaring and constructing an instance of Document. C++ knows it needs to create space for a "Document". 
		// It will reserve space for Document's members... which are m_pData and m_size
		Document doc(1000, 'L'); // create document. This constructor contains a call to the "new[]" keyword.
		// Generally, we actually prefer not to have the "new" keyword in a constructor because it increases the...
		// likelihood of a programmer allocating memory by accident without knowing. In example 2 you can see how easily that can happen.

		//sizeof tells us how much space something takes up, in bytes
		std::cout << "size of object instance doc in bytes is... " << sizeof(doc) << std::endl;

		// Call the static function PrintDocumentToConsole on the class DocumentReader, and pass in doc as a parameter.
		// 'static' lets us call it on the class itself instead of on an instance of it. We never had to create a DocumentReader variable
		
		std::cout << "\nContents of doc at creation (specifically, the memory pointed to by doc's m_pData):" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// Even though the size of doc is 8, the size of the data doc's m_pData points to is much larger
		// These data need to be released manually when we are done with it with delete[] because we allocated it with new[]
		doc.Cleanup(); // free memory that was allocated for the 'L's 

		getchar(); // "wait for user to enter any character". It returns the character entered, but can also be used similar to System("Pause")
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Example 2: memberwise copy (assignment operator) with a memory leak and funky behaviour
	{
		std::cout << "\n======================== Example 2: Memberwise Assignment (MEMORY LEAK) ========================\n" << std::endl;

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

		std::cout << "\nAssigning data in doc\n" << std::endl;

		// If we modify the data in doc, we are telling it to change the stuff at the address its m_pData pointer points to.
		doc.SetAllData('g');
		std::cout << "\nContents of doc" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// Changing the data to 'g's in doc also changes the data to 'g's in docMemberwise, since they are pointing to the same thing.
		// In some cases that could be desired. But in this case, maybe not...
		std::cout << "\nContents of docMemberwise" << std::endl;
		DocumentReader::PrintDocumentToConsole(docMemberwise);

		doc.Cleanup(); // we can clean up the memory that doc and docMemberwise point to: the 'g's
		// but we can never clean up the memory we already leaked. Those 'Q's are gone forever

		getchar(); getchar(); // "wait for user to enter any character". It returns the character entered, but can also be used similar to System("Pause")
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Example 3: Copy Constructor
	{
		std::cout << "\n======================== Example 3: Copy Constructor ========================\n" << std::endl;

		Document doc(16, 'L');
		std::cout << "\nContents of doc at creation" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// copy constructor is called here, because we are declaring and initializing docCopy in one line using doc
		Document docCopy = doc; // Both should be 5 Ls 

		std::cout << "\nAssigning data in doc\n" << std::endl;

		// If we modify the data in doc, we are telling it to change the stuff at the address its m_pData pointer points to.
		doc.SetAllData('g');
		std::cout << "\nContents of doc" << std::endl;
		DocumentReader::PrintDocumentToConsole(doc);

		// After modifying doc, we can see that docCopy wasn't modified as well, which is different from what we saw in Example 2
		std::cout << "\nContents of docCopy" << std::endl;
		DocumentReader::PrintDocumentToConsole(docCopy);

		// now we have 2 to clean up
		doc.Cleanup();
		docCopy.Cleanup();

		getchar(); getchar(); // "wait for user to enter any character". It returns the character entered, but can also be used similar to System("Pause")
	}

	return 0;
}