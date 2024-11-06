#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Sedgewick Algorithm 5.4 Trie symbol table
class Trie
{
public:
	static const int R = 128; // ASCII table 0 이상 127 이하

	struct Node
	{
		vector<Node*> children; // 다음 글자에 대응하는 노드에 대한 포인터 (map<char, Node*> children; 으로도 구현 가능)
		string value;           // 리프(leaf)가 아니어도 (자식이 있어도) 값 저장 가능

		Node()
		{
			children.resize(R, nullptr); // 자식 노드 최대 R개
		}
	};

	Node* root = nullptr;

	~Trie()
	{
		DeleteAll();
	}

	// DeleteAll()과 Size()는 앞에서 공부했던 다른 트리들과 비교해보는 용도입니다.

	void DeleteAll() // 모든 노드 삭제
	{
		DeleteAll(root);
	}

	void DeleteAll(Node*& n)
	{
		if (n) // if(n != nullptr)
		{
			for (int c = 0; c < R; c++)
				DeleteAll(n->children[c]);
			delete n;
			n = nullptr;
		}
	}

	int Size() // 단어가 몇 개 추가되었는지를 세어서 반환
	{
		return Size(root);
	}

	int Size(Node* n)
	{
		if (n == nullptr) return 0; // if(!n)

		int count = 0;

		if (!n->value.empty()) // 값이 저장된 노드
			count++;

		for (auto* n : n->children)
			count += Size(n);

		return count;
	}

	// 재귀호출을 사용하지 않는 삽입(insert)
	void IterInsert(string key, string val)
	{
		if (root == nullptr)
			root = new Node;

		Node* node = root;

		// std::cout << "key : " << key << std::endl;
		for (char ch : key)
		{
			// std::cout << "ch : " << ch << std::endl;
			// std::cout << "n->value  : " << n->value  << ", in IterInsert()" << std::endl;

			// TODO: 필요한 경우 새로운 자식 노드 생성
			if (node->children.at(ch) == nullptr)
				node->children.at(ch) = new Node;
			node = node->children.at(ch); // n = n->children[c];

			// 보충
			// - children.at(c)는 children[c]와 같은 기능을 합니다.
			// - at()은 []와 달리 인덱스의 범위를 확인하기 때문에 디버깅에 유리합니다.
		}
		// std::cout << "val in IterInsert(): " << val << std::endl;
		node->value = val; // 키(key)의 마지막 글자에 해당하는 노드에는 값(value) 저장
	}

	string IterSearch(string key)
	{
		// 키(key)를 찾았을 경우에는 값(value) 문자열을 반환
		// 키(key)를 찾지 못했을 경우에는 빈 문자열(string(""))을 값(value)으로 반환
		// 키의 마지막 글자에 해당하지 않는 노드의 value는 빈 문자열

		if (root == nullptr)
			return string("");

		Node* node = root;

		for (char ch : key)
		{
			if (node->children.at(ch))
				node = node->children.at(ch);
		}
		return static_cast<string>(node->value);
	}

	// 재귀호출을 사용하는 삽입(Insert)
	void Insert(string key, string val)
	{
		root = Insert(root, key, val, 0);
	}

	Node* Insert(Node*& n, string key, string val, int d)
	{
		if (!n) n = new Node; // Node*& 포인터에 대한 참조 사용

		if (d == key.length())
		{
			// TODO: 해당 노드에 val 저장
			return n;
		}

		// TODO: 다음 글자로 진행 (주의: d + 1)

		return n;
	}

	string Search(string key)
	{
		Node* n = Search(root, key, 0);

		if (!n) return string("");

		return n->value;
	}

	Node* Search(Node* n, string key, int d)
	{
		// 마지막 글자의 노드 포인터 반환
		// 찾지 못했다면 nullptr 반환
		if (n->children.at(key[d]))
			return Search(n->children.at(key[d]), key, d + 1);
		return n;
	}

	// 저장되어 있는 모든 키들을 찾아서 반환
	vector<string> Keys()
	{
		// 편의상 KeysWithPrefix()를 사용

		return KeysWithPrefix(string("")); // Prefix가 빈 문자열인 경우
	}

	vector<string> KeysWithPrefix(string pre)
	{
		vector<string> keys;

		// Search()로 키(key)가 pre인 노드를 찾고
		Node* n = Search(root, pre, 0);

		// 그 자식 노드들을 모두 모아서 반환
		Collect(n, pre, keys);

		return keys;
	}

