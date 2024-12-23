#include <vector>
#include <iostream>
#include <string>
using namespace std;


/**
 * LPS(Longest proper Prefix and Suffix)
 * abcd
 */
vector<int> ComputePrefixFunction(string pat)
{
	int M = int(pat.size());

	vector<int> lps(pat.size()); // lps: longest proper prefix and suffix (가장 긴 진접두사 이자 진접미사)

	lps[0] = 0; // 길이가 0인 문자열의 LPS는 0
	int k = 0;  // LPS는 0에서 시작

	for (int i = 1; i < M; i++) // i는 1부터 시작하고 항상 증가
	{
		// break; // TODO: 삭제

		// while (TODO: k가 0보다 크고 i와 k 자리의 글자들이 서로 다를 경우) // 매칭에 실패했을 경우 k를 되돌리기
		// 매칭에 실패했을 경우 k를 되돌리기
		while (k > 0 && pat[k] != pat[i])
		{
			k = lps[k - 1];
			// k = k - 1; // 주의: 이렇게 하면 안되는 이유는?
		}

		if (pat[k] == pat[i])
		{
			k = k + 1;
		}

		lps[i] = k; // 다음 상태 기록?!
	}

	cout << pat << endl;
	for (auto i : lps) cout << i % 10;
	cout << endl;

	return lps;
}

void KMPMatcher(string pat, string txt)
{
	int N = int(txt.size());
	int M = int(pat.size());

	vector<int> lps = ComputePrefixFunction(pat); // longest proper prefix suffix

	for (int i = 0; i < txt.size(); i++)
		cout << i % 10;
	cout << endl << txt << endl;

	int k = 0;
	for (int i = 0; i < N; i++) // i가 0부터 시작합니다.
	{
		// break; // TODO: 삭제

        while (k > 0 && pat[k] != txt[i])
        {
            k = lps[k - 1];
        }

        if (pat[k] == txt[i])
        {
            k += 1;
        }

        if (k == M)
        {
            for (int s = 0; s < i - (M - 1); s++)
                cout << " ";
            cout << pat << " " << i - (M - 1) << endl;

            k = lps[k - 1]; // 모든 글자가 매칭된 경우에도 다음 매칭을 위해 k를 되돌림
        }

	}

	cout << endl;
}

int main()
{
	string txt1 = "abababcabababca";
	string pat1 = "abababca";
	KMPMatcher(pat1, txt1);

	string txt2 = "AABAACAADAABAABA";
	string pat2 = "AABA";
	KMPMatcher(pat2, txt2);

	string txt3 = "ababababcababababab";
	string pat3 = "abab";
	KMPMatcher(pat3, txt3);

	return 0;
}