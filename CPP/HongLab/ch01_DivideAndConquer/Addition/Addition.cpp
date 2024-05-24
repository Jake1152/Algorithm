#include <string>
#include <vector>
#include <iostream>

using namespace std;

/** 입력도 문자열, 출력도 문자열
 * 작은 자릿수부터 더 한다.
 * 
 * 생각나는대로 여러가지 시도
*/
string Add(string str1, string str2)
{
	// TODO:
	std::string addtionResultStr;

	// addtionResultStr += str1;
	// std::cout << "str1 : " << str1 << std::endl;
	// std::cout << "str2 : " << str2 << std::endl;
	
	int carry = 0;
	int idx_str1= str1.size() - 1;
	int idx_str2= str2.size() - 1;

	while (idx_str1 >= 0 && idx_str2 >= 0)
	{
		int digitAddtionResult;
		int curDigitResult;

		// std::cout << "str1.at(idx_str1) : " << str1.at(idx_str1) << ",\tidx_str1 : " << idx_str1 << std::endl;
		// std::cout << "str2[idx_str2] : " << str2[idx_str2] << ",\tidx_str2 : " << idx_str2 << std::endl;
		digitAddtionResult = static_cast<int>(str1.at(idx_str1)) - '0' + static_cast<int>(str2[idx_str2]) - '0' + carry;
		// std::cout << "digitAddtionResult : " << digitAddtionResult << std::endl;
		carry = digitAddtionResult / 10;
		curDigitResult = digitAddtionResult % 10;
		addtionResultStr = to_string(curDigitResult) + addtionResultStr; // to_string이외에 바꿀 방법은 없는가?
		// std::cout << "addtionResultStr : " << addtionResultStr << std::endl;
		idx_str1--;
		idx_str2--;
	}

	while (idx_str1 >= 0)
	{
		int digitAddtionResult = static_cast<int>(str1.at(idx_str1)) - '0' + carry;
		// std::cout << "digitAddtionResult : " << digitAddtionResult << std::endl;
		carry = digitAddtionResult / 10;
		int curDigitResult = digitAddtionResult % 10;
		addtionResultStr = to_string(curDigitResult) + addtionResultStr; // to_string이외에 바꿀 방법은 없는가?
		idx_str1--;
	}

	while (idx_str2 >= 0)
	{
		int digitAddtionResult = static_cast<int>(str2[idx_str2]) - '0' + carry;
		// std::cout << "digitAddtionResult : " << digitAddtionResult << std::endl;
		carry = digitAddtionResult / 10;
		int curDigitResult = digitAddtionResult % 10;
		addtionResultStr = to_string(curDigitResult) + addtionResultStr; // to_string이외에 바꿀 방법은 없는가?
		idx_str2--;
	}
	
	if (carry) 
		addtionResultStr = to_string(carry) + addtionResultStr;

	// std::cout << "addtionResultStr : " << addtionResultStr << std::endl;
	return addtionResultStr;
}

int main()
{
	vector<vector<string>> tests = {
		{"12", "34", to_string(12 + 34)}
		, {"123", "45", to_string(123 + 45)}
		, {"54544", "44545", to_string(54544 + 44545)}
		, {"5555", "55", to_string(5555 + 55)}
		, {"5555", "5555", to_string(5555 + 5555)}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "11538017781967960909090003089999089"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];     // "12"
		const string str2 = t[1];     // "34"
		const string expected = t[2]; // "46"

		cout << str1 << " + " << str2 << " = " << expected << endl;

		const string result = Add(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK" << endl;
		else {
			cout << "Not OK" << endl;
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}