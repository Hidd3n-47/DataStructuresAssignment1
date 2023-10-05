#include <iostream>

#include "List.h"

#include <list>

void TestOne()
{
	std::cout << "\n|=============================================================|\n";
	std::cout <<   "|                           TEST_ONE                          |\n";
	std::cout <<   "|-------------------------------------------------------------|\n";

	List<int> list;

	for (int i = 0; i < 6; i++)
	{
		list.push_back(i);
	}

	int sum = 0;

	std::cout << "| List:\n| ";

	for (_iterator<int> it = list.begin(); it != list.end(); it++)
	{
		sum += it.value();
		std::cout << it.value() << ", ";
	}

	std::cout << std::endl;
	std::cout << "| Sum: " << sum << std::endl;
	std::cout << "|=============================================================|\n";

}

void TestTwo()
{
	std::cout << "\n|=============================================================|\n";
	std::cout <<   "|                           TEST_TWO                          |\n";
	std::cout <<   "|-------------------------------------------------------------|\n";

	List<char> list;
	list.push_back('d', 'l', 'r', 'o', 'w', ' ', 'o', 'l', 'l', 'e', 'h');

	List<char> reverse;

	for (_iterator<char> it = list.begin(); it != list.end(); it++)
	{
		reverse.push_front(it.value());
	}

	std::cout << "| First List:\n| ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n| Second List:\n| ";
	for (auto it = reverse.begin(); it != reverse.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << std::endl;
	std::cout << "|=============================================================|\n";
}

void TestThree()
{
	std::cout << "\n|=============================================================|\n";
	std::cout <<   "|                         TEST_THREE                          |\n";
	std::cout <<   "|-------------------------------------------------------------|\n";

	List<int> list;
	list.push_back(-10, 0, 2, 9, 0, -15, -6, -7, 0, 13, 8, 4, 0, 6);

	List<int> negatives;
	List<int> zeros;
	List<int> positives;

	for (auto it = list.begin(); it != list.end(); it++)
	{
		int tmp = it.value();
		if (tmp < 0)
		{
			negatives.push_back(tmp);
		}
		else if (tmp == 0)
		{
			zeros.push_back(tmp);
		}
		else
		{
			positives.push_back(tmp);
		}
	}

	std::cout << "| Original List:\n| ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n|\n| Negative List:\n| ";
	for (auto it = negatives.begin(); it != negatives.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n| Zero List:\n| ";
	for (auto it = zeros.begin(); it != zeros.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n| Positive List:\n| ";
	for (auto it = positives.begin(); it != positives.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << std::endl;
	std::cout << "|=============================================================|\n";
}


void TestFour()
{
	std::cout << "\n|=============================================================|\n";
	std::cout <<   "|                          TEST_FOUR                          |\n";
	std::cout <<   "|-------------------------------------------------------------|\n";


	List<int> list;
	list.push_back(10, 2, 9, 15, 6, 7, 13, 8);

	List<int> odds;
	List<int> evens;

	for (auto it = list.begin(); it != list.end(); it++)
	{
		int tmp = it.value();
		if (tmp % 2 == 0)
		{
			evens.push_back(tmp);
		}
		else
		{
			odds.push_back(tmp);
		}
	}

	std::cout << "| Original List:\n| ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n|\n| Odds List:\n| ";
	for (auto it = odds.begin(); it != odds.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << "\n| Evens List:\n| ";
	for (auto it = evens.begin(); it != evens.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << std::endl;
	std::cout << "|=============================================================|\n";
}

void TestFive()
{
	std::cout << "\n|=============================================================|\n";
	std::cout <<   "|                          TEST_FIVE                          |\n";
	std::cout <<   "|-------------------------------------------------------------|\n";

	List<int> list;
	list.push_back(-1, 5, 17, 4, 9, 20, -7, 8, 11, 0, 53, 14);

	std::cout << "| Original List:\n| ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	for (int i = list.size(); i > 0; i--)
	{
		int counter = 0;
		auto previous = list.begin();

		for (auto it = list.begin(); counter++ < i; it++)
		{
			if (it == list.begin()) { continue; }

			if (previous.value() > it.value())
			{
				list.swap(previous, it);
			}
			previous = it;
		}
	}

	std::cout << "\n| Sorted List:\n| ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << ", ";
	}

	std::cout << std::endl;
	std::cout << "|=============================================================|\n\n";
}

void PrintMemory()
{
	std::cout << "|=============================================================|\n";
	std::cout << "|                       MEM_ALLOCATION                        |\n";
	std::cout << "|-------------------------------------------------------------|\n";
	std::cout << "| Allocated: "	<< MEM_ALLOCATION._allocated	<< " bytes\n";
	std::cout << "| Freed: "		<< MEM_ALLOCATION._freed		<< " bytes\n";
	std::cout << "|=============================================================|\n";
}

int main()
{
	PrintMemory();

	TestOne();
	TestTwo();
	TestThree();
	TestFour();
	TestFive();

	{
		List<double> list;
		list.push_back(2., 4., 6.);
		list.clear();
		list.push_back(1., 3., 5.);
	}
	PrintMemory();

	std::cout << std::endl;
	system("PAUSE");
	return 0;
}