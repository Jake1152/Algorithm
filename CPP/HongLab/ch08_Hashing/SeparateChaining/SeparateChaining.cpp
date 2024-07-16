#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <list>
using namespace std;

/**
실행 예시
난수를 사용하기 때문에 달라질 수 있습니다.

0:
1:
2:
3:
4:
5: (327, 1)->(120, 1)->
6: (52, 1)->
7: (76, 1)->(237, 1)->
8: (330, 2)->(192, 1)-> // 생일이 330인 사람 2명
9: (78, 1)->
10: (240, 1)->(194, 1)->
11: (264, 1)->
12:
13:
14:
15: (360, 1)->(61, 1)->(84, 1)->(107, 1)->
16: (85, 1)->(269, 1)->
17: (109, 1)->
18:
19: (341, 1)->(249, 1)->
20:
21: (320, 1)->
22: (183, 1)->
1
50.62 % // 이론 추정치와 비슷합니다. 

*/

// Sedgewick Ch3.1 p.375
template<typename T_KEY, typename T_VALUE>
class SequentialSearch
{
public:
	struct Node
	{
		T_KEY key;
		T_VALUE value;
	};

	Node* Find(T_KEY key)
	{
		// TODO: 찾았을 경우 주소 반환

		// 못 찾았을 경우 nullptr 반환
		// 찾았는지 못 찾았는 지에 대한 대응을 호출한 쪽으로 넘기는 방식
		// std::map, std::unordered_map에서는 iterator를 반환

		// std::list<int>::iterator
		// for (auto iter = this->list.begin(); iter != this->list.end(); iter++)
		for (typename std::list<Node>::iterator iter = this->list.begin(); iter != this->list.end(); iter++)
		{
			if (iter->key == key)
				return &(*iter);
		}
		// cout << key << " was not found." << endl;

		return nullptr;
	}

	void Insert(Node n)
	{
		// 이미 있을 경우에는 추가 X
		if (this->Find(n.key))
			return ;
		
		// TODO: 키를 찾아봤는데 없으면 추가
		list.push_back(n);
	}

	void Reset()
	{
		list.clear();
	}

	void Print()
	{
		for (auto& n : list)
			cout << "(" << n.key << ", " << n.value << ")->";
		cout << endl;
	}

	int Size()
	{
		return int(list.size());
	}

private:
	list<Node> list;
};

template<typename T_KEY, typename T_VALUE>
class SeparateChaining
{
public:
	typedef typename SequentialSearch<T_KEY, T_VALUE>::Node Node;

	SeparateChaining(int c)
	{
		st.resize(c);
		Reset();
	}

	Node* Find(T_KEY k)
	{
		// TODO:
		const int key = HashFunc(k);

		return st.at(key).Find(k);
	}

	void Insert(Node n)
	{
		// TODO:
		if (this->Find(n.key))
			return ;
		const int key = HashFunc(n.key);
		st[key].Insert(n);
	}

	void Reset()
	{
		for (auto& s : st)
			s.Reset();
	}

	void Print()
	{
		for (int i = 0; i < st.size(); i++)
		{
			cout << i << ": ";
			st[i].Print();
		}
	}

private:
	vector<SequentialSearch<T_KEY, T_VALUE>> st;

	int HashFunc(int key)
	{
		return key % st.size(); // 가장 간단한 해시 함수 사용
	}

	// int Hash(string key){ /* string을 hash값으로 변환 */ }
};

int main()
{
	// 난수 생성기
	random_device rd;
	mt19937 g(rd());
	uniform_int_distribution<int>  dist(1, 365);

	// 모인 인원 수
	int num_people = 23;

	// 이상적인 해시 크기는 365가 아니라 저장하고 싶은 데이터 수인 사람 수
	SeparateChaining<int, int> map(23); // 버킷 수를 늘리면 충돌 감소

	// 한 번만 테스트
	{
		int samebirthday_count = 0;

		for (int i = 0; i < num_people; i++)
		{
			int birthday = dist(g);

			auto* n = map.Find(birthday);

			if (n) // 이미 키(key)가 존재할 경우
			{
				samebirthday_count += 1;
				n->value += 1;
			}
			else
				map.Insert({ birthday, 1 }); // {생일, 이 날이 생일인 사람의 숫자}
		}

		map.Print();

		cout << samebirthday_count << endl;
	}

	// 아래는 반복 테스트
	int num_try = 10000;
	int all_samebirthday_count = 0;

	for (int t = 0; t < num_try; t++)
	{
		int samebirthday_count = 0;

		for (int i = 0; i < num_people; i++)
		{
			int birthday = dist(g);

			auto* n = map.Find(birthday);

			if (n) // 이미 키(key)가 존재할 경우
			{
				samebirthday_count += 1;
				n->value += 1;
			}
			else
				map.Insert({ birthday, 1 }); // {생일, 이 날이 생일인 사람의 숫자}
		}

		if (samebirthday_count > 0)
			all_samebirthday_count += 1;

		map.Reset(); // 다음 테스트를 위해 초기화
	}

	std::cout << (all_samebirthday_count * 100.0 / num_try) << " % " << endl;

	return 0;
}