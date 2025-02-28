def linear_search(lst, element):
    for i in lst:
        if i == element:
            return lst.index(i)
    return None