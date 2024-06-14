#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
	// vector<int> arr = { 8, 2, 3, 5, 9, 1, 9, 4, 3, 7, 6, 7 };
	random_device rd;
	mt19937 gen(rd());

	const int n = 20;
	vector<int> my_vector(n);
	
	uniform_int_distribution<int> value_distribution(1, 10);
	generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });

	// TODO:
	int max = my_vector[0];
	int min = my_vector[0];

	size_t compare_count = 0;
	for (size_t idx = 1; idx < my_vector.size(); idx++)
	{
		compare_count++;
		if (my_vector[idx] > max)
			max = my_vector[idx];
		else if (my_vector[idx] < min)
		{
			compare_count++;
			min = my_vector[idx];
		}
		else // else에서 compare_count 증가 시키는 이유는 else if까지 연산했었는지 보기 위함
			compare_count++;
	}

	std::cout << "compare count : " << compare_count << std::endl;
	std::cout << "3n/2 - 2 : " <<  (3 * n / 2) - 2 << std::endl;

	cout << "Min value = " << min << ", Max value = " << max << endl; // Min value = 1, Max value = 9
	sort(my_vector.begin(), my_vector.end());
	for (auto element : my_vector)
		std::cout << element << " ";
	std::cout << std::endl;
	assert(min == my_vector[0]);
	assert(max == my_vector.at(my_vector.size() - 1));
	
}