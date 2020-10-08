def read_file(filename: str, ignore_char: str = "#") -> list:
    """
    Read the file "filename" and stores it into a list of string where each element
    is a line of the file. For each lines, the characters after the "ignore_char" character (if present)
    are discarded. If the line is empty, i.e. a real empty line or a line that containted "ignore_char" as
    first character, then the line is discarded

    :param filename: str
        Path to the file to read.
    :param ignore_char: str
        Character delimiting comments and lines/part of lines to be discarded
    :return: list
        List of non-empty lines
    """

    file_str_list = []

    f = open(filename, "r")
    for i in f:
        file_str_list.append(i.strip("\n"))
    f.close()

    file_str_list_new = []

    for i in range(0, len(file_str_list)):
        index = file_str_list[i].find(ignore_char)
        if index != -1:
            file_str_list[i] = file_str_list[i][:index]
            file_str_list[i] = file_str_list[i].replace("\t", " ").strip(" ")

        if len(file_str_list[i]) > 0:
            file_str_list_new.append(file_str_list[i])

    return file_str_list_new


def split_str_list(str_list: list, n_elem_max: int, split_char: str = " ") -> list:
    """
    Split each element of a list of string "str_list" according to the "split_char". The number of elements of
    each line will be >= n_elem_max. If the split lead to more elements, then the last elements are concatanated
    using spaces as separator.

    :param str_list: list
        List of string to be split
    :param n_elem_max: int
        Maximum number of elements in each line of the list
    :param split_char: str
        Splitting character
    :return: list
        List of list of string of split sentences
    """

    for i in range(0, len(str_list)):
        str_list[i] = list(filter(None, str_list[i].split(split_char)))
        tmp = []
        for j in range(len(str_list[i])):
            if j == n_elem_max - 1:
                s = ""
                for k in range(j, len(str_list[i])):
                    s += str_list[i][k] + " "
                s = s.strip(" ")
                tmp.append(s)
                break
            else:
                tmp.append(str_list[i][j])
        str_list[i] = tmp

    return str_list


def is_subset(l1: list, l2: list) -> bool:
    """
    Test if l2 is a subset of l1, i.e. all elements of l2 are contained in l1 and return True if it the case, False
    otherwise.

    :param l1: main list
    :param l2: list whose elements are to be checked (if they're in l1 or not)
    :return: True if l2 is a subset of l1, False otherwise.
    """
    set1 = set(l1)
    set2 = set(l2)
    return set1.issubset(set2)


def listdic_to_diclist(listdic: list):
    """
    Convert a list of discionaries into a dictionary of list

    :param listdic:
    :return:
    """

    diclist = {}
    for elem in listdic:
        for key in elem:
            if not(key in diclist):
                diclist[key] = []
            diclist[key].append(elem[key])

    return diclist