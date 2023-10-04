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
	list.push_back('d');
	list.push_back('l');
	list.push_back('r');
	list.push_back('o');
	list.push_back('w');
	list.push_back(' ');
	list.push_back('o');
	list.push_back('l');
	list.push_back('l');
	list.push_back('e');
	list.push_back('h');

	List<char> reverse;

	for (_iterator<char> it = list.begin(); it != list.end(); it++)
	{
		reverse.push_front(it.value());
	}

	std::cout << "\n\nFirst List:\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value() << "_";
	}

	std::cout << "\n\nSecond List:\n";
	for (auto it = reverse.begin(); it != reverse.end(); it++)
	{
		std::cout << it.value() << "_";
	}
}

void TestThree()
{
	List<int> list;
	list.push_back(-10);
	list.push_back(0);
	list.push_back(2);
	list.push_back(9);
	list.push_back(0);
	list.push_back(-15);
	list.push_back(-6);
	list.push_back(-7);
	list.push_back(0);
	list.push_back(13);
	list.push_back(8);
	list.push_back(4);
	list.push_back(0);
	list.push_back(6);

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
		std::cout << it.value() << "_";
	}

	std::cout << "\n\nZero List:\n_____________\n";
	for (auto it = zeros.begin(); it != zeros.end(); it++)
	{
		std::cout << it.value() << "_";
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
	list.push_back(10);
	list.push_back(2);
	list.push_back(9);
	list.push_back(15);
	list.push_back(6);
	list.push_back(7);
	list.push_back(13);
	list.push_back(8);

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
	List<int> list;
	list.push_back(-1);
	list.push_back(5);
	list.push_back(17);
	list.push_back(4);
	list.push_back(9);
	list.push_back(20);
	list.push_back(-7);
	list.push_back(8);
	list.push_back(11);
	list.push_back(0);
	list.push_back(53);
	list.push_back(14);

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