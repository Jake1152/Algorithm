#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Vertex
{
	Vertex(string k, int i)
	{
		key = k;
		index = i;
	}

	string key = "";
	int index = -1;  // 이 Vertex의 포인터가 저장된 vertices 배열의 인덱스
	bool visited = false;

	vector<Vertex*> out_neighbors;
};

class SymbolGraph
{
public:
	SymbolGraph(vector<string> keys)
	{
		this->table.clear();
		this->vertices.clear();
		this->vertices.reserve(keys.size());


		// TODO: vertices와 table 초기화
		// index는 keys에 들어오는 순서대로인가 아니면 'A' ~ 'Z' 사이의 알파벳 순서인가?
		for (size_t idx = 0; idx < keys.size(); idx++) {
			this->table.insert({keys[idx], idx});
			// this->table.insert(std::make_pair(keys[idx], idx));
			this->vertices.push_back(new Vertex(keys[idx], idx));
		}

		// 확인용
		for (auto v : this->vertices)
			cout << v->key << " " << v->index << endl;
		for (auto i : this->table)
			cout << i.first << " " << i.second << endl;
	}

	~SymbolGraph()
	{
		for (auto* v : this->vertices)
			delete v;
	}

	void AddDiEdge(string kv, string kw)
	{
		// TODO: table 이용
		// g.AddDiEdge("F", "B");
		// g.AddDiEdge("F", "G");

		// this->table.find(rv);
		
		// 
		/** 틀린 이유*/
		// this->vertices[this->table[kv]]->out_neighbors.push_back(new Vertex(kw, this->table[kw]));
		// 정답
		this->vertices[this->table[kv]]->out_neighbors.push_back(this->vertices[this->table[kw]]);
		// honglab way
		// AddDiEdge(table[kv], table[kw]);
	}

	void AddDiEdge(int v, int w) // 단방향 간선
	{
		this->vertices[v]->out_neighbors.push_back(vertices[w]);
	}

	void DFS(string k)
	{
		// TODO: table 이용
		DFS(this->table[k]);
	}

	void DFS(int source)
	{
		for (auto* v : this->vertices)
			v->visited = false;
		DFS(vertices[source]);
		cout << endl;
	}

	void DFS(Vertex* source)
	{
		source->visited = true;

		// Preorder
		// cout << source->key << " ";

		for (auto* w : source->out_neighbors)
			if (!w->visited)
				DFS(w);

		// Postorder
		cout << source->key << " ";
	}

private:
	vector<Vertex*> vertices;

	unordered_map<string, int> table; // key -> index
};

int main()
{
	SymbolGraph g({ "A", "B", "C", "D", "E", "F", "G", "H", "I" });

	g.AddDiEdge("F", "B");
	g.AddDiEdge("F", "G");
	g.AddDiEdge("B", "A");
	g.AddDiEdge("B", "D");
	g.AddDiEdge("D", "C");
	g.AddDiEdge("D", "E");
	g.AddDiEdge("G", "I");
	g.AddDiEdge("I", "H");

	g.DFS("F");

	return 0;
}