	void Collect(Node* n, string pre, vector<string>& keys)
	{
		if (!n) return;

		// cout << "pre : " << pre << endl;
		if (n->value.empty() == false) keys.push_back(pre);

		for (int c = 0; c < R; c++)
		{
			// TODO: Collect(...)
			if (n->children.at(c))
				Collect(n->children.at(c), n->children.at(c)->value, keys);
		}
	}

	/** LongestPrefixOf(string s)
	 * 인자로 주어진 문자열에서 현재 dict에 있는 값 중 가장 많이 일치하는 문자열을 찾아서 return 한다.
	 * 1. SearchPrefix()를 이용해서 가장 많은 공통 부분을 갖는 문자열의 길이를 알아낸다.
	 * 2. 알아낸 문자열의 길이를 가지고 인자로 주어진 문자열에서 그 길이 만큼 잘라서 return 한다.
	 */
	string LongestPrefixOf(string s)
	{
		int l = SearchPrefix(root, s, 0, 0);
		return s.substr(0, l);
	}

	/** SearchPrefix(Node* node, string str, int d, int longest_prefix_size)
	 * 인자로 주어진 문자열에서 앞부분이 일치하는 문자열의 길이를 알아낸다.
	 * 1. 다음 문자 노드가 null이면 longest_prefix_size를 return 한다.
	 * 2. n->value가 비어있지 않다면 key의 마지막 글자이므로 longest_prefix_size에 현재 문자열의 길이를 저장한다.
	 * 3. 현재 문자열의 길이와 찾고자 하는 문자열의 길이가 같다면 더 이상 진행할 필요가 없으므로 longest_prefix_size를 return 한다.
	 * 4. 가장 최근에 찾은 문자 노드, 찾고자 하는 문자열, 현재까지 찾은 문자열 길이 + 1, longest_prefix_size를 인자로해서 SearchPrefix()를 재귀호출한다.
	 *    즉, return SearchPrefix() 형태이어야 한다.
	 */
	int SearchPrefix(Node* node, string str, int d, int longest_prefix_size)
	{
		// l은 지금까지 찾은 가장 긴 prefix의 길이

		if (node == nullptr) return longest_prefix_size;

		// TODO: n->value가 비어있지 않다면 key의 마지막 글자라는 의미니까 l에 d를 기록
		if (node->value.empty() == false)
			longest_prefix_size = d;

		// TODO: d와 str.length()가 같다면 더 진행할 필요가 없으니까 l 반환
		if (str.length() == d)
			return longest_prefix_size;

		char ch = str.at(d); // s[d]

		return SearchPrefix(node->children[ch], str, d + 1, longest_prefix_size);
	}

	/** KeysThatMatch(string pattern)
	 * 패턴이 일치하는 문자열을 찾아서 return한다.
	 * 와일드카드도 가능!
	 * 
	 * keys vector에 pattern에 해당하는 단어들을 추가한다.
	 */
	vector<string> KeysThatMatch(string pattern)
	{
		vector<string> keys;

		CollectMatch(root, string(""), pattern, keys);

		return keys;
	}

	/**
	 * nullptr
	 *   |
	 *  'a'
	 *   |
	 *  'n'
	 *   |
	 *   
	 */
	void CollectMatch(Node* node, string pre, string pattern, vector<string>& keys)
	{
		if (!node) return;

		int d = int(pre.length());

		// wildcard 케이스는 어떻게 처리할 것인가?
		if (d == pattern.length() && node->value.empty() == false)
			keys.push_back(pre);

		if (d == pattern.length()) return;

		char next = pattern.at(d);

		if (next == '?')
		{
			// TODO: ? 자리에 어떤 글자든지 들어올 수 있다 -> 모든 글자에 대해 재귀 호출
			for (int i = 0; i < this->R ; i++)
				if (node->children.at(i))
					CollectMatch(node->children.at(i), pre + static_cast<char>(i), pattern, keys);
			// # TODO: ? 자리에 아무 글자도 안들어올 수도 있지만, 그런 케이스를 감안하게 되면 중복이 발생할 수 있다.
			// const string pre_str = pattern.substr(0, d);
			// const string post_str = pattern.substr(d+1, pattern.length());
			// const string new_pattern = pre_str + post_str;
			// CollectMatch(node, pre, new_pattern, keys); // <= ?가 들어가는 패턴길이를 줄이면서 재귀 호출하는 방법('?' 개수에 따라 중복 발생 가능)
			// cout << "pattern : " << pattern << endl; 
			// cout << "pre_str : " << pre_str << "\t,d : " << d << endl; 
			// cout << "post_str : " << post_str << "\t,d+1 : " << d+1<< endl;
			// cout << "new_pattern : " << new_pattern << endl << endl; 
		}
		else if (next == '*')
		{
			// 참고: https://www.geeksforgeeks.org/wildcard-character-matching/  
			//      https://github.com/TeodorDyakov/wildcard-trie/blob/master/src/main/java/trie/Trie.java

			// 난이도가 높은 도전 문제입니다. 

			// TODO:
			for (int i = 0; i < this->R ; i++)
			{
				// CollectMatch(node->children.at(i), pre + static_cast<char>(i), pattern, keys);
				// CollectMatch(node->children.at(i), pre, pattern, keys);
			}
		}
		else // "she"
		{
			
			// TODO: 그 외의 일반적인 알파벳일 경우
			if (node->children.at(next))
				CollectMatch(node->children.at(next), pre + next, pattern, keys);
		}
	}

