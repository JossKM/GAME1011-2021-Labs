////////////////////////////////////////////////////////////////
// GAME1011 Lab 11
////////////////////////////////////////////////////////////////

/////// Topic: STL Lists
// https://www.cplusplus.com/reference/vector/vector/
// https://www.cplusplus.com/reference/list/list/
// https://www.cplusplus.com/reference/forward_list/forward_list/
// https://www.bigocheatsheet.com/
// Wallace's lab video, explaining how to create your own singly linked list class https://youtu.be/KtcpDbIKEVY

/////// Keywords to note
/*
Time Complexity
Singly Linked List
Doubly Linked List
Array List
Lambda Expression
*/

/////// Lab activities
// This lab, we will explore the performance of different implementations of Lists in the Standard Template Library (STL). 
// This is complementary to Wallace's Lab video, and could let you test your custom class against the STL version

/////// 1: Setup
// Clone the repo (https://github.com/JossKM/GAME1011-2021-Labs), set this Lab as "Startup Project", or start a new project with a main function                                                                                     

/////// 2: Create a function which uses <chrono> to time several executions of another function
// A cool and scalable way to do this is with Lambda expressions, allowing you to re-use the same timer function to time arbitrary expressions
// You could also achieve this effect with preprocessor directives, namely #define

/////// 3: Develop a testing application which lets us analyze the performance of different data structures
// Test the time it takes to:
//      -Insert an element at the beginning
//      -Insert an element at random
//      -Access an element at the beginning
//      -Access an element at random
// It should have configurable numbers for:
// Number of tests to average out for each function
// Number of elements to put in containers
// Number of different sizes to try out for containers

/////// 4: Format outputs to the console
// You can use std::setw(), std::left and std::right from <iomanip>, or print using printf

/////// 5: Configure our build settings for testing
// To get accurate results, we need to configure our build settings to NOT optimize our code out!

/////// 6: Run the tests!
// Try the largest sizes you can get without running out of memory

/////// X: Make your own tests
// Within the test framework, you may make adjustments and see what changes they have. For example, emplace_back versus push_back
// You can use this to test your own container classes or functions for different input numbers


#include <iostream>
#include <iomanip>
#include <vector> // array list
#include <list> // doubly linked list
#include <chrono> // for precision timing

using namespace std;

#define TEST_TYPE char
#define N 100000000
#define NUM_TRIALS 10000
vector<TEST_TYPE> TestVector;
list<TEST_TYPE> TestList;

// This function is intended to take a Lambda Expression, allowing us to time any block of code we want
template<typename TLambda>
double ExecutionTimeOf(TLambda func)
{
	chrono::high_resolution_clock::time_point begin;
	chrono::high_resolution_clock::time_point end;
	begin = chrono::high_resolution_clock::now();
	for (size_t i = 0; i < NUM_TRIALS; i++)
	{
		func();
	}
	end = chrono::high_resolution_clock::now();
	chrono::nanoseconds duration = end - begin;
	return duration.count() / (double)NUM_TRIALS;
}

#define PrintTime(Lambda) cout << setw(16) <<  ExecutionTimeOf(Lambda)

int main()
{
	TestVector = vector<TEST_TYPE>(N, TEST_TYPE());
	TestList = list<TEST_TYPE>(N, TEST_TYPE());
	// Seeding with time
	size_t randomSeed = chrono::high_resolution_clock::now().time_since_epoch().count();


	cout << "Comparing random access of a vector with random access of a list" << endl;

	// Call Srand with the SAME seed for both functions because we want to compare
	srand(randomSeed);
	// Insert a Lambda expression into ExecutionTimeOf
	PrintTime([] {
		size_t randIndex = rand();
		TestVector[randIndex % N];
	});

	srand(randomSeed);
	PrintTime([] {
		size_t randIndex = rand();
		auto iterator = TestList.begin();
		advance(iterator, randIndex % N);
	});



	cout << endl << "Comparing random insertion of a vector with a list" << endl;

	srand(randomSeed);
	PrintTime([] {
		size_t randIndex = rand();
		auto iterator = TestVector.begin();
		advance(iterator, randIndex % N);
		TestVector.insert(iterator, 'c');
	});

	srand(randomSeed);
	PrintTime([] {
		size_t randIndex = rand();
		auto iterator = TestList.begin();
		advance(iterator, randIndex % N);
		TestList.insert(iterator, 'c');
	});
}