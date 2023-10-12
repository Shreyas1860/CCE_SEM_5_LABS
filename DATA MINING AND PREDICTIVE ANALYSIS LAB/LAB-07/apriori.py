f = open('apriori_DB.txt')
db = f.readlines()
for i, line in enumerate(db):
    db[i] = line.split()
    db[i].sort()

print("DB: ", db)

while True:
    try:
        min_support = int(input("Enter minimum support: "))
        break
    except ValueError:
        print("Please enter a valid integer for minimum support.")

L, C, k = [[]], [[]], 0

def freqGreaterThanOrEqualToMinSupport(db, newItemSet):
    cnt = 0
    for row in db:
        if set(newItemSet).issubset(set(row)):
            cnt = cnt + 1
    return cnt >= min_support

# Based on downward closure property - for any frequent itemset, its subset is also frequent
def prune(L, k, newItemSet):
    for i in range(len(newItemSet)):
        smallItemset = newItemSet[0:i] + newItemSet[i + 1:]
        if smallItemset not in L[k - 1]:
            return False
    return True

def candidate_gen(L, C, k):
    n = len(L[k - 1])
    for i in range(n - 1):
        for j in range(i + 1, n):
            if L[k - 1][i][0:k - 1] == L[k - 1][j][0:k - 1]:
                newItemSet = L[k - 1][i] + [L[k - 1][j][k - 1]]
                if prune(L, k, newItemSet):
                    C[k].append(newItemSet)
                    if freqGreaterThanOrEqualToMinSupport(db, newItemSet):
                        L[k].append(newItemSet)
            else:
                break

def init(L, C, k):
    count = {}
    for line in db:
        for element in line:
            if element in count:
                count[element] = count[element] + 1
            else:
                count[element] = 1
                C[k].append([element])

            if count[element] >= min_support and [element] not in L[k]:
                L[k].append([element])

    while len(L[k]) > 0:
        k = k + 1
        C.append([])  # to add itemsets to C[k]
        L.append([])  # to add itemsets to L[k]
        candidate_gen(L, C, k)  # C[k] is filled

init(L, C, k)

print('\n------- Frequent Itemsets --------')
for i, l in enumerate(L):
    if len(l) > 0:
        print(f'{i + 1} itemsets: {l}')
