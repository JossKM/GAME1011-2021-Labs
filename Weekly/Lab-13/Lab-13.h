#pragma once
#include <iostream>
#include <string>

/* 

,__                   __
    '~~****Nm_    _mZ*****~~
            _8@mm@K_
           W~@`  '@~W
          ][][    ][][
    gz    'W'W.  ,W`W`    es
  ,Wf    gZ****MA****Ns    VW.
 gA`   ,Wf     ][     VW.   'Ms
Wf    ,@`      ][      '@.    VW
M.    W`  _mm_ ][ _mm_  'W    ,A
'W   ][  i@@@@i][i@@@@i  ][   W`
 !b  @   !@@@@!][!@@@@!   @  d!
  VWmP    ~**~ ][ ~**~    YmWf
    ][         ][         ][
  ,mW[         ][         ]Wm.
 ,A` @  ,gms.  ][  ,gms.  @ 'M.
 W`  Yi W@@@W  ][  W@@@W iP  'W
d!   'W M@@@A  ][  M@@@A W`   !b
@.    !b'V*f`  ][  'V*f`d!    ,@
'Ms    VW.     ][     ,Wf    gA`
  VW.   'Ms.   ][   ,gA`   ,Wf
   'Ms    'V*mmWWmm*f`    gA`
   
	 .   .
      \ /
    `/ ! \`
    | o:o |
   ~| o:o |~
   / \_:_/ \

*/


template<typename T>
class SimpleVector
{
protected:
	T* m_pData = nullptr;

	//number of elements
	size_t m_size;

	//number of elements in the array
	size_t m_sizeAllocated;


public:
	SimpleVector() : m_size(0), m_sizeAllocated(0)
	{
	}

	SimpleVector(size_t size) : m_size(0), m_sizeAllocated(size)
	{
		m_pData = new T[m_size];
	}

//															     '__'
//															    \O__O/
//															   ==x||x==
//															    /^||^\
//															   /^^||^^\
//															   \^^||^^/
//															    '-''-'

	// Copy constructor. Called when we create based on another
	SimpleVector(const SimpleVector& other)
	{
		delete[] m_pData;
		m_size = other.m_size;
		m_sizeAllocated = other.m_sizeAllocated; // copying this is ok
		m_pData = new T[m_sizeAllocated];

		for (short i = 0; i < m_size; i++)
		{
			m_pData[i] = other.m_pData[i];
		}
	}

	// Our destructor should be virtual because we plan to inherit from this class later, and we want this destructor to be called
	virtual ~SimpleVector()
	{
		delete[] m_pData;
	}

	/*
				  \ /																     \ /
				  oVo																     oVo
			  \___XXX___/															 \___XXX___/
			   __XXXXX__															  __XXXXX__
			  /__XXXXX__\															 /__XXXXX__\
			  /   XXX   \															 /   XXX   \
				   V																      V
	*/

	void push_back(T value)
	{
		if ((m_size + 1) >= m_sizeAllocated)
		{
			Resize(m_sizeAllocated * 2);
		}

		m_size++;
		m_pData[m_size] = value;
	}

	T pop_back()
	{
		T lastElement = m_pData[m_size]; // save last element before we remove it, so we can return it!
		if ((m_size - 1) < m_sizeAllocated / 2)
		{
			Resize(m_sizeAllocated / 2);
		}

		m_size--;
		return lastElement;
	}

	/*
													 .   .
													  \ /
													`/ ! \`
													| o:o |
												   ~| o:o |~
												   / \_:_/ \
   */

	void Resize(size_t numElements)
	{
		T* pOldData = m_pData;

		m_sizeAllocated = numElements;
		m_pData = new T[m_sizeAllocated]; // create a new block of memory for the copy

		//copy all the data!
		for (short i = 0; i < m_size; i++)
		{
			m_pData[i] = pOldData[i];
		}

		delete[] pOldData;
	}

	// Returns number of spaces for elements allocated
	size_t SizeAllocated()
	{
		return m_sizeAllocated;
	}

	// Returns number of elements in the vector
	size_t Size()
	{
		return m_size;
	}

	// Return a reference so that it can be assigned e.g. mySimpleVector[5] = 7;
	T& operator[] (size_t index)
	{
		return m_pData[index];
	}

	//Operator overload for assignment operator '='
	void operator=(const SimpleVector& valueToAssign)
	{
		m_sizeAllocated = valueToAssign.m_sizeAllocated; // copying size is ok
		m_size = valueToAssign.m_size;

		delete[] m_pData; // we need to clean up the data before we replace it. Don't want to leave orphans... therefore. we DESTROY IT
		m_pData = new T[m_sizeAllocated]; // create a new block of memory for the copy

		//copy all the data!
		for (size_t i = 0; i < m_size; i++)
		{
			m_pData[i] = valueToAssign.m_pData[i];
		}
	}
};

/*
											    \ /
											    oVo
											\___XXX___/
											 __XXXXX__
											/__XXXXX__\
											/   XXX   \
											     V
*/

// Stream insertion operator, to make it convenient to print
template<typename T>
std::ostream& operator<<(std::ostream& out, SimpleVector<T>& toPrint)
{
	std::string outStr = "{";

	for (size_t i = 0; i < toPrint.SizeAllocated(); i++)
	{
		outStr += " " + toPrint[i];
	}
	outStr += "}";

	return out;
}