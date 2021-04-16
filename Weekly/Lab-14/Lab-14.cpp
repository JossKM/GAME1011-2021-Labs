////////////////////////////////////////////////////////////////
// GAME1011 Lab 14
////////////////////////////////////////////////////////////////

/////// Topic: Representation of numbers and bitwise operations

/////// Keywords to note
/*
Two's complement
bitwise operators &, |, ~, ^
big-endian vs. little-endian
decimal, binary, hexadecimal
bit, byte
bitshifting operators << >>
bit masking
*/

/////// Lab activities
// This lab, we will look at how signed and unsigned integer values are stored in memory and test some bitwise operations on them

/////// 1: Setup
// Clone the repo (https://github.com/JossKM/GAME1011-2021-Labs), set this Lab as "Startup Project", or start a new project with a main function                       

/////// 2: Allocate some dynamic memory
// Use new[] to allocate a dynamic array of memory, so we can examine its structure
// Set the memory to specific numbers you know e.g. 0, 1, 5, 365, 100, 256...
// new returns a pointer. Be sure to save it so we can find the data.
// Don't forget to call delete[] later.

/////// 3: Play with your calculator
// Find a programming calculator app on your phone or computer (On Windows, the default Calculator app includes this--check the dropdown menu)
// Type your numbers into the calculator to see how they come up in different formats
// If you have a 8-bit char and | (OR) it with the maximum char value of 255, what do you get?
// If you & (AND) it with 255 what do you get?
// What if you XOR it with 255?
// How about all of these with 0 instead of 255?

/////// 4: Use bitwise operators in code and see how they affect the data
// Try using the bitwise operators on the data.
// Create some examples including AND, OR, XOR, and Bitshifting
// Breakpoint your code so execution stops before the operations

/////// 5: Use the Memory View
// While the app is running, look Under Debug->Windows->Memory
// This window allows you to directly explore the contents of your RAM
// Use this view to see what is happening to the data as each operation is done.

/////// 6: Create a bit-masking flag system
// It is a common pattern in many APIs to see unsigned integer arguments passed to a function as a way of "configuring flags" in the function call.
// For example, SLD_Init() takes flags OR'd together such as SDL_INIT_TIMER, SDL_INIT_AUDIO, and SDL_INIT_EVERYTHING - https://wiki.libsdl.org/SDL_Init
// If you check the definitions of these macros in SDL.h, you will find:
//
#define SDL_INIT_TIMER          0x00000001u
#define SDL_INIT_AUDIO          0x00000010u
#define SDL_INIT_VIDEO          0x00000020u  /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
#define SDL_INIT_JOYSTICK       0x00000200u  /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
#define SDL_INIT_HAPTIC         0x00001000u
#define SDL_INIT_GAMECONTROLLER 0x00002000u  /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
#define SDL_INIT_EVENTS         0x00004000u
#define SDL_INIT_SENSOR         0x00008000u
#define SDL_INIT_NOPARACHUTE    0x00100000u  /**< compatibility; this flag is ignored. */
#define SDL_INIT_EVERYTHING ( \
                SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | \
                SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR \
            )
// We can make our own system like this to store game-specific flag data in a memory-efficient way. 
// This is a common way games handle keeping track of what objects should collide with what others in a physics system because it allows each object to have its own unique settings, 
// while keeping the amount of extra data storage per object low.

// Note that numbers in the #define statements are shown with "0x" in front of them. This means they are in hexadecimal i.e. instead of 0-9, the digits are 0-F
// A binary digit (bit) can be in 2 states and stores 1 bit of informations. Each hexadecimal digit can be in 16 states and stores 4 bits of information. (2^4 = 16)
// A byte is the smallest individual data size we can address. It is 8 bits in size. Two hexadecimal digits can represent its entire value (2 * 4 bits = 8 bits total)
// On a 64-bit OS, memory addresses are indexed by pointers of 64 bits                                                              

#include <iostream>

using namespace std;

int main()
{
}