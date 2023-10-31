#pragma once

#include <iostream>

// Struct to hold the memory that has been allocated and freed. Unnamed to have single instance.
struct
{
	uint32_t _allocated = 0;
	uint32_t _freed = 0;
} MEM_ALLOCATION;

// 'new' Keyword override.
void* operator new(size_t size)
{
	MEM_ALLOCATION._allocated += size;
	return malloc(size);
}

// 'delete' Keyword override.
void operator delete(void* memory, size_t size)
{
	MEM_ALLOCATION._freed += size;
	free(memory);
}

void PrintMemory()
{
	std::cout << "|===================================================================|\n";
	std::cout << "|                          MEM_ALLOCATION                           |\n";
	std::cout << "|-------------------------------------------------------------------|\n";
	std::cout << "| Allocated: " << MEM_ALLOCATION._allocated << " bytes\n";
	std::cout << "| Freed: " << MEM_ALLOCATION._freed << " bytes\n";
	std::cout << "|===================================================================|\n";
}

// Macro.
#ifdef _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(x) x
#endif
