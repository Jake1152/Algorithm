#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정

// Bonus: 한쪽이 더 클수도 있다고 가정, swap해서 진행하면 될거 같다.(sign flag 사용 필요)
string Subtract(string str1, string str2)
{
	// 둘이 같을 경우 바로 "0" 반환
	std::cout << "str1 : " << str1 << ",\tstr2 : " << str2 << std::endl;

	if (str1 == str2)
		return "0"; // '0'은 char, "0"은 string

	int N = max(str1.size(), str2.size());
	str1 = string(N - str1.size(), '0') + str1; // 문자열끼리의 더하기도 가능
	str2 = string(N - str2.size(), '0') + str2;

	string result(N, '0');

	// 500 - 420
	// TODO: 더하기와 거의 비슷합니다.
    int carry = 0; // 더한 결과가 10보다 클 경우 다음 자리로 넘겨줄 숫자
    for (int i = N - 1; i >= 0; i--) // 역순 주의
    {
        int n1 = str1[i] - '0'; // 문자를 정수로 변환
        int n2 = str2[i] - '0';

        int substraction = n1 - n2 + carry;
		if (substraction < 0)
		{
			substraction += 10;
			carry = -1;
		}
		else
		{
        	carry = 0; // 다음 자리로 넘길 숫자 업데이트 
		}

        result[i] = char(substraction % 10 + '0'); // 결과 저장        
        // 디버깅용 출력
        cout << n1 << " " << n2 << " " << carry << " " << result << endl; 
    }

	// 불필요한 '0' 제거 (예: "078" -> "78")
	// TODO:
	/* cpp string erase() usage
	sequence (1)	
	string& erase (size_t pos = 0, size_t len = npos);
	
	character (2)	
	iterator erase (iterator p);

	range (3)	
    iterator erase (iterator first, iterator last);
	*/
	while (result.at(0) == '0')
	{
		// result.erase(0, 1);
		// result.erase(result.begin());
		result.erase(result.begin(), result.begin() + 1);
	}

	std::cout << "# result  : " << result << endl;
	return result;
}

int main()
{
	// 항상 큰 수에서 작은 수를 빼는 경우(결과가 음수가 되지 않는 경우)를 가정
	vector<vector<string>> tests = {
		{"34", "12", std::to_string(34 - 12)}
		, {"123", "45", std::to_string(123 - 45)}
		, {"54544", "44545", std::to_string(54544 - 44545)}
		, {"5555", "55", std::to_string(5555 - 55)}
		, {"5555", "5555", std::to_string(5555 - 5555)}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "8108924688874870000000906000909999"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];
		const string str2 = t[1];
		const string expected = t[2];

		cout << str1 << " - " << str2 << " = " << expected << endl;

		const string result = Subtract(str1, str2);

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