///////////////////////////////////////////////////////////////
// GAME1011 Lab 10
////////////////////////////////////////////////////////////////

/////// Topic: Recursive Functions
// https://www.youtube.com/watch?v=sJFoGhyZtPg // Wallace's lab video, including Binary Search
// https://craftofcoding.wordpress.com/2018/05/10/recursive-patterns-the-sierpinski-carpet/

/////// Keywords to note
/*
Base case
Recurrence relation
Iterative vs recursive
*/

/////// Lab activities
// This lab, we will be exploring recursion

/////// 1: Setup
// Clone the repo, set this Lab as "Startup Project", or start a new project with a main function                                                                                     

/////// 2: Make a function that prints, then calls itself
	/////// Call the function
		/////// The function calls itself
			/////// The function calls itself
				/////// The function calls itself
					/////// The function calls itself
						/////// The function calls itself
							/////// The function calls itself
								/////// The function calls itself
									/////// The function calls itself
										/////// The function calls itself
											/////// The function calls itself
												/////// The function calls itself
													/////// The function calls itself
														/////// The function calls itself
															/////// The function calls itself
																/////// The function calls itself
																	/////// And eventually... stack Overflow. How deep did it go before crashing?

/////// 3: Use Visual Studio's call stack to observe the function in action
// Place a breakpoint inside the recursive function

/////// 4: Convert the recursive function into a loop by adding a BASE CASE
// Give the function a variable which will change each time
// Add a BASE CASE where the function returns without calling itself (i.e. when the changing variable reaches a certain condition)

/////// 5. Try printing some squares to the console using the provided functions

/////// 6. Observe the Sierpinski Carpet fractal pattern
// https://craftofcoding.wordpress.com/2018/05/10/recursive-patterns-the-sierpinski-carpet/
// The pattern itself isn't important to the course, but the process of making a recursive function for it is. We are going to make it!

/////// Print a Sierpinski carpet to the console using recursion!
// Base case: either choose an iteration number, or make it exit when the size of squares is too small
// Recursion: Divide the drawing area into 9 sub-squares. For the middle sub-square, draw a filled rectangle.
// For the remaining 8 of the 9 sub-squares, the function should be recursive, calling itself within each sub-square.


#include <iostream>
#include <time.h>

// This code allows you to "draw" in 2D to the console window, as if they were pixels
// This is essentially your "screen". We draw to this instead of the screen directly, then copy it to the screen when it is ready. Similar to how there is a front and back buffer in graphics.
#define RESOLUTIONX 400
#define RESOLUTIONY 200
char printBuffer[RESOLUTIONX * RESOLUTIONY];
#define BUFFER_AT(x, y) printBuffer[y * RESOLUTIONX + x]

void PrintSquare(char pixel, int xPos, int yPos, int width, int height)
{
	for (int ix = xPos; ix < xPos + width; ix++)
	{
		for (int iy = yPos; iy < yPos + height; iy++)
		{
			if (0 <= ix && ix < RESOLUTIONX - 1 && 0 <= iy && iy < RESOLUTIONY)
			{
				BUFFER_AT(ix, iy) = pixel;
			}
		}
	}
}

void ClearBuffer(char clearCharacter)
{
	for (int ix = 0; ix < RESOLUTIONX; ix++)
	{
		for (int iy = 0; iy < RESOLUTIONY; iy++)
		{
			if (ix == RESOLUTIONX - 1)
			{
				BUFFER_AT(ix, iy) = '\n';
			}
			else
			{
				BUFFER_AT(ix, iy) = clearCharacter;
			}
		}
	}
}

void Loop(int times)
{
	if (times <= 0) // Base case: where recursion ends
	{
		return;
	}
	else
	{
		Loop(times - 1);
		std::cout << times << std::endl;
		PrintSquare('o', times * 10, 0, rand() % 5, rand() % 10);
	}
}

void TinySquareGang(int posX, int posY, int size)
{
	// Base case, function returns when size is less than 1. 
	// Important that this is always hit otherwise the function may be unstable
	if (size < 1) 
	{
		return;
	}
	else
	{
		/*
		[0][1][2]
		[3][4][5]
		[6][7][8]
		*/

		// Indexing a 2D position from a 1D index and a size
		// i == 0 : position = (0 * size/3, 0 * size/3)
		// i == 1 : position = (1 * size/3, 0 * size/3)
		// i == 2 : position = (2 * size/3, 0 * size/3)
		// i == 3 : position = (0 * size/3, 1 * size/3)
		// i == 4 : position = (1 * size/3, 1 * size/3)
		// i == 5 : position = (2 * size/3, 1 * size/3)
		// i == 6 : position = (0 * size/3, 2 * size/3)

		int shrunkSize = size / 3;
		for (int i = 0; i < 9; i++)
		{
			int newSquarePosX = posX + (i % 3) * shrunkSize * 2; // posX + 1/3 size
			int newSquarePosY = posY + (i / 3) * shrunkSize;

			if (i == 4)
			{
				// We multiply the widths by 2 just because characters in the console window are taller than they are wide, 
				// and we want it to look more 'square'
				PrintSquare('X', newSquarePosX, newSquarePosY, shrunkSize * 2, shrunkSize);
			}
			else
			{
				// Recursion case
				TinySquareGang(newSquarePosX, newSquarePosY, shrunkSize);
			}
		}
	}
}

// Swap two elements in an array by index
template<typename T>
void Swap(T* arr, int indexA, int indexB)
{
	T temp = arr[indexA];
	arr[indexA] = arr[indexB];
	arr[indexB] = temp;
}

int main()
{
	srand(time(0));

	ClearBuffer('.');
	//Loop(10);
	TinySquareGang(0, 0, 200);

	std::cout << printBuffer;
	getchar();
	return 0;
}