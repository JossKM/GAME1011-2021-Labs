////////////////////////////////////////////////////////////////
// GAME1011 Lab 13
////////////////////////////////////////////////////////////////

/////// Topic: Exceptions and Debugging

/////// Keywords to note
/*
Exceptions
try-catch
throw

Debugging
breakpoints
watch
call stack
pointer addresses
hexadecimal values
*/

/////// Lab activities
// This lab, we will improve some existing code by fixing bugs in it, and adding additional layers of safety through the use of exceptions

/////// 1: Setup
// Clone the repo (https://github.com/JossKM/GAME1011-2021-Labs), set this Lab as "Startup Project", or start a new project with a main function                                                                                     

/////// 2: Run the program

/////// 3: Panic
// It's buggy!

/////// 4: Investigate
// It's buggy... but why?
// Your tools include the error and output windows, the call stack, breakpoints, watches, print statements and commenting/uncommenting code
// Beware of places where the comments are misleading, or where you are making assumptions that may not be true. Does the "Resize(int)" function do what you think it does?

/////// 5: Fix/Baby-proof
// Implement robust fixes that will make the erroneous states impossible, or at least make it clear what has gone wrong if it happens again. Throwing Exceptions can help with this!

#include "Lab-13.h"
#include <time.h>

using namespace std;
#define N 1000

int main()
{
    srand(time(0));
    SimpleVector<string> myVec(0);
    SimpleVector<string> myVec2(0);

    cout << "Press any key to start the specific push/pop test" << endl;
    getchar();


    myVec.push_back("0"); // {0}
    myVec.pop_back(); // {}
    myVec.pop_back(); // {}
    myVec.push_back("1"); // {1}
    myVec.push_back("2"); // {1, 2}
    myVec.pop_back(); // {1}
    myVec.pop_back(); // {}
    cout << myVec << "<- This should be {}" << endl;


    cout << "Press any key to start the large push() test" << endl;
    getchar();

    for (int i = 0; i < N; i++)
    {
        myVec.push_back(to_string(i));
    }
    cout << myVec << "<- This should contain integers fron 0 to (N - 1)" << endl;
    cout << "Press any key to start the large pop() test" << endl;
    getchar();
    
    for (int i = 0; i < N; i++)
    {
        myVec2.push_back(myVec.pop_back());
    }
    cout << myVec << "<- This should be empty now" << endl;
    cout << myVec2 << "<- This should contain every element, but reversed" << endl;




    cout << "Press any key to start the random push/pop test" << endl;
    getchar();

    for (int i = 0; i < N; i++)
    {
        system("cls");
        if (rand() % 2)
        {
            myVec.push_back(to_string(i));
        }
        else
        {
            myVec.pop_back();
        }

        cout << myVec << endl;
    }


    cout << "Congratulations on not crashing!" << endl;
    getchar();
}
