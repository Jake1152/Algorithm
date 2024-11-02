#include <string>
#include <vector>
#include <iostream>
using namespace std;

void RabinKarpMatcher(string pattern, string txt, int digits, int hash_prime)
{
	const int pattern_size = int(pattern.size());
	const int txt_size = int(txt.size());

	// 자주 사용되는 숫자를 미리 계산
	// 여기서는 (128 % hash_prime) * 128 % hash_prime) * 128 % hash_prime
	int hash_value = 1;
	for (int i = 0; i < pattern_size - 1; i++)
		hash_value = (hash_value * digits) % hash_prime;

	int target_pattern_hash_value = 0; // 찾으려는 패턴의 해시값
	int txt_window_hash_value = 0; // 대상 문자열의 앞부분 해시값
	for (int i = 0; i < pattern_size; i++)
	{
		target_pattern_hash_value = (target_pattern_hash_value * digits + pattern[i]) % hash_prime;
		// cout << "target_pattern_hash_value : " << target_pattern_hash_value << endl;
		txt_window_hash_value = (txt_window_hash_value * digits + txt[i]) % hash_prime;
		// cout << "txt_window_hash_value : " << txt_window_hash_value << endl;
	}

	cout << "Pattern hash " << target_pattern_hash_value << endl;

	for (int i = 0; i <= txt_size - pattern_size; i++)
	{
		cout << string(i, ' ') + txt.substr(i, pattern_size) << " " << txt_window_hash_value << " at " << i << endl;

		if (target_pattern_hash_value == txt_window_hash_value) // 해시값이 일치하면 한 글자씩 비교해서 확인
		{
			int j;
			for (j = 0; j < pattern_size; j++)
				if (txt[i + j] != pattern[j])
					break;

			if (j == pattern_size)
				cout << "Pattern found at index " << i << endl;
			else
				cout << "Spurious hit " << i << endl;
		}

		if (i < txt_size - pattern_size)
		{
			// TODO:
			txt_window_hash_value = (txt_window_hash_value + hash_prime - hash_value * txt[i] % hash_prime) % hash_prime;
			// t = (t * d + txt[i + M]) % q;
			txt_window_hash_value = (txt_window_hash_value * digits + txt[i + pattern_size]) % hash_prime;
		}
	}
}

int main()
{
	string txt = "ABCDCDEDABABCDEBABCDEDA";
	string pattern = "ABCD";

	int digits = 128; // ASCII 코드의 가짓수

	// q는 d*q를 작게 만들 적당한 소수(prime number)
	int hash_prime = 997; // 이 숫자가 작으면 surous hit이 자주 발생, 해시 충돌과 비슷한 상황
	// hash_prime 

	// 문제 설명을 위한 출력
	{
		const int pattern_size = int(pattern.size());
		int txt_size = int(txt.size());
		cout << txt << endl;

		for (int i = 0; i <= txt_size - pattern_size; i++)
		{
			// 해시값을 하나씩 더해서 계산
			int hash_value = 0;
			for (int j = 0; j < pattern_size; j++)
				hash_value = (digits * hash_value + txt[i + j]) % hash_prime;

			cout << string(i, ' ') + txt.substr(i, pattern_size) << " " << hash_value << " at " << i << endl;
		}

		cout << endl;
	}

	RabinKarpMatcher(pattern, txt, digits, hash_prime);

	return 0;
}
