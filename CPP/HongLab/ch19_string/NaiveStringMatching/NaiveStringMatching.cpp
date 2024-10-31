#include <iostream>
#include <string>
using namespace std;

// CLRS 4th 32.1
void NaiveStringMatcher(string& pat, string& txt)
{
	int M = int(pat.size());
	int N = int(txt.size());

	cout << txt << " " << pat << endl;
	for (int i = 0; i < N; i++)
		cout << i % 10;
	cout << endl;

	for (int i = 0; i < N; i++)
	{
		if (txt.compare(i, M, pat) == 0)
		{
			for (int j = 0; j < i; j++)
				cout << " ";
			cout <<  pat << " " << i << endl;
		}
	}
	
	// # HongLab Way
	// i <= N - M 조건을 줌으로써 불필요한 부분들을 반복 돌지 않을 수 있음
	// for (int i = 0; i <= N - M; i++) // N 까지가 아니라 N - M 까지입니다.
    // {
    //     int j;
    //     for (j = 0; j < M; j++)
    //     {
    //         if (txt[i + j] != pat[j])
    //             break;
    //     }

    //     if (j == M)
    //     {
    //         for (int s = 0; s < i; s++)
    //             cout << " ";
    //         cout << pat << " " << i << endl;
    //     }
    // }

	cout << endl;
}

int main()
{
	string txt1 = "acaabc";
	string pat1 = "aab";
	NaiveStringMatcher(pat1, txt1);

	string txt2 = "AABAACAADAABAABA";
	string pat2 = "AABA";
	NaiveStringMatcher(pat2, txt2);

	string txt3 = "ababababcababababab";
	string pat3 = "abab";
	NaiveStringMatcher(pat3, txt3);

	return 0;
}