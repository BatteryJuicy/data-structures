def bubble_sort(lst):
    for i in range(1, len(lst) + 1):
        k = 0
        for j in range(len(lst) - i):
            if lst[j] > lst[j+1]:
                lst[j], lst[j+1] = lst[j+1], lst[j]
                k += 1
        if k == 0:
            return lst
