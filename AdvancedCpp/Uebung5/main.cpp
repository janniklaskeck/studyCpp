#include <fstream>
#include <istream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <string>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std::chrono;

time_point<high_resolution_clock> nowTime()
{
	return high_resolution_clock::now();
}

nanoseconds timePointToNumber(nanoseconds timePoint)
{
	return duration_cast<nanoseconds>(timePoint);
}

nanoseconds findTenLongestWords(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds findMeanLengthOfAllWords(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds findMedianLengthOfAllWords(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds listEvery100Word(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	std::vector<std::string> list;

	for (int i = 0; i < words.size(); i++)
	{
		if (i % 99 == 0)
		{
			list.push_back(words[i]);
		}
	}

	return timePointToNumber(nowTime() - start);
}

nanoseconds find10MostOccuringWords(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds findSingleWords(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds findWordsOccurringBetween5To15Times(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

char findFirstChar(std::string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] > 0)
		{
			return word[i];
		}
	}
	return 0;
}

nanoseconds findWordsStartingUppercase(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	int count = 0;

	for (std::string word : words)
	{
		if (isupper(findFirstChar(word)))
		{
			count++;
		}
	}

	return timePointToNumber(nowTime() - start);
}

nanoseconds calcHistogramAToZ(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	return timePointToNumber(nowTime() - start);
}

nanoseconds sortAlphabetically(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	std::sort(words.begin(), words.end());

	return timePointToNumber(nowTime() - start);
}

nanoseconds findWordsStartingWithT(std::vector<std::string> words)
{
	time_point<steady_clock> start;
	start = nowTime();

	int count = 0;

	for (std::string word : words)
	{
		if (word[0] == 't')
		{
			count++;
		}
	}

	return timePointToNumber(nowTime() - start);
}

int main()
{

	std::fstream file("dickens.txt");
	std::vector <std::string> words{
		std::istream_iterator<std::string>(file),
		std::istream_iterator<std::string>() };

	printf("5. Make list of every 100 word in: %ld nanoseconds\n", listEvery100Word(words));

	printf("9. Find all uppercase words in: %ld nanoseconds\n", findWordsStartingUppercase(words));
	printf("10. Sort words alphabetically in: %ld nanoseconds\n", sortAlphabetically(words));
	printf("12. Find Words starting with 't' in: %ld nanoseconds\n", findWordsStartingWithT(words));

	char a;
	std::cin >> a;
	return 0;
}


