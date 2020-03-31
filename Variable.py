fields = [("namespace", True),
          ("name", True),
          ("type", True),
          ("default", True),
          ("external unit", False),
          ("internal unit", False),
          ("comment", False),
          ]

field_list = [f[0] for f in fields]
field_must_exist = [f[1] for f in fields]

type_list = ["double", "int", "string", "bool"]


class Variable:
    """
    Class to describe a variable. A variable is defined in the user-written input file as a set of
    fields F1, F2, ... and corresponding values V1, V2, ... and written in the following fashion:

    input_template.txt:
        !new_var
            F1 = V1
            F2 = V2

        !new_var
            F1 = V1'
            F2 = V2'
        [...]

    Each object of the Variable class reflects one set of field/value under a !new_var statement. The field name
    must be contained by the control list named "field_list" otherwise an error is thrown. The field name for
    which the "field_must_exist" control list element is set the True MUST exist, i.e. it MUST be defined by the user,
    otherwise an error is thrown.

    """
    def __init__(self):
        self.__data = {}    # Main container of the class is a dictionary

    def parse(self, str_list: list):
        """
        Parse a str_list and runs several auto-completion and sanity checks. In brief,
            1. self__populate_data_dict(str_list):
                Populate the self.__data dict. Minimal checks are done here
            2. self__complete_data_dict():
                Complete the self.__data dict so that it contains all entries of the field_list. If a must-be-defined
                entry has not been defined, then it throws an error
            3. self __check_type():
                Check that the type of the variable is defined in type_list. Otherwise, it throws an error
            4. self.__nonify():
                Replace the strings "None" (case insensitive) to the Python type None.
            5. set_internal_names():
                From user defined names, it derives internal names such as:
                    cpp_name:   name of the variable in the cpp class
                    user_name:  name of the variable in the cpp-read user file
                    get_name:   name of the get function in the cpp class.

        This parse function is the high level API of the variable class for parsing. For more information,
        check in more detail the private functions that are briefly mentioned above.

        :param str_list: list   list of string where each element correspond to one entry of a variable
        :return: None
        """

        self.__populate_data_dict(str_list)
        self.__complete_data_dict()
        self.__check_type()
        self.__nonify()
        self.__set_internal_names()

    def __populate_data_dict(self, str_list):
        """
        Parse a list of string into the self.__data dictionary.
        A typical list of string might look like that:
            str_list[0] = "   Namespace = TimeAxis   "
            str_list[1] = "   Name      = Start      "
            [...]

        Only two things are ensured here:
            1. That each line contains only 1 "=" char, i.e. for splitting
            2. That the leftside of the "=" char is an allowed field (see field_list)

        :param str_list: list   List of string where each element correspond to one entry of a variable
        :return: None
        """
        for line in str_list:
            words = line.replace("\t", " ").strip("\n").strip(" ").split("=")
            words = [x.strip("\n").strip(" ") for x in words]
            words[0] = words[0].lower()
            assert(len(words) == 2)
            assert(words[0] in field_list)
            self.__data[words[0]] = words[1]

    def __complete_data_dict(self):
        """
        Complete the self.__data dict so that it contains all the field from the field_list. It also check
        that all the must-be-defined fields are defined, otherwise it throws an error
        :return:
        """
        for i in range(0, len(field_list)):
            if field_list[i] not in self.__data:
                if field_must_exist[i]:
                    print("Field %s as not been found ..." % field_list[i])
                    print("It must be declared !!!")
                    print("Error !")
                    assert(False)
                else:
                    self.__data[field_list[i]] = None

    def __check_type(self):
        """
        Check that the type is a valid one, i.e. is contained in the type_list
        :return:
        """
        if self.__data["type"] not in type_list:
            print("Type %s is not a valid type ..." % self.__data["type"])
            print("Current object : %s " % self.__str__())
            print("Valid types are :")
            for i in type_list:
                print("\t%s" % i)
            print("Exiting after error ...")
            assert(False)

    def __nonify(self):
        """
        Transform the "None" string into the python None (case insensitive)
        :return:
        """
        for i in self.__data:
            if isinstance(self.__data[i], str):
                if self.__data[i].lower() == "none":
                    self.__data[i] = None

    def __set_internal_names(self):
        """
        Set internal names:
            cpp_name:   name of the variable in the cpp class
            user_name:  name of the variable in the cpp-read user file
            get_name:   name of the get function in the cpp class.
        :return:
        """
        self.__data["cpp_name"] = self.__data["namespace"].lower() + "_" + self.__data["name"].lower() + "_"
        self.__data["user_name"] = self.__data["namespace"] + "." + self.__data["name"]
        self.__data["get_name"] = "Get_" + self.__data["namespace"] + "_" + self.__data["name"]

    def __getitem__(self, item):
        return self.__data[item]

    def __str__(self):
        a = "\n"
        for i in self.__data:
            a += "\tdata[\"%s\"] = %s\n" % (i, self.__data[i])
        return a


if __name__ == "__main__":
    print("Testing the Variable class.")
    x = Variable()

    test_list = ["\tNamespace = TimeAxis\n", "\tName = Start", "Type = double", "Default = 0.0"]

    x.parse(test_list)

    print(x)