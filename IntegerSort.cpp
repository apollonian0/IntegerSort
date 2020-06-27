// Copyright 2020 Ben Howenstein. All rights reserved.
//

#include <iostream>
#include <random>
#include <chrono>


void SortZerosInPlace(int values[], const int length)
{
	int lastIndex = length;
	for (int i = 0; i < lastIndex; )
	{
		if (values[i] == 0)
		{
			for (int j = i; j < lastIndex - 1; ++j)
			{
				values[j] = values[j + 1];
			}
			values[--lastIndex] = 0;
			continue;
		}
		++i;
	}
}


void SortZerosCopy(int values[], const int length)
{
	int* valuesCopy = new int[length];
	memset(valuesCopy, 0, sizeof(valuesCopy[0]) * length);

	int valuesCopyLength = 0;
	for (int i = 0; i < length; ++i)
	{
		if (values[i] != 0)
		{
			valuesCopy[valuesCopyLength++] = values[i];
		}
	}
	memcpy(values, valuesCopy, sizeof(valuesCopy[0]) * length);
}


int main()
{
	std::default_random_engine randEngine;
	std::uniform_int_distribution<size_t> randDist(0, 100);

	int values[10000] = {};
	auto FillRandom = [&](const int length, void(*sortFn)(int[], int) )
	{
		for (int i = 0; i < length; ++i)
		{
			const auto randValue = randDist(randEngine);
			values[i] = !(randValue % 3) ? 0 : randValue;
		}


		auto PrintValues = [&values, length]()
		{
			for (int i = 0; i < length; ++i)
			{
				std::cout << values[i] << " ";
			}
			std::cout << "\n";
		};

		//PrintValues();
		const auto startTime = std::chrono::high_resolution_clock::now();
		sortFn(values, length);
		const auto endTime = std::chrono::high_resolution_clock::now();
		//PrintValues();
		std::cout << "Num elements: " << length << " Time taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
		std::cout << "\n";
	};

	std::cout << "In place sort:\n";
	FillRandom(10, SortZerosInPlace);
	FillRandom(100, SortZerosInPlace);
	FillRandom(1000, SortZerosInPlace);
	FillRandom(10000, SortZerosInPlace);
	std::cout << "\n";
	std::cout << "Copy sort:\n";
	FillRandom(10, SortZerosCopy);
	FillRandom(100, SortZerosCopy);
	FillRandom(1000, SortZerosCopy);
	FillRandom(10000, SortZerosCopy);

	/*
	Sample output(release):

	In place sort:
		Num elements: 10 Time taken: 200
		Num elements: 100 Time taken: 1300
		Num elements: 1000 Time taken: 78900
		Num elements: 10000 Time taken: 7312000

	Copy sort:
		Num elements: 10 Time taken: 4100
		Num elements: 100 Time taken: 3000
		Num elements: 1000 Time taken: 4600
		Num elements: 10000 Time taken: 56800
	*/
}
