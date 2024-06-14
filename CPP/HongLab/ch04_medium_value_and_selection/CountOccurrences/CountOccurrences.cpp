#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}


// O(n)
int Count1(const vector<int>& arr, int target)
{
    int count = 0;
	//TODO: O(n)
    for (auto element : arr)
        if (target == element)
            count++;
	return count;
}

/** Binary Search
 * x값의 시작 위치를 찾아야한다.
 * 1 1 3 3 3 4 4 5 6 7 7 7 7 7 8 8 8 9 10 10 
 *     a b c
 * 
 * 이분탐색에서 3 b, 3 c를 찾았다 했을 때,  3 a부터 시작되어야한다.
 * 작아지기 직전까지 가야한다.
 * 
 */
int Count2(const vector<int>& arr, int target)
{
	//TODO: O(log(n) + count)
    int start = 0;
	int end = arr.size() - 1;

    while (start <= end)
    {
		int mid = (start + end) / 2;

		if (arr.at(mid) < target)
			start = mid + 1;
		else if (arr.at(mid) > target)
			end = mid - 1;
		else //(arr.at(mid) == target)
		{
			start = mid - 1;
			end--;
		}
    }

	for (auto element : arr)
		std::cout << element << " ";
	std::cout << std::endl;
	// std::cout << "target : " << target <<std::endl;
	// std::cout << "start : " << start << ", arr.at(start) : " << arr.at(start) << std::endl;
	// std::cout << "end : " << end << ", arr.at(end) : " << arr.at(end) << std::endl;
	int count = 0;
	while (arr.at(start) == target)
	{
		count++;
		start++;
	}
	return count;
}

/**
 * target이랑 일치하는 값을 가진 위치 중 가장 왼쪽과 가장 오른쪽을 찾아서 둘의 차를 구한다.
 */
int Count3(const vector<int>& arr, int target)
{
	//TODO: O(log(n))
	int start = 0;
	int end = arr.size() - 1;

    while (start <= end)
    {
		int mid = (start + end) / 2;

		if (arr.at(mid) < target)
			start = mid + 1;
		else if (arr.at(mid) > target)
			end = mid - 1;
		else //(arr.at(mid) == target)
		{
			start = mid - 1;
			end--;
		}
    }

	int prev_start = start;
	end = arr.size() - 1;
    while (start <= end)
    {
		int mid = (start + end) / 2;

		if (arr.at(mid) < target)
			start = mid + 1;
		else if (arr.at(mid) > target)
			end = mid - 1;
		else //(arr.at(mid) == target)
		{
			end = mid + 1;
			start++;
		}
    }
    return (end - prev_start) + 1;
}

int main()
{
	random_device rd;
	mt19937 gen(rd());

	const int n = 20;
	vector<int> my_vector(n);

	int x = 6; // target to find

	for (int r = 0; r < 100; r++)
	{
		uniform_int_distribution<int> value_distribution(1, 10);
		generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
		sort(my_vector.begin(), my_vector.end());

		Print(my_vector);

		const int expected_count = std::count(my_vector.begin(), my_vector.end(), x);

		cout << "Expected count = " << expected_count << endl;

		// 1. O(n) brute force
		if (Count1(my_vector, x) != expected_count)
		{
			cout << "Wrong count1: " << Count1(my_vector, x) << endl;
			exit(-1);
		}

		// 2. O(log(n) + count)
		if (Count2(my_vector, x) != expected_count)
		{
			cout << "Wrong count2: " << Count2(my_vector, x) << endl;
			exit(-1);
		}

		// 3. O(log(n))
		if (Count3(my_vector, x) != expected_count)
		{
			cout << "Wrong count3: " << Count3(my_vector, x) << endl;
			exit(-1);
		}
	}

	cout << "Good!" << endl;

	return 0;
}