	void Delete(string key)
	{
		root = Delete(root, key, 0); // root가 삭제될 경우 새로운 root 대입
	}

	bool IsEmpty(Node* n) // 자식이 하나도 없으면 true
	{
		for (int i = 0; i < R; i++)
			if (n->children[i])
				return false;
		return true;
	}

	Node* Delete(Node* n, string key, int d)
	{
		if (!n) return nullptr;

		if (d == key.length())
		{
			n->value = string(""); // 키(key)와 값(value) 삭제
		}
		else
		{
			char c = key.at(d);
			n->children[c] = Delete(n->children[c], key, d + 1);
		}

		//if ( TODO: 자식이 하나도 없고 value도 비어있다면)
		//{
		//	// TODO: 메모리 삭제
		//	n = nullptr;
		//}

		return n;
	}

	// 아래는 디버깅을 위한 트리구조 출력

	void Display2D()
	{
		vector<string> screen(Height(), string(Width(root) * 6, ' '));
		Display2D(root, 0, 0, screen);
		for (auto& s : screen) cout << s << endl;
	}

	void Display2D(Node* n, int x, int level, vector<string>& screen)
	{
		if (!n) return;
		for (int c = 0; c < R; c++)
			if (n->children[c])
			{
				screen[level][3 * x] = char(c);
				if (n->children[c]->value.empty() == false)
					screen[level][3 * x + 1] = '*';
				Display2D(n->children[c], x, level + 1, screen);
				x += Width(n->children[c]);
			}
	}

	int Height()
	{
		return Height(root);
	}

	int Height(Node* n)
	{
		if (!n) return 0;
		int cnt = 0;
		for (auto* c : n->children)
			cnt = std::max(cnt, Height(c));
		return 1 + cnt;
	}

	int Width(Node* n)
	{
		vector<int> w(Height(n), 0);
		WidthHelper(n, w, 0);
		return *std::max_element(w.begin(), w.end());
	}

	void WidthHelper(Node* n, vector<int>& w, int level)
	{
		for (int c = 0; c < R; c++)
			if (n->children[c])
			{
				w[level] += 1;
				WidthHelper(n->children[c], w, level + 1);
			}
		w[level] = std::max(1, w[level]);
	}
};

void run_dict(); // 함수 구현은 main() 아래에

