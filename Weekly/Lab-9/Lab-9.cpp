////////////////////////////////////////////////////////////////
// GAME1011 Lab 9
////////////////////////////////////////////////////////////////

/////// Topic: File I/O
// http://www.cplusplus.com/reference/fstream/fstream/
// http://www.cplusplus.com/reference/iolibrary/
// https://en.cppreference.com/w/cpp/error/errno_macros

/////// Keywords to note
/*
exception
format flags
streams
stream insertion operator, stream extraction operator
*/

/////// Lab activities
// This lab, we will create an application which can open and edit different types of files.

/////// 1: Open and print a text File
// Try printing File1.txt 

/////// 2: Create and write to a text File
// Try writing to a new file

/////// 3: Design your own file format to save and load!
// Simplest to store each piece of data in its own line
// Try storing some string data with spaces, and some numerical data
// E.g. 
// <Name>
// <Age>
// <Address>
// You can even come up with your own file extension. It does not have to be txt. Pick anything you want!

/////// 4: Save/Load a struct as a binary File
// A struct or class in C++ is guaranteed to contain its data members in sequential order based on their declaration. 
// You can actually just save and load the instance data as it is in computer memory
// This involves treating it as just a bunch of bytes (which happens to be the size of char)
// For large data, this can save a lot of work that would be spent parsing each data member
// Binary files will no longer be human readable

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int ReadAndPrint(const char* filename)
{
	ifstream myFileStream;
	myFileStream.open(filename);

	if (!myFileStream.is_open())
	{
		char errorMessage[256];
		strerror_s(errorMessage, errno);
		cerr << "Failed to open file: " << filename << ": " << errorMessage;
		return -1;
	}

	const int MAX_CHARS_PER_LINE = 256;
	while (!myFileStream.eof())
	{
		char lineContents[MAX_CHARS_PER_LINE];
		myFileStream.getline(lineContents, MAX_CHARS_PER_LINE);

		if (myFileStream.fail())
		{
			cerr << "Error: something went wrong reading line by line in file: " << filename;
			return -2;
		}

		cout << lineContents << endl;
	}

	return 0;
}

int OpenAndWrite(const char* filename)
{
	fstream file;
	file.open(filename, fstream::out);

	int age;
	string name;
	string address;
	string ageStr;

	cout << "Hello! What is your name?" << endl;
	getline(cin, name);
	cout << "What is your age?" << endl;
	getline(cin, ageStr);
	cout << "What is your address?" << endl;
	getline(cin, address);

	age = stoi(ageStr);
	file << name << endl
		<< age << endl
		<< address << endl;


	file.close();
	return 0;
}

struct SomeData
{
	int data[3];
};

int OpenBinary(const char* filename)
{
	fstream file;
	// Create the file if it does not exist
	file.open(filename, fstream::out | fstream::app);
	file.close();

	file.open(filename, fstream::in | fstream::binary);

	SomeData myData = {-1};
	// char is the size of one byte
	char* rawDataPointer = (char*)&myData;

	file.read(rawDataPointer, sizeof(myData));
	for (int i = 0; i < 3; i++)
	{
		cout << myData.data[i] << " ";
	}
	cout << endl;
	file.close();

	cout << "enter first element" << endl;
	cin >> myData.data[0];
	cout << "enter second element" << endl;
	cin >> myData.data[1];
	cout << "enter third element" << endl;
	cin >> myData.data[2];

	/// Open for writing to file
	file.open(filename, fstream::out | fstream::beg | fstream::binary);
	file.write(rawDataPointer, sizeof(myData));
	file.close();
	return 0;
}

int main()
{
	//ReadAndPrint("MyAssets/File1.txt");
	//OpenAndWrite("MyAssets/File2.txt");
	OpenBinary("MyAssets/TheCoolestFile.cool");
}