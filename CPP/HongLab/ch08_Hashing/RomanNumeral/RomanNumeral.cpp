#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

// LeetCode: Roman to Integer
// https://leetcode.com/problems/roman-to-integer/description/

/**
 * stack으로 만든다.
 * top에 있는 값과 string에서 뽑은 값을 비교한다.
 * top에 있는 값보다 string에 있는 값이 더 크다면
 * stack을 빌때까지 pop한다.
 * stack에서 pop한 값은 temp_sum에 값을 더한다.
 * string에서 뽑았던 값에서 temp_sum을 뺀다.
 * 빼고 남은 값을 ans에 더한다.
 * 
 * 이 과정을 반복한다
 * 이후 stack이 빌때까지 하나씩 pop하며 ans에 더 한다.
 */
int RomanToInt(string s)
{
	unordered_map<char, int> m;

	m['I'] = 1;
	m['V'] = 5;
	m['X'] = 10;
	m['L'] = 50;
	m['C'] = 100;
	m['D'] = 500;
	m['M'] = 1000;

	int ans = 0;

	// TODO:
	std::stack<int> st;
	int temp_sum = 0;
	for (int i = 0; i < s.length(); i++)
	{
		const char prev_char = s[i-1];
		const char cur_char = s[i];

		if (st.size() && m[cur_char] > m[st.top()])
		{
			while (st.size())
			{
				temp_sum += m[st.top()];
				st.pop();
			}
			cout << "# str : " << s[i] << " ,temp_sum : " << temp_sum << endl;
			cout << "# m[cur_char] : " << m[cur_char] << endl;
			ans += m[cur_char] - temp_sum;
			temp_sum = 0;
		}
		else
			st.push(s[i]);
	}

	// cout << s << " = " << ans << endl;
	while (st.size())
	{
		const char cur_char = st.top();

		st.pop();
		ans += m[cur_char];
	}

	cout << s << " = " << ans << endl;

	return ans;
}

int main()
{
	RomanToInt("II");

	RomanToInt("III");

	RomanToInt("XII");

	RomanToInt("XXVII");

	RomanToInt("IV");

	RomanToInt("IX");

	RomanToInt("XL");

	RomanToInt("XC");

	RomanToInt("CD");

	RomanToInt("CM");

	RomanToInt("LVIII");

	RomanToInt("MCMXCIV");

	return 0;
}