int main()
{
	// 기본 사례
	{
		// Trie에 추가할 단어들
		vector<string> words = { "and", "ant", "do", "dad", "ball", "she", "shells" };

		Trie trie;

		// 키(key) 추가
		for (auto w : words)
		{
			trie.IterInsert(w, w + "_value"); 
			//trie.Insert(w, w + "_value"); // _value는 디버깅을 위한 임시 값(value) (뒤에서는 사전의 내용)
		}

		// 모든 키 출력
		// and ant ball dad do she shells <- 알파벳 순서로 정렬되어서 출력됩니다.
		cout << "Keys()" << endl;
		for (const auto& k : trie.Keys())
			cout << k << " ";
		cout << endl << endl;

		// 트리 구조 확인
		cout << "Display2D()" << endl;
		trie.Display2D();
		cout << endl;

		// 키 탐색
		// do : do_value     <- do를 찾아서 do_value 출력
		// dad : dad_value
		// hello : Not found <- 삽입하지 않았기 때문에 찾지 못함

		cout << "Search" << endl;
		for (auto w : vector<string>{ "do", "dad", "hello" })
		{
			// string value = trie.IterSearch(w); // string value = trie.Search(w);
			string value = trie.Search(w);
			if (value.empty()) value = "Not found"; // 반환 문자열이 비어있다면 못 찾은 상황
			cout << w << " : " << value << endl;
		}
		cout << endl;

		// 특정 문자열로 시작하는 키 검색
		// dad do <- "d"로 시작하는 단어들이 모두 출력
		cout << "KeysWithPrefix()" << endl;
		// for (const auto& k : trie.KeysWithPrefix("a"))
		for (const auto& k : trie.KeysWithPrefix("d"))
		{
			cout << k << " ";
		}
		cout << endl << endl;

		// 앞 부분이 겹치는 가장 긴 단어 출력
		cout << "LongestPrefixOf()" << endl;
		cout << trie.LongestPrefixOf("she") << endl;       // she
		cout << trie.LongestPrefixOf("shell") << endl;     // she
		cout << trie.LongestPrefixOf("shellsort") << endl; // shells
		cout << trie.LongestPrefixOf("shallow") << endl;   // 공백(찾지 못함)
		cout << endl;

		// 와일드카드(wildcard) ? 테스트
		// ? 자리에 어떤 글자든지 들어갈 수 있음
		// "an?" 에서 ? 자리가 각각 d와 t인 "and" 와 "ant" 출력

		/**
		 *  an? an??
		 * an으로만 끝나도 된다면?
		 * 중복 발생가능
		 */
		cout << "KeysThatMatch()" << endl;
		// for (const auto& k : trie.KeysThatMatch("ant"))
		// for (const auto& k : trie.KeysThatMatch("an?"))
		for (const auto& k : trie.KeysThatMatch("an????"))
		{
			cout << k << " ";
		}
		cout << endl << endl;

		// 키 삭제
		cout << "Delete()" << endl;
		for (auto w : vector<string>{ "and", "ant", "ball", "she" })
		{
			cout << "Delete: " << w << endl;
			trie.Delete(w);
			trie.Display2D(); // 트리구조가 어떻게 달라지는 지 실행 예시에서 보세요
		}
		cout << endl << endl;

		// 삭제 후 키 출력 (삭제된 단어들은 출력되지 않음)
		cout << "Keys() after Delete()" << endl;
		for (const auto& k : trie.Keys())
			cout << k << " ";
		cout << endl << endl;
		/*

		*/
	}

	// 와일드카드 * 테스트
	// * 자리에는 어떤 문자열이든지 들어갈 수 있습니다. 아무 글자도 들어가지 않을 수도 있습니다.
	// 예시) "ab*cd"에서 *자리에 
	//      아무 글자도 들어가지 않으면 abcd 
	//      "1"이 들어가면 "ab1cd" 
	//      "12"가 들어가면 "ab12cd" 
	//      "123"이 들어가면 "ab123cd"
	{
		Trie trie;

		for (string w : {"abcd", "ab1cd", "ab12cd", "ab123cd"})
			trie.IterInsert(w, w + "_value");

		cout << "KeysThatMatch(\"ab*cd\")" << endl;
		for (const auto& k : trie.KeysThatMatch("ab*cd"))
		{
			cout << k << " ";
		}
		cout << endl << endl;
	}

	// 영어 사전 (사전 파일을 읽어들이는 데에 시간이 약간 걸립니다.)
	// run_dict();


	return 0;
}

void run_dict()
{
	Trie trie;

	ifstream ifile("./eng_dic.txt");
	int count = 0;
	while (ifile)
	{
		string key, value; // char key[1024], value[1024];
		getline(ifile, key); //ifile.getline(key, sizeof(key));
		getline(ifile, value); //ifile.getline(value, sizeof(value));

		if (!key.empty())
		{
			trie.Insert(key, value); // trie에 추가
			count++;
		}
	}
	ifile.close();
	cout << "Inserted " << count << " keys" << endl;

	while (true)
	{
		string word; // char word[1024];
		cout << "Input a word : ";
		cin >> word;

		vector<string> keys = trie.KeysThatMatch(word);

		if (!keys.empty())
			for (string k : keys)
				cout << k << " : " << trie.Search(k) << endl;
		else
			cout << "Not found" << endl;
		cout << endl;
	}
}


			// 힌트: 3가지 경우에 대해 CollectMatch()를 재귀호출합니다.
			// 1. * 자리에 글자가 없는 경우 (예: wor*d로 word를 찾음)
			// 2. * 자리에 ?처럼 어떤 글자든지 들어갈 수 있는 경우
			// 3. * 자리에 여러 글자가 들어가는 경우 (예: wor*d로 world, worried 등을 찾음)
