
////////////////////////////////////////////////////////////////
// GAME1011 Lab 3
////////////////////////////////////////////////////////////////

/////// Topic: Inheritance and Polymorphism
//"Inheritance" means making a class which
//https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
//https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
//https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm

/////// Keywords to note
/*
class
abstract
virtual
final
override
pure virtual
public/private/protected data member access specifiers
public/private/protected inheritance access specifiers
interface
polymorphism
virtual destructor
*/

/////// Lab activities

/////// 1: Setup
// Clone the repo, set Lab 4 as "Startup Project", or start a new project with a main function and an empty class                                                                                           

/////// 2: Plan Your Heirarchy
// Why do you need inheritance?
// Having a parent (or base) and child classes can:
// 1. Avoid repeating work where multiple classes have identical data members and functions
// 2. Allow you to have a container of base class pointers which may point to different child class instances

/////// 3: Create a parent class
// Add some data members and functions. We can make a GameActor class with a name member and a Update() function

/////// 4: Populate a container of parent class pointers
// Make a container with parent class pointers, call a function on them

/////// 5: Inherit
// Create some child classes to inherit public data members and functions
// Use public inheritance

/////// 6: Constructing child instances
// Create some custom constructors
// You can call base class functionality
// Use the constructors to instantiate some child classes and assign them as elements in the container

/////// 7: Override
//In a child class, override some functionality from a parent class
//Use the keyword 'virtual' in the base class function, and the keyword 'override' in the child class function

/////// 8: Destroy
// If you instantiated classes with new, you must delete them!
// However, just as you must use the 'virtual' to dynamically bind to a member function, 
// you must also do the same to dynamically bind the destructor!
// Any time you intend to delete a base class pointer, you need a virtual destructor!
// If you have a base class with a dynamically allocated data member A, you may add "delete" in its destructor. 
// ... But if you have a child class with a dynamically allocated data member B, 
// ... then you call a calling delete on a base class pointer to a child class object
// ... this may leave the data member B leaked, since the base class does not know about B
// ... The base class only knows about A, and only knows to free the memory associated with A. Not B
// https://www.learncpp.com/cpp-tutorial/virtual-destructors-virtual-assignment-and-overriding-virtualization/

////////////////////////////////////////////////////////////////

#include <iostream>

class GameActor
{
private:
	std::string m_name;

public:
	void Update();
};

int main()
{
	return 0;
}