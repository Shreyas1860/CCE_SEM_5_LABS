
list1_str = input("Enter elements of the first list with space\n")
list2_str = input("Enter elements of the second list with space\n")

list1 = list(map(int, list1_str.split(' ')))
list2 = list(map(int, list2_str.split(' ')))

union_result = list(set(list1) | set(list2))
intersection_result = list(set(list1) & set(list2))
difference_result = list(set(list1) - set(list2))

print("Union:", union_result)
print("Intersection:", intersection_result)
print("Difference (List1 - List2):", difference_result)


