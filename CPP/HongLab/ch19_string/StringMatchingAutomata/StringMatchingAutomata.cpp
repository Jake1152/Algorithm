#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 아래 구현은 CLRS 4th p.974을 유사하게 이해하기 쉽도록 정리한 것입니다.
// C 스타일의 보다 효율적인 구현은 아래 링크 참고하세요. (영상 밑에 해설 참고하세요)
// https://www.geeksforgeeks.org/finite-automata-algorithm-for-pattern-searching/
/**
 * 패턴을 기준으로 현재 상태에서 입력 값에 따라 다음 상태를 알려준다.
 * 패턴 길이를 기준으로 한다.
 */
void ComputeTransitionFunction(string pat, vector<vector<int>>& TF) // TF reference
{
	int M = int(pat.size());
	int d = int(TF[0].size()); // number of characters (128 in ASCII)

	// 힌트
	// - pat[0]에서 pat[s-1]까지 순서대로 들어왔다면 상태 숫자는 s입니다.
	// - 바꿔말하면 상태가 s번이라는 의미는 글자가 s개 매칭된 상태라는 의미입니다.
	// - 상태의 가짓수는 패턴의 글자수보다 하나 더 많습니다. (하나도 매칭 안된 0번 상태 포함)
	// - TF[state][x]는 상태s(= s개가 이미 매칭된 상태)에 추가로 x가 더 들어오는 경우를 의미합니다.

	for (int state = 0; state <= M; ++state)     // 상태 state에서
	{
		for (int x = 32; x < d; ++x)             // 글자 x가 들어오면 (ASCII 32 미만은 패턴에 사용되지 않는다고 가정)
		{
			int k = std::min(M, state + 1); // 상태는 M보다 클 수 없다

			// TO KNOW: k를 갱신하는 이유?, 3중 for문이라서 k값이 패턴 길이보다 길어지는 경우가 있어서?
			// 어느 경우의 k값이 패턴 길이보다 길어지는가?

			while (k > 0) // k == 0 이라면 한 글자도 매칭이 안되었다는 의미
			{
				// pat[state]
				// 문자열 연산 힌트 substr(), += char(x)
				// string prefix = TODO;     // 패턴의 앞에서부터 k 글자
				// string suffix = TODO;     // [현재 상태로 오기위해 입력받은 문자열 + 새로운 글자]의 뒷부분 k 글자
				string prefix = pat.substr(0, k);
				string suffix = pat.substr(0, state);
				suffix += char(x); // 새로 들어올 글자 추가
				suffix = suffix.substr(suffix.size() - k, k); // 입력 문자열의 뒤에서부터 k글자

				// suffix를 3줄로 나눠서 구현하는 경우
				// string suffix = pat.substr(0, state);
				// suffix = char(x); // 현재 상태로 오기위해 입력받은 문자열
				// suffix += suffix.substr(suffix.size() - k, k);       // 새로 들어올 글자 추가

				// string suffix = pat.substr(state - (k - 1), k - 1) + char(x); // 한줄로 줄인 구현

				if (prefix == suffix)
					break;

				k = k - 1; // 길이 k인 경우에 매칭 실패,더 짦은 경우에 대해 시도
				cout << "k : " << k << ",\tprefix : " << prefix << ",\tsuffix : " << suffix << endl;
			}

			TF[state][x] = k;
		}
	}
}

void PrintTransitionFunction(vector<vector<int>>& tf)
{
	cout << "   ";
	for (char i = 'a'; i <= 'd'; i++) // 편의상 abcd에 대해서만 출력
		cout << i;
	cout << endl;

	for (int s = 0; s < tf.size(); s++)
	{
		cout << s << "  ";
		for (char i = 'a'; i <= 'd'; i++) // 편의상 abcd에 대해서만 출력
			cout << tf[s][i];
		cout << endl;
	}
	cout << endl;
}

// Automaton은 automata의 단수형입니다.
// 앞에 붙은 finite은 상태가 유한하다는 의미입니다.
void FiniteAutomatonMatcher(string pat, string txt)
{
	int M = int(pat.size());
	int N = int(txt.size());
	int d = 128; // number of ASCII characters

	vector<vector<int>> tf(M + 1, vector<int>(d, 0)); // 모두 0으로 초기화 (엉뚱한 글자가 들어오면 첫 상태로 이동)

	// tf[state][character] -> next state

	// 본격적인 매칭을 시작하기에 앞서서 전이함수 tf를 미리 만듭니다.
	ComputeTransitionFunction(pat, tf); // txt 없이 패턴pat로만 만들 수 있습니다.

	PrintTransitionFunction(tf); // tf를 표로 출력, 디버깅에 활용하세요.

	for (int i = 0; i < N; i++)
		cout << i % 10;
	cout << endl << txt << endl;

	string record; // state 기록, 디버깅용

	// 준비된 tf를 이용해서 Theta(N)으로 매칭 진행
	int state = 0;
	for (int i = 0; i < N; i++)
	{
		state = tf[state][txt[i]];

		record.append(to_string(state));

		if (state == M)
		{
			cout << record << endl;
			cout << string(i - M + 1, ' ') << pat << " " << i - M + 1 << endl;
		}
	}
}

int main()
{
	// string txt = "aabaacaadaabaaabaa";
	// string pat = "aaba";
	string txt = "abababcabababab";
	string pat = "abab";

	FiniteAutomatonMatcher(pat, txt); // 중복 매치 가능

	return 0;
}