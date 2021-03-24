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
// Clone the repo, set this Lab as "Startup Project", or start a new project with a main function                                                                                     

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

int main()
{
   
}