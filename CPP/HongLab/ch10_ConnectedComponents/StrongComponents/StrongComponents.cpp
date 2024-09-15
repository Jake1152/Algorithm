
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Vertex*> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
	vector<Vertex*> in_neighbors;  // 들어오는 방향의 이웃 vertex들에 대한 포인터
};

class Graph
{
public:
	Graph(int num_vertices)
	{
		vertices.resize(num_vertices);
		for (int i = 0; i < num_vertices; i++)
			vertices[i] = new Vertex(i);
	}

	~Graph()
	{
		for (auto* v : vertices)
			delete v;
	}

	void AddDiEdge(int v, int w) // 단방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->in_neighbors.push_back(vertices[v]);
	}

	bool HasPath(int start, int target)
	{
		for (auto* v : this->vertices)
			v->visited = false;
		return HasPathHelper(this->vertices[start], this->vertices[target]);
	}

	/**
	 * 1 -> 4번이 연결되었는지, 확인
	 * 1에서 4번으로 연결 되었는지(연결이 되었건, 아니건) 
	 * 확인되었다면, 
	 * 4 -> 1번으로 연결되었는지는 확인 필요
	 */
	void BruteForceStrongComponents()
	{
		int count = 0;
		vector<int> id(vertices.size(), -1);

		// TODO: HasPath()를 이용해서 서로 강하게 연결된 요소들을 찾습니다.
		/**
		 * 각 노드에서 전부 강한 연결이 되는지 확인해본다.
		 */
		for (const auto v : this->vertices)
		{
			for (const auto neighbor : v->in_neighbors)
			{
				std::cout << "neighbor->value : " << neighbor->value << std::endl;
				std::cout << "#count : " << count << std::endl;
				if (HasPath(v->value, neighbor->value) == true);
					count++;
				std::cout << std::endl;
			}
		}
		std::cout << "count : " << count << std::endl;

		// 결과 정리 후 출력
		// vector<vector<int>> components(count);
		// for (int s = 0; s < vertices.size(); s++)
		// 	components[id[s]].push_back(s);
		// cout << count << " strong components" << endl;
		// for (int i = 0; i < components.size(); i++)
		// {
		// 	cout << "Strong component " << i + 1 << ": ";
		// 	for (auto v : components[i])
		// 		cout << v << " ";
		// 	cout << endl;
		// }
	}

private:
	vector<Vertex*> vertices;

	bool HasPathHelper(Vertex* v, Vertex* t)
	{
		// TODO: DFS 방식으로 v와 t가 만날 수 있는 지를 확인합니다.
		v->visited = true;
		std::cout << "source : " << v->value << std::endl;
		std::cout << "target : " << t->value << std::endl;
		if (v->value == t->value)
			return true;
		for (const auto neighbor : v->out_neighbors)
		{
			if (neighbor->visited == false)
				return HasPathHelper(neighbor, t);
		}
		return false;
	}
};

int main()
{
	// Sedgewick p569
	// 방향(directed) 그래프
	vector<vector<int>> edges = {
		{4, 2}, {2, 3}, {3, 2}, {6, 0}, {0, 1}, {2, 0}, {11, 12}, {12, 9}, {9, 10},
		{9, 11}, {7, 9}, {10, 12}, {11, 4}, {4, 3}, {3, 5}, {6, 8}, {8, 6}, {5, 4},
		{0, 5}, {6, 4}, {6, 9}, {7, 6} };

	Graph g(13);

	for (vector<int>& p : edges)
		g.AddDiEdge(p[0], p[1]);

	g.BruteForceStrongComponents();

	return 0;
}