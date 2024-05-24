import random
import sys

def generate_random(n) :
    lower_bound = 10 ** (n - 1)
    upper_bound = (10 ** n) - 1
    return random.randint(lower_bound, upper_bound)

START = 1
MAX_DIGITS = 1600000
STEP = 100000

if MAX_DIGITS > 100:
    sys.set_int_max_str_digits(2 * MAX_DIGITS + 1) # 곱하기는 숫자길이가 2배

with open("test_cases_add.txt", "w") as f :
    f.write(str((MAX_DIGITS - START)// STEP) + '\n') # 테스트 케이스의 개수
    for n in range(START, MAX_DIGITS + 1, STEP) :
        a = generate_random(n)
        b = generate_random(n)
        #c = a * b # 곱하게 데이터 생성할 때
        c = a + b
        f.write(str(a) + '\n')
        f.write(str(b) + '\n')
        f.write(str(c) + '\n') # 파이썬에서 계산한 정답도 저장
