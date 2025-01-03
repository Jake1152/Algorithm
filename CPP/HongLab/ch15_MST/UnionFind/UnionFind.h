#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std; // 편의용

class UnionFind
{
public:
	vector<int> group;
	int num_groups;

	UnionFind(int N)
		: group(N), num_groups(N)
	{
		for (int i = 0; i < this->group.size(); i++)
			this->group[i] = i;
	}

	int NumGroups()
	{
		return this->num_groups;
	}

	bool Connected(int p, int q)
	{
		return Find(p) == Find(q);
	}

	/* Quick-Find 방식: Union()에서 미리 정리하기 때문에 Find()는 빠름 */
	// int Find(int p)
	// {
	// 	return this->group[p];
	// }

	/*
		대한민국 - 서울
		서울 - 도봉
		=> 	   대한민국 - 도봉
		      

		대한민국 - 경기도
		경기도 - 성남
		성남 - 판교	
		대한민국 - 판교
		대한민국 - 경기도
		대한민국 - 성남
	*/


	/**
	 * 대한민국 - 성남 - 판교 
	 *    대한민국 - 성남
	 *    대한민국 - 판교
	 * 
	 * 서울 - 도봉 
	 */
	// void Union(int p, int q)
	// {
	// 	int pid = Find(p); // pid 성남
	// 	int qid = Find(q); // qid 서울

	// 	if (pid == qid) return;

	// 	for (int i = 0; i < this->group.size(); i++)
	// 	{
	// 		// TODO:
	// 		if (this->group[i] == pid)
	// 			this->group[i] = qid;
	// 	}

	// 	this->num_groups--;
	// }

	/* Quick-Union 방식: Union()은 빠르고 Find()할 때 정리 */
	/* 
	*/

	int Find(int p)
	{
		while (p != this->group[p])
		{
			// TODO:
			p = this->group[p];
		}

		return p;
	}

		// 대한민국 - 서울
		// 서울 - 도봉
		// => 	   대한민국 - 도봉

		// 대한민국 - 경기도
		// 경기도 - 성남
		// 성남 - 판교	
	void Union(int p, int q)
	{
		int i = Find(p);
		int j = Find(q);
		if (i == j) return;

		this->group[i] = j;

		this->num_groups--;
	}

	void Print()
	{
		cout << "Num groups = " << NumGroups() << endl;

		cout << "Index:";
		for (int i = 0; i < this->group.size(); i++)
			cout << setw(3) << i;
		cout << endl;

		cout << "Group:";
		for (auto i : group)
			cout << setw(3) << i;
		cout << endl;
	}
};
