def binary_search(lst, element):
    right = len(lst) - 1
    left = 0
    mid = (left + right)//2

    while left <= right:
        mid = (left + right)//2
        if lst[mid] == element:
            return mid
        elif lst[mid] < element:
            left = mid + 1
        else:
            right = mid - 1
    return None
