#include <iostream>

#include "List.h"

#include <list>

void TestOne()
{
	List<int> list;

	for (int i = 0; i < 6; i++)
	{
		list.push_back(i);
	}

	int sum = 0;

	for (_iterator<int> it = list.begin(); it != list.end(); it++)
	{
		sum += it.value();
		std::cout << it.value() << std::endl;
	}

	std::cout << "----------" << std::endl;
	std::cout << "Sum: " << sum << std::endl;
}

void TestTwo()
{
	List<char> list;
	list.push_back('d', 'l', 'r', 'o', 'w', ' ', 'o', 'l', 'l', 'e', 'h');

	List<char> reverse;

	for (_iterator<char> it = list.begin(); it != list.end(); it++)
	{
		reverse.push_front(it.value());
	}

	std::cout << "\n\nFirst List:\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << " ";
	}

	std::cout << "\n\nSecond List:\n";
	for (auto it = reverse.begin(); it != reverse.end(); it++)
	{
		std::cout << it.value() << " ";
	}
}

void TestThree()
{
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

	std::cout << "\n\nNegative List:\n_____________\n";
	for (auto it = negatives.begin(); it != negatives.end(); it++)
	{
		std::cout << it.value() << " ";
	}

	std::cout << "\n\nZero List:\n_____________\n";
	for (auto it = zeros.begin(); it != zeros.end(); it++)
	{
		std::cout << it.value() << " ";
	}

	std::cout << "\n\nPositive List:\n_____________\n";
	for (auto it = positives.begin(); it != positives.end(); it++)
	{
		std::cout << it.value() << "_";
	}
}


void TestFour()
{
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

	std::cout << "\n\nOdds List:\n_____________\n";
	for (auto it = odds.begin(); it != odds.end(); it++)
	{
		std::cout << it.value() << "_";
	}

	std::cout << "\n\nEvens List:\n_____________\n";
	for (auto it = evens.begin(); it != evens.end(); it++)
	{
		std::cout << it.value() << "_";
	}
}

void TestFive()
{
	std::cout << std::endl << std::endl << std::endl;
	List<int> list;
	list.push_back(-1, 5, 17, 4, 9, 20, -7, 8, 11, 0, 53, 14);

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

	for (auto it = list.begin(); it != list.end(); it++)
		std::cout << it.value() << std::endl;


	// TODO: sort.
}

int main()
{
	TestOne();

	TestTwo();

	TestThree();

	TestFour();

	TestFive();

	system("PAUSE");
	return 0;
}