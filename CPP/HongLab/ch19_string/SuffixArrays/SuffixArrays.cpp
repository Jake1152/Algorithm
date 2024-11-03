#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <set>
#include <cstring>

using namespace std;

class SuffixArray
{
public:
	string _txt;
	vector<int> _sa;

	SuffixArray(string txt)
		: _txt(txt)
	{
		BuildSuffixArray();
	}

	void BuildSuffixArray()
	{
		this->_sa.resize(this->_txt.size()); // suffix array

		for (int i = 0; i < this->_txt.size(); i++)
			this->_sa[i] = i;

		cout << "Before sorting" << endl;
		for (int i = 0; i < this->_sa.size(); i++)
			cout << setw(3) << i << " : " << setw(3) << this->_sa[i] << " : " << this->_txt.substr(this->_sa[i], this->_sa.size() - this->_sa[i]) << endl;
		cout << endl;

		// for (vector<int>::iterator iter = this->_sa.begin(); iter != this->_sa.end(); iter++)
		// 	cout << "*iter : " << *iter << endl;

		sort(this->_sa.begin(), this->_sa.end(),
			[&](int a, int b) {
				// cout << "a : " << a << ",b : " << b << endl;
				// cout << "this->_txt.c_str() : " << this->_txt.c_str() << endl;
				// cout << "this->_txt.c_str()[this->_sa[a]] : " << this->_txt.c_str()[this->_sa[a]] << endl; 
				// cout << "this->_txt.c_str()[this->_sa[b]] : " << this->_txt.c_str()[this->_sa[b]] << endl; 
				// cout << "this->_txt.c_str()[a] : " << this->_txt.c_str()[a] << endl; 
				// cout << "this->_txt.c_str()[b] : " << this->_txt.c_str()[b] << endl; 
				// return strcmp(&this->_txt.c_str()[a], &this->_txt.c_str()[b]) < 0;
				return strcmp(&this->_txt.c_str()[a], &this->_txt.c_str()[b]) < 0;
				// return strcmp(&this->_txt.c_str()[this->_sa[a]], &this->_txt.c_str()[this->_sa[b]]) < 0;
				// return static_cast<bool>(strcmp(&this->_txt.c_str()[this->_sa[a]], &this->_txt.c_str()[this->_sa[b]])) == false;
				// return false; // TODO: strcmp() 사용
				// strcmp(&this->_txt.c_str()[this->_sa[mid]], pattern.c_str()); // 힌트로 사용하세요
			}
		);

		cout << "After sorting" << endl;
		for (int i = 0; i < this->_sa.size(); i++)
			cout << setw(3) << i << " : " << setw(3) << this->_sa[i] << " : " << this->_txt.substr(this->_sa[i], this->_sa.size() - this->_sa[i]) << endl;
		cout << endl << endl;
	}

	void Search(string pattern)
	{
		for (int i = 0; i < this->_txt.size(); i++)
			cout << i % 10;
		cout << endl << this->_txt << endl;

		int l = 0, r = int(this->_sa.size() - 1);
		while (l <= r)
		{
			// TO KNOW: 왜 mid 계산을 l + (r - l) / 2로 하는가?
			int mid = l + (r - l) / 2;

			// cout << "l : " << l << ",\tr : " << r << endl;
			// cout << "&this->_txt.c_str()[this->_sa[mid]] : " << &this->_txt.c_str()[this->_sa[mid]] << endl;
			// cout << "pattern.c_str() : " << pattern.c_str() << endl;
			int compare = strcmp(&this->_txt.c_str()[this->_sa[mid]], pattern.c_str()); // 힌트로 사용하세요
			// cout << "compare : " << compare << endl;

			if (compare == 0)
			{
				// 매칭되는 순서대로 출력하기 위해 set에 저장해서 정렬했다가 출력
				set<int> matched;
				matched.insert(this->_sa[mid]);

				// TODO: 
				// for (int i = mid - 1; i >= 0 && strcmp(&_txt.c_str()[this->_sa[i]], pattern.c_str(), pattern.size()) == 0; i--)
				// Honglab way
				for (int i = mid - 1; i >= 0 && strncmp(&_txt.c_str()[_sa[i]], pattern.c_str(), pattern.size()) == 0; i--)
                    matched.insert(_sa[i]);
                for (int i = mid + 1; i < _txt.size() && strncmp(&_txt.c_str()[_sa[i]], pattern.c_str(), pattern.size()) == 0; i++)
                    matched.insert(_sa[i]);

				for (int index : matched)
					cout << string(index, ' ') << pattern << " " << index << endl;
				cout << endl;

				return;
			}
			else if (compare > 0)
			{
				r = mid - 1;
			}
			else if (compare < 0)
			{
				l = mid + 1;
			}
			// cout << "l : " << l << ",\tr : " << r << endl;
			// TODO: mid 변경
		}
		return; // TODO: 제거

		cout << "Not found" << endl;
	}
};

int main()
{
	//  C/C++ 문자열 복습 (string::c_str(), strcmp(), strncmp() 3가지)
	//{
	//	string str1("abc");
	//	string str2("abx");

	//	// 1. string::c_str()
	//	const char* c_str1 = str1.c_str(); // c언어 스타일의 문자열 (마지막에 널캐릭터 포함)
	//	const char* c_str2 = str2.c_str(); // c언어 스타일의 문자열 (마지막에 널캐릭터 포함)

	//	cout << c_str1 << endl; // "abc"
	//	cout << c_str2 << endl; // "abx"

	//	// 2. strcmp(c_str1, c_str2): 두 문자열의 길이와 글자가 같을 경우 0, str1이 앞설 경우 -1, str2가 앞설 경우 1 반환
	//	cout << strcmp(str1.c_str(), str2.c_str()) << endl; // -1
	//	cout << strcmp("ab", "abc") << endl; // -1
	//	cout << strcmp("abc", "ab") << endl; // 1
	//	cout << strcmp("ab", "ab") << endl;  // 0
	// 
	// // 3. strncmp(c_str1, c_str2, n): strcmp를 글자 n개만 수행
	// // cout << strncmp("abc", "ab", 2) << endl; // 0, strcmp()에서는 1
	//}

	{
		SuffixArray s("abcdefg");
	}

	{
		SuffixArray s("gfedcba");
	}

	{
		SuffixArray s("banana");
		s.Search("na");
	}

	{
		SuffixArray s("aaaaaaaaaa");
		s.Search("aaa");
	}

	{
		SuffixArray s("abababcabababca");
		s.Search("abababca");
	}

	{
		SuffixArray s("AABAACAADAABAABA");
		s.Search("AABA");
	}

	{
		SuffixArray s("ababababcababababab");
		s.Search("abab");
	}

	return 0;
}