#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}

// 가장 작은 값이 arr[lo]에 오도록 
void SelectionSortPass(vector<int>& arr, int lo, int hi)
{
	// TODO: 
	int min_value_index = lo;

	for (int idx = min_value_index; idx < hi;  idx++)
	{
		if (arr[idx] < arr[min_value_index])
			min_value_index = idx;
	}
	std::swap(arr[lo], arr[min_value_index]);
}

/**
 * 주어진 배열에서 k 값을 바꿔가면서 k-selection을 아주 많이 한다면 가장 효율적인 방법은 뭘까요?
 * 
 * 미리 정렬하는 것이겠지만 그렇게 한다면 PartialSelectionSort()을 호출하기 전에 정렬해야한다.
 * 
 * selection sort는 아직 정렬되지 않은 부분에서 가장 작은 값을 찾아서 
 * 정렬된 부분 가장 오른쪽에 추가(정렬되지 않은 부분 가장 왼쪽 자리와 바꿈)하는 것
 */

void PartialSelectionSort(vector<int>& arr, int k)
{
	Print(arr);

	for (int i = 0; i < k; i++)
	{
		// SelectionSortPass( TODO: );
		SelectionSortPass(arr, i, arr.size());
		Print(arr);
	}
}

int main()
{
	// vector<int> my_vector = { 7, 10, 4, 3, 20, 15 };
	random_device rd;
	mt19937 gen(rd());

	const int n = 20;
	vector<int> my_vector(n);
	
	uniform_int_distribution<int> value_distribution(1, 10);
	generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
	// int k = 1;
	// int k = 3;
	int k = 4;

	PartialSelectionSort(my_vector, k);

	int the_value = my_vector[k - 1];
	cout << my_vector[k - 1] << endl;

	sort(my_vector.begin(), my_vector.end());
	for (auto element : my_vector)
		std::cout << element << " ";
	std::cout << std::endl;
	
	assert(the_value == my_vector[k - 1]);
}