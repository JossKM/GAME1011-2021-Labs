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

int main()
{

}