def permute(word):
    results = []

    def permutations(msg, j=0):
        lst = list(msg)
        if j == len(lst):
            results.append("".join(lst))
        else:
            for i in range(j, len(msg)):
                lst[i], lst[j] = lst[j], lst[i]
                permutations("".join(lst), j + 1)
                lst[i], lst[j] = lst[j], lst[i]
    permutations(word)
    return results
