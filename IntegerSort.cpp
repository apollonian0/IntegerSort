// Copyright 2020 Ben Howenstein. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

void SortZeros1(int values[], const int length)
{
    int lastIndex = length - 1;
    for(int i = 0; i < lastIndex; ++i)
    {
        if (values[i] == 0)
        {
            for (int j = i; j < lastIndex; ++j)
            {
                values[j] = values[j + 1];
            }
            values[lastIndex--] = 0;
        }
    }
}

int main()
{
    srand(time(NULL));

    auto FillRandom = [](int values[], int length)
    {
        for (int i = 0; i < length; ++i)
        {
            if (rand() % 3 == 0)
            {
                values[i] = 0;
            }
            else
            {
                values[i] = rand() % 100;
            }
        }
    };

    int NumValues = 10;
    int randomValues[100] = {};

    FillRandom(randomValues, NumValues);
    SortZeros1(randomValues, NumValues);
    for (int i = 0; i < NumValues; ++i)
    {
        std::cout << randomValues[i] << " ";
    }
    std::cout << "\n\n";

    NumValues = 20;
	FillRandom(randomValues, NumValues);
	SortZeros1(randomValues, NumValues);
	for (int i = 0; i < NumValues; ++i)
	{
		std::cout << randomValues[i] << " ";
	}
    std::cout << "\n\n";
}
