'''
조합

n개 중에 k개를 순서 상관없이 뽑는 방식

{1, 2}
0Cn, 1Cn, ..., nCn

{1}, {2}
{1, 2}


{3, 2, 5}

{3}, {2}, {5}
{3, 2}, {3, 5}, {2, 5}

{3, 2, 5}


# input
집합,
앞으로 뽑아야할 것들의 개수,
뽑은 원소의 위치,
조합 집합이 들어갈 배열


# output
조합된 집합
'''

def recur_combination(group, k, pos, combination_group):
    if (k < 0 or \
        pos + 1 > len(group) or \
        pos + k > len(group)):
            return
    combination_group.append(group[pos])
    for interval in range(1, pos, len(group)):
        recur_combination(group, k - 1, pos + interval, combination_group)

def combination(group, k):
    combination_groups = []
    for pos in range(0, len(group)):
        combination_group = []
        recur_combination(group, k, pos, combination_group)
        combination_groups.append(combination_group)
    return combination_groups


if __name__ == "__main__":
    group = [3, 2, 1]
    print(f"{group}")
    combination_group = combination(group, 2)
    #for k in range(len(group) + 1):
    #    combination_group = combination(group, k)
    print(f"{combination_group=}")


