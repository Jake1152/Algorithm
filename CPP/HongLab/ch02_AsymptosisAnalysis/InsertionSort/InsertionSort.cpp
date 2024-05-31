#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool CheckSorted(vector<int>& arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(vector<int>& arr)
{
	for (auto v : arr)
		cout << v << " ";
	cout << endl;
}

int main()
{
	// vector<int> a = { 6, 5, 4, 3, 2, 1 };
	vector<int> a = { 6, 4, 3, 8, 5 };

	int N = a.size();
	for (int idx_i = 1; idx_i < N; idx_i++)
	{
		// TODO: 딱 2줄만 사용
		for (int idx_j = idx_i; idx_j > 0 && a[idx_j - 1] > a[idx_j]; idx_j--)
			std::swap(a[idx_j - 1], a[idx_j]);
		Print(a);
	}
	std::cout << std::endl;
	Print(a);
}
