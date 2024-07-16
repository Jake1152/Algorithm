#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<string, int> map;
    //map<string, int> map;

    // 새로운 키-값 추가
    map.insert({ "Orange", 1 });
    map.insert({ "Apple", 10 });
    map.insert({ "Strawberry", 7 });

    // 새로운 키-값 추가(배열처럼 인덱싱 연산자 사용)
    map["Kiwi"] = 5;   // map.insert({"Kiwi", 5}); 와 동일

    // 값 변경
    map.find("Kiwi")->second += 1; // 이터레이터 사용
    map["Kiwi"] += 1; // 인덱싱(더 편리)

    cout << map.count("Apple") << endl; // 1 아니면 0 반환
    // 이진탐색트리와 해쉬테이블 둘 다 키(key)의 중복을 허용하지 않기 때문에 
    // count()는 0 아니면 1입니다. 2 이상 X

    // map은 내부적으로 정렬된 순서 유지 (unordered_map과 출력 순서가 다를 수 있음)
    for (auto i : map)
        cout << i.first << " " << i.second << endl;
    // 여기서 i는 tuple 자료형입니다. first가 key, second가 value 입니다.

    return 0;
}