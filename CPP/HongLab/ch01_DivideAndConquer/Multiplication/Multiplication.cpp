#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

string Multiply(string str1, string str2)
{
	std::string result;

	// TODO:
	if (str1.length() == 0 || str2.length() == 0)
		return string("0");

	size_t str_max_size = std::max(str1.length(), str2.length());
	// std::cout << "str_max_size : " << str_max_size << std::endl;

	str1.insert(0, string(str_max_size - str1.size(), '0'));
    str2.insert(0, string(str_max_size - str2.size(), '0'));
	result.insert(0, string(2 * str_max_size, '0'));

	// std::cout << "str1 : " << str1 << std::endl;
	// std::cout << "str2 : " << str2 << std::endl;
	// std::cout << "result : " << result << std::endl;

	size_t carry = 0;
	size_t digitMultiplicationResult;

	/**
	 * 12
	 * 34
	 * 
	 * => 12 * 4 = 48
	 * => 12 * 30 = 360
	*/
	for (int idx = str_max_size - 1; idx >= 0; idx--)
	{
		// str1[idx]
		// str2[idx]
		for (int idx_j = str_max_size - 1; idx_j >= 0; idx_j--)
		{
			int n1 = str1.at(idx_j) - '0';
			int n2 = str2.at(idx) - '0';

			// digitMultiplicationResult =  * (str2.at(idx) - '0' * std::pow(10, (str_max_size - 1) - idx)) + carry;
			digitMultiplicationResult = n1 * n2 + carry;
			carry = digitMultiplicationResult / 10;
			
			// std::cout << "digitMultiplicationResult : " << digitMultiplicationResult << std::endl;
			size_t cur_digit_value = ((digitMultiplicationResult % 10) + (result.at(idx_j + idx + 1) - '0'));
			result.at(idx_j + idx + 1) = cur_digit_value % 10 + '0';
			carry += cur_digit_value / 10;
		}
		// std::cout << "# carry : " << carry << "\tresult : " << result << std::endl;
		if (carry)
		{
			result.at(idx) = carry + '0';
			// carry = carry / 10; // = 0으로 해도 무방할 듯
			carry = 0;
		}
		// digitMultiplicationResult
	}

	while (result.at(0) == '0')
		result.erase(0, 1);

	// std::cout << "result : " << result << std::endl;
	return result;
}

int main()
{
	vector<vector<string>> tests = {
		{"12", "34", std::to_string(12 * 34)},
		{"123", "45", std::to_string(123 * 45)},
		{"5000", "50", std::to_string(5000 * 50)},
		{"5000", "55", std::to_string(5000 * 55)},
		{"5555", "55", std::to_string(5555 * 55)},
		{"5555", "5555", std::to_string(5555 * 5555)},
		{"98234712354214154", "171454654654655", "16842798681791158832220782986870"}
		// , {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "16842798681791114273590624445460185389471221520083884298838480662480"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];
		const string str2 = t[1];
		const string expected = t[2];

		cout << str1 << " * " << str2 << " = " << expected << endl;

		const string result = Multiply(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK";
		else {
			cout << "Not OK";
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}