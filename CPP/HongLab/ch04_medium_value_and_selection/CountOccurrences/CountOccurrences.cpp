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
    
	/*
	int count = 0;
	//TODO: O(n)
    for (auto element : arr)
        if (target == element)
            count++;
	return count;
	*/

	// # honglab
	// 무식하게(brute-force) 하나하나 찾아보는 방식입니다.
    int c = 0;
    for (const auto& v : arr)
        if (v == target) c += 1;
    return c;

}


// # mine
/** Binary Search, 
 * x값의 시작 위치를 찾아야한다.
 * 1 1 3 3 3 4 4 5 6 7 7 7 7 7 8 8 8 9 10 10 
 *     a b c
 * 
 * 이분탐색에서 3 b, 3 c를 찾았다 했을 때,  3 a부터 시작되어야한다.
 * 작아지기 직전까지 가야한다.
 * 
 */
/*
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
*/

// # honglab way
int BinarySearch(const vector<int>& arr, int lo, int hi, int x)
{
    while (lo <= hi)
    {
        int middle = lo + (hi - lo) / 2;
        if (x < arr[middle])        hi = middle - 1;
        else if (x > arr[middle])   lo = middle + 1;
        else                        return middle;
    }
    return -1; // Not found
}
// O(log(n) + count)
int Count2(const vector<int>& arr, int x)
{
    const int n = arr.size();
    int i = BinarySearch(arr, 0, n - 1, x); // 이진탐색으로 아무거나 하나 찾음, O(log(n))

    if (i == -1) return 0; // 하나도 없다면 0개 반환

    // 정렬된 상태라는 것을 이용

    int count = 1; // 여기까지 왔다면 하나는 찾았음
    int left = i - 1; // 왼쪽(인덱스가 작은쪽)으로 가면서 이웃하는 개수 세기
    while (left >= 0 && arr[left] == x)
    {
        count++;
        left--;
    }

    int right = i + 1; // 오른쪽(인덱스가 큰 쪽)으로 가면서 세기
    while (right < n && arr[right] == x)
    {
        count++;
        right++;
    }

    return count;
}

// # mine
/**
 * target이랑 일치하는 값을 가진 위치 중 가장 왼쪽과 가장 오른쪽을 찾아서 둘의 차를 구한다.
 */
/*
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
*/

// # Honglab
int FindFirst(const vector<int>& arr, int lo, int hi, int x);
int FindLast(const vector<int>& arr, int low, int high, int x);

int Count3(const vector<int>& arr, int x)
{
    // 정렬되어 있기 때문에 처음과 시작을 찾으면(=구간을 찾으면) 하나하나 세지 않아도 됩니다.
    int first = FindFirst(arr, 0, arr.size() - 1, x); // 주의: 이진탐색의 변형

    if (first == -1)
        return 0;

    int last = FindLast(arr, first, arr.size() - 1, x); // 주의: 이진탐색의 변형
    return last - first + 1; // <- 생각해봅시다
}

int FindFirst(const vector<int>& arr, int lo, int hi, int x)
{
    // 이진탐색이 살짝 변형된 형태
    if (hi >= lo)
    {
        int n = arr.size();
        int mid = lo + (hi - lo) / 2;
        if ((mid == 0 || x > arr[mid - 1]) && arr[mid] == x) // 첫번째를 찾아들어가기 위한 조건
            return mid;
        else if (x > arr[mid])
            return FindFirst(arr, (mid + 1), hi, x);
        else
            return FindFirst(arr, lo, (mid - 1), x);
    }
    return -1;
}

int FindLast(const vector<int>& arr, int low, int high, int x)
{
    if (high >= low)
    {
        int n = arr.size();
        int mid = (low + high) / 2;
        if ((mid == n - 1 || x < arr[mid + 1]) && arr[mid] == x)
            return mid;
        else if (x < arr[mid])
            return FindLast(arr, low, (mid - 1), x);
        else
            return FindLast(arr, (mid + 1), high, x);
    }
    return -1;
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