#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item
{
	double value;
	double weight;
};

void Print(vector<Item>& items)
{
	for (auto i : items)
	{
		// (가성비 = value/weight = ratio, value, weight)
		cout << "(" << i.value / i.weight << ", " << i.value << ", " << i.weight << ") ";
	}
	cout << endl;
}

bool Compare(struct Item a, struct Item b)
{
	double ratio_a = a.value / a.weight;
	double ratio_b = b.value / b.weight;

	return ratio_a > ratio_b; // ratio가 큰 쪽이 앞으로 오도록 정렬
}

double FractionalKnapsack(vector<Item> items, double W)
{
	sort(items.begin(), items.end(), Compare); // Compare() 함수를 이용해서 정렬

	cout << "W = " << W << endl;
	Print(items);

	double vsum = 0.0;

	/**
	 * weight에 반영된 item은 제거하거나
	 * item의 가치를 무한대로 만든다.
	 * for문만 돌아도 충분히 계산가능.
	 * 전체 아이템 수이기에 이미 계산된 item을 리스트에서 제외할 필요는 없다.
	 * 
	 * 무게 단위별로 가져올 수 있다는 특징이 있다
	 * 가치 6짜리 아이템의 무게가 2일 때
	 * 무게 1을 가져오고 가치 3을 얻을 수 있다.
	 */
	for (auto& i : items)
	{
		// TODO:
		/**
		 * min(현재 베낭 남은 무게, 아이템 무게)
		 * 몫 * 가치 
		 */
		if (W <= 0)
			break ;
		const size_t available_weight = min(W, i.weight);
		std::cout << "W : " << W << std::endl;
		W -= available_weight;
		std::cout << "available_weight : " << available_weight << std::endl;
		const double ratio_item = i.value / i.weight;
		vsum += ratio_item * available_weight;
	}

	return vsum;
}

int main()
{
	double W = 6.0;

	vector<Item> items = { { 10, 1 }, { 28, 4 }, { 12, 2 }, { 12, 3 } };

	cout << FractionalKnapsack(items, W) << endl;

	return 0;
}