////////////////////////////////////////////////////////////////
// GAME1011 Lab 4
////////////////////////////////////////////////////////////////

/////// Topic: Template Functions
// https://en.cppreference.com/w/cpp/language/template_metaprogramming
// https://en.cppreference.com/w/cpp/language/template_specialization

/////// Keywords to note
/*
template
typename
auto
"T"
"Template meta-programming"
*/

/////// Lab activities
// This lab, we will be writing code which can work without specifying the types it is working with!

/////// 1: Setup
// Clone the repo, set this Lab as "Startup Project", or start a new project with a main function                                                                                     

/////// 2: Make a Linear Interpolation (Lerp) function 
// This function should take three inputs, A, B, and t, 
// where A and B are the same type, and t is some kind of floating-point type, such as float or double
// The function should return the linear interpolation between A and B using a weight of t, 
// The function should satisfy that Lerp(A,B,0) = A, and Lerp(A,B,1) = B. Lerp(A,B,0.5) should result in "equal weights of A and B"
// The return type of the function should be the same as the type of A and B

/////// 2: Test the Lerp function on some floats
// Do some basic tests to ensure the Lerp is working correctly.

/////// 3: Make a simple Vector2 class
// Add some basic operations
// Vector2 + Vector2
// Vector2 * float

/////// 4: Turn the Linear Interpolation (Lerp) function into a template function
// Not every variable needs to be changed...

/////// 5: Test the Lerp function on some Vector2
// The same Lerp function, without any overloads, should work for
// floats, doubles, Vector2, and anything else you throw at it which has a meaningful addition and multiplication by scalar operator

// That's it!

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}