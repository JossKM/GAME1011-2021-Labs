////////////////////////////////////////////////////////////////
// GAME1011 Lab 5
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
#include <vector>

struct Vector2
{
    float x;
    float y;
};

// Vector + Vector
Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{ lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2{ lhs.x - rhs.x, lhs.y - rhs.y };
}

//single operand means it needs to belong in a class
//two operands and it can live on its own
Vector2 operator*(const Vector2& lhs, const float& rhs)
{
    return Vector2{ lhs.x * rhs, lhs.y * rhs };
}

std::ostream& operator<<(std::ostream& out, Vector2& toPrint)
{
    return out << "(" << toPrint.x << "," << toPrint.y << ")";
}

//float Lerp(float start, float end, float t)
//{
//    float interpolatedValue = start + ((end - start) * t);
//    return interpolatedValue;
//}

//Assumes that start and end are the same type
//Assumes SomeType has an implementation for +, -, and * float
template<typename SomeType>
auto Lerp(SomeType start, SomeType end, float t)
{
    auto interpolatedValue = start + ((end - start) * t);
    return interpolatedValue;
}

//At compile-time, the compiler will look at all the types being fed into different 
//calls of this function, and create new versions of the function written with those types
//for example, if you call Lerp with ints anywhere in the code, the compiler will generate this...
//int Lerp(int start, int end, float t)
//{
//    int interpolatedValue = start + ((end - start) * t);
//    return interpolatedValue;
//}


int main()
{
    // Lerping some doubles
    std::cout << Lerp(0.0, 1.0, 0.0) << std::endl; // 0
    std::cout << Lerp(0.0, 1.0, 0.5) << std::endl; // 0.5
    std::cout << Lerp(10.0, 20.0, 0.5) << std::endl; // 
    std::cout << Lerp(0.0, 100.0, 0.75) << std::endl; //

    // Lerping some ints
    int aInt = 50;
    int bInt = 200;
    std::cout << Lerp(aInt, bInt, 0.75) << std::endl; //

    // Lerping some vectors (a custom class)
    Vector2 myVecA = {0, 10};
    Vector2 myVecB = { 10, 0 };
    auto result = Lerp(myVecA, myVecB, 0.75); // auto keyword can be used to replace the type name if you don't know or care what type you are dealing with. Generally don't use it unless you have to because it makes code less legible
    std::cout << result << std::endl; //

    // Now a discussion about vectors...
    {
        // std::vector is not to be confused with our spatial vectors from linear algebra
        // an std::vector is an implementation of an Array List. It's a List, made with an array
        // std::vector is a template class. You must specify what type it will use when making one
        // in this case, we make an std::vector to hold our type, Vector2
        std::vector<Vector2> myListOfVectors;

        //You can add to the end with 
        myListOfVectors.push_back(myVecA); // {myVecA}
        myListOfVectors.push_back(myVecB); // {myVecA, myVecB}
        myListOfVectors.push_back(result); // {myVecA, myVecB, result}

        myListOfVectors[2]; // index 2 would be the accessing the third element
        
        // pop_back just removes one off the end... 
        myListOfVectors.pop_back(); // {myVecA, myVecB}

        myListOfVectors.size(); // size returns number of elementsa
    }
}