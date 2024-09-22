#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node
{
	string data; // char보다 디버깅 편리
	int freq;
	Node* left = nullptr;
	Node* right = nullptr;
};

// std::priority_queue에서 사용할 MinHeapNode의 비교
struct Compare
{
	bool operator()(Node* l, Node* r)
	{
		// TODO:
		if (l->freq > r->freq)
			return true;
		return false;
	}
};

void PrintCodes(Node* root, string str)
{
	if (!root)
		return;

	if (!root->left && !root->right) // leaf node이면 출력
		cout << root->data << ": " << str << "\n";

	PrintCodes(root->left, str + "0");
	PrintCodes(root->right, str + "1");
}

void HuffmanCoding(vector<char> data, vector<int> freq)
{
	// freq가 작을 수록 우선순위가 높은 힙
	// struct Compare에서 우선순위 비교
	priority_queue<Node*, vector<Node*>, Compare> heap;

	for (int i = 0; i < data.size(); ++i)
		heap.push(new Node{ string(1, data[i]), freq[i] });
	

	while (heap.size() != 1)
	{
		Node* left, * right, * top;

		// TODO:
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();
		// new 할당 실패시에는 예외 발생, try-catch로 잡아주어야함
		top = new Node{ left->data + right->data, left->freq + right->freq };
		top->left = left;
		top->right = right;
		heap.push(top);
		cout << "(" << left->data << ", " << left->freq << ") + (" << right->data << ", " << right->freq << ") -> ";
		cout << "(" << top->data << ", " << top->freq << ")" << endl;
	}
	PrintCodes(heap.top(), "");
	/*
	*/

}

/**
 * 실행  예시
(f, 5) + (e, 9) -> (fe, 14)
(c, 12) + (b, 13) -> (cb, 25)
(fe, 14) + (d, 16) -> (fed, 30)
(cb, 25) + (fed, 30) -> (cbfed, 55)
(a, 45) + (cbfed, 55) -> (acbfed, 100)
a: 0
c: 100
b: 101
f: 1100
e: 1101
d: 111
 */

int main()
{
	vector<char> data = { 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<int> freq = { 45, 13, 12, 16, 9, 5 };

	HuffmanCoding(data, freq);

	return 0;
}