////////////////////////////////////////////////////////////////
// GAME1011 Lab 4
////////////////////////////////////////////////////////////////

/////// Topic: Inheritance and Polymorphism
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
// Clone the repo, set Lab 4 as "Startup Project", or start a new project with a main function                                                                                     

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
	int* m_pSomeData;

public:
	GameActor(std::string a_name)
	{
		m_name = a_name;
		m_pSomeData = new int[3];
	}

	// virtual signals that the function can be dynamically linked. 
	// Meaning it is determined which function to call at runtime (polymorphism!)
	virtual void Update()
	{
		std::cout << GetName() << " (GameActor)" << std::endl;
	}

	std::string GetName()
	{
		return m_name;
	}

	virtual ~GameActor()
	{
		std::cout << "Destructor for GameActor" << std::endl;
		delete[] m_pSomeData;
	}
};


// This will be an abstract class... otherwise known as an Interface
class Drawable
{
public:
	virtual void Draw() = 0; // This is an abstract function. It has no implementation. Also called "Pure virtual"
};


//public inheritance: inherit public members
//protected inheritance: inherit public and protected
class GameActorDrawable : public GameActor, public Drawable
{
private:
	//Sprite??
	//Position??
	char* m_pRawImageData;

public:
	GameActorDrawable(std::string a_name) : GameActor(a_name)
	{
		// pretend we are loading image data here...
		m_pRawImageData = new char[10000];
	}

	void Update() override
	{
		std::cout << GetName() << " (Drawable)" << std::endl;
		//calling base class functionality from a child class
		GameActor::Update();
	}

	void Draw() override
	{
		std::cout << GetName() << " [(O _ O)]" << std::endl;
	}

	~GameActorDrawable() override
	{
		std::cout << "Destructor for GameActorDrawable" << std::endl;
		delete[] m_pRawImageData;
	}
};

// maybe a class which can be drawn
// maybe a player class with a different update()
// maybe a bullet class with a special update
// What about an enemy class?

int main()
{
	const int kNumGameActorsMax = 50000;


	GameActor* world[kNumGameActorsMax] = {nullptr};

	world[0] = new GameActor("Luke");
	world[1] = new GameActor("Darth Vader");
	world[2] = new GameActorDrawable("Obi-Wan");

	std::cout << "Press any key to instantiate 40,000 GameActorDrawables and place them in our world" << std::endl;
	getchar();

	//Let's make things crazy by instantiating a LOT of new objects...
	//Hint: See memory usage with Debug -> Windows -> Show Diagnostic Tools
	//https://docs.microsoft.com/en-us/visualstudio/profiling/memory-usage?view=vs-2019
	for (int iDrawable = 0; iDrawable < 40000; iDrawable++)
	{
		// Find the first empty slot
		for (int i = 0; i < kNumGameActorsMax; i++)
		{
			// If the slot is empty...
			GameActor* pActor = world[i];
			if (pActor == nullptr)
			{
				// Add a new GameActorDrawable to it!!!
				pActor = new GameActorDrawable("C3PO # " + iDrawable);
				world[i] = pActor;
			}
		}
	}

	std::cout << "Press any key to Update and Draw everything in our world" << std::endl;
	getchar();

	//Update everything in the world
	for (int i = 0; i < kNumGameActorsMax; i++)
	{
		// make sure we only update items that exist
		GameActor* pActor = world[i];
		if (pActor == nullptr)
		{
			continue;
		}
		
		// When we call Update() on a GameActor pointer, 
		// and it dynamically chooses different child class Update behaviour, this is called Polymorphism
		pActor->Update();
	}

	//Draw everything
	for (int i = 0; i < kNumGameActorsMax; i++)
	{
		// make sure we only update items that exist
		GameActor* pActor = world[i];

		// Try to convert to Drawable. This is a dynamic cast. If it fails, it will be nullptr
		// () is the least specific type of type cast. It will try everything
		// static_cast is the safest, but doesn't work if you want polymorphism
		// dynamic_cast works for polymorphism https://en.cppreference.com/w/cpp/language/dynamic_cast

		GameActorDrawable* pDrawable = dynamic_cast<GameActorDrawable*>(pActor);

		// If the cast did not work, or pActor was null to begin with... do not do anything!
		if (pDrawable == nullptr)
		{
			continue;
		}

		pDrawable->Draw();
	}

	std::cout << "Press any key to delete everything in our world" << std::endl;
	getchar();

	//////////////////////////////////////////////////////////////////////

	// Delete everything!
	for (int i = 0; i < kNumGameActorsMax; i++)
	{		// make sure we only update items that exist
		GameActor* pActor = world[i];
		if (pActor == nullptr)
		{
			continue;
		}

		delete pActor; // Note: this will call the destructor of the class it points to
		// If the destructor is not marked virtual and we call delete on a GameActor pointer to a GameActorDrawable object,
		// it will not know to call the destructor in GameActorDrawable, which could cause a memory leak!
	}


	std::cout << "Press any key to say goodbye" << std::endl;
	getchar();

	return 0;
}