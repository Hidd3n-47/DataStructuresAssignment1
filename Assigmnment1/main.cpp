#include "Memory.h"
#include "List.h"

template<class T>
void ConsolePrintList(const List<T>& list)
{
	std::cout << "{ ";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value();
		if (it != list.end() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << " }" << std::endl;
}

#define PRINT(x) \
	std::cout << "| '" << #x << "' = "; \
	ConsolePrintList(x)

void TestOne()
{
	std::cout << "\n|===================================================================|\n";
	std::cout <<   "|                              TEST_ONE                             |\n";
	std::cout <<   "|-------------------------------------------------------------------|\n";

	List<int> list;

	for (int i = 0; i < 6; i++)
	{
		list.push_back(i);
	}

	int sum = 0;

	// Print method re-written here due to question stating "_Inside_ TestOne(), create a loop..."
	// Could use PRINT(list); instead to display the contents of the list, which will be used
	// in the other test methods.
	std::cout << "| list = { ";
	for (_iterator<int> it = list.begin(); it != list.end(); it++)
	{
		std::cout << it.value();
		if (it != list.end() - 1)
		{
			std::cout << ", ";
		}
		sum += it.value();
	}
	std::cout << " }" << std::endl;

	std::cout << "| Sum: " << sum << std::endl;
	std::cout << "|===================================================================|\n";

}

void TestTwo()
{
	std::cout << "\n|===================================================================|\n";
	std::cout <<   "|                              TEST_TWO                             |\n";
	std::cout <<   "|-------------------------------------------------------------------|\n";

	List<char> original;
	original.push_back('d', 'l', 'r', 'o', 'w', ' ', 'o', 'l', 'l', 'e', 'h');

	List<char> reverse;

	for (_iterator<char> it = original.begin(); it != original.end(); it++)
	{
		reverse.push_front(it.value());
	}

	PRINT(original);

	PRINT(reverse);

	std::cout << "|===================================================================|\n";
}

void TestThree()
{
	std::cout << "\n|===================================================================|\n";
	std::cout <<   "|                            TEST_THREE                             |\n";
	std::cout <<   "|-------------------------------------------------------------------|\n";

	List<int> original;
	original.push_back(-10, 0, 2, 9, 0, -15, -6, -7, 0, 13, 8, 4, 0, 6);

	List<int> negatives;
	List<int> zeros;
	List<int> positives;

	for (auto it = original.begin(); it != original.end(); it++)
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

	PRINT(original);

	PRINT(negatives);

	PRINT(zeros);

	PRINT(positives);

	std::cout << std::endl;
	std::cout << "|===================================================================|\n";
}


void TestFour()
{
	std::cout << "\n|===================================================================|\n";
	std::cout <<   "|                             TEST_FOUR                             |\n";
	std::cout <<   "|-------------------------------------------------------------------|\n";


	List<int> original;
	original.push_back(10, 2, 9, 15, 6, 7, 13, 8);

	List<int> odds;
	List<int> evens;

	for (auto it = original.begin(); it != original.end(); it++)
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

	PRINT(original);

	PRINT(odds);

	PRINT(evens);

	std::cout << "|===================================================================|\n";
}

void TestFive()
{
	std::cout << "\n|===================================================================|\n";
	std::cout <<   "|                             TEST_FIVE                             |\n";
	std::cout <<   "|-------------------------------------------------------------------|\n";

	List<int> list;
	list.push_back(-1, 5, 17, 4, 9, 20, -7, 8, 11, 0, 53, 14);

	std::cout << "| Original List:" << std::endl;
	PRINT(list);

	list.sort();

	std::cout << "| Sorted List:" << std::endl;
	PRINT(list);

	std::cout << "|===================================================================|\n\n";
}

// Class to test memory allocation.
class foo
{
public:
	foo() { }
	int arr[10] = { };
};

int main()
{
	PrintMemory();

	TestOne();
	TestTwo();
	TestThree();
	TestFour();
	TestFive();

	// Memory Test 1.
	{
		List<double> list;
		list.push_back(2., 4., 6.);
		list.clear();
		list.push_back(1., 3., 5.);
	}

	// Memory Test 2.
	{
		List<foo> list;
		for (int i = 0; i < 10; i++)
		{
			foo bar;
			list.push_back(bar);
		}
	}

	PrintMemory();

	std::cout << std::endl;
	system("PAUSE");
	return 0;
}