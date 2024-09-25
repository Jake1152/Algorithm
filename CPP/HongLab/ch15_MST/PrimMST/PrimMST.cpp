#include <iostream>
#include <vector>
#include <limits>
#include "../../ch11_WeightGraph/IndexMinPQ/IndexMinPQ.h"

using namespace std;

constexpr double kInf = numeric_limits<double>::infinity();

struct DirectedEdge
{
	int u;         // 간선 시작(edge tail, 화살표 꼬리) 정점의 인덱스
	int v;         // 간선 끝(edge head, 화살촉) 정점의 인덱스
	double weight; // edge weight (여기서는 u-v 이동 비용)
};

class EdgeWeightedDigraph
{
public:
	vector<vector<DirectedEdge>> adj;

	EdgeWeightedDigraph(int num_vertices)
	{
		this->adj.resize(num_vertices);
	}

	void AddBiEdge(DirectedEdge e) // 양방향(무방향)
	{
		this->adj[e.u].push_back(e);
		// 건너편 노드에서는 시작, 끝 정점이 바뀌어 들어가야 하므로 아래와 같이 입력하여 처리
		this->adj[e.v].push_back({ e.v, e.u, e.weight });
	}

	vector<DirectedEdge>& Adj(int v)
	{
		return this->adj[v];
	}

	void PrimMST()
	{
		int V = int(this->adj.size());

		vector<double> key(V, kInf);     // dist in Sedgewick Algorithm 4.7, key in CLRS p. 596
		vector<int> pre(V);              // pi in CLRS

		double cost_sum = 0.0;

		key[0] = 0.0;
		pre[0] = -1;

		IndexMinPQ<double> pq(V);

		// TODO: 우선순위큐에다가 일단 모든 정점의 인덱스를 넣는다.
		//       위에서 key[0] = 0.0 이기 때문에 0번이 가장 위로 온다.
		for (size_t idx = 0; idx < V; idx++)
			pq.Insert(idx, key[idx]);

		while (!pq.Empty())
		{
			// 가중치가 가작 작은 정점을 뺀다.
			int u = pq.DelMin();
			// cout << "current vertex : " << u << endl;

			if (pre[u] >= 0)
			{
				cost_sum += key[u];
				cout << pre[u] << " - " << u << " : " << key[u] << endl;
			}

			/**
			 * 큐에 있는 이웃 정점들의 값을 갱신한다.
			 * key[idx]에 있는 값을 기준으로 힙 정렬 되므로, 
			 * 이웃 정점들의 key[idx] 값을 바꾼다.
			 * 
			 * pre를 어떻게 쓸 것인가?
			 */
			// 현재 연결된 정점의 이웃 정점들
			for (DirectedEdge& e : Adj(u))
			{
				int v = e.v;
				double weight = e.weight; // u-v 간선 비용

				// pq.keyOf(v);
				// pq.ChangeKey(v, weight);
				// if( TODO: v가 pq안에 아직 있는지 && u-v 비용이 더 적은지)
				// TO KNOW: u-v 비용이 더 적은지, 무엇을 의미하는가?
				if (pq.Contains(v) && key[v] > weight)
				{
					pre[v] = u;
					key[v] = weight;
					pq.ChangeKey(v, weight);
				}
			}
		}

		cout << cost_sum << endl;
	}
};

int main()
{
	vector<DirectedEdge> edges =
	{
		// 시작 정점, 끝 정점, 비용 
		{ 0, 1, 4.0 },
		{ 0, 7, 9.0 },
		{ 1, 2, 8.0 },
		{ 1, 7, 11.0 },
		{ 2, 3, 7.0 },
		{ 2, 5, 4.0 },
		{ 2, 8, 2.0 },
		{ 3, 4, 9.0 },
		{ 3, 5, 14.0 },
		{ 4, 5, 10.0 },
		{ 5, 6, 2.0 },
		{ 6, 7, 1.0 },
		{ 6, 8, 6.0 },
		{ 7, 8, 7.0 },
	};

	// 정점의 개수를 파라미터로 전달
	EdgeWeightedDigraph g(9);

	// 가중치가 있는 양방향 그래프, 정점 연결 처리
	for (auto e : edges)
	{
		g.AddBiEdge(e);
	}

	// 신장 트리로 만듦, 모든 정점을 하나의 트리로 연결(싸이클이 형성되어서는 안됨)
	g.PrimMST();

	return 0;
}