from utils import *

''' 
    Allowed types 
'''
legit_var_types = ["double", "int", "string", "bool"]

''' 
    Fields in the input file for !new_var
        Those are list of tuples. 
            The first field of the tuple if the name of the field.
            The second field of the tuple is the must_exist flag
'''
var_fields = [("namespace", True),
              ("name", True),
              ("type", True),
              ("default", True),
              ("external unit", False),
              ("internal unit", False),
              ("comment", False),
              ]

''' 
    Fields in the input file for !new_unit
        Those are list of tuples. 
            The first field of the tuple if the name of the field.
            The second field of the tuple is the must_exist flag
'''
unit_fields = [("external unit", True),
               ("internal unit", True),
               ("conversion", True),
               ]


class PParserPy:
    """
    Class that handles the reading and parsing of the pppy.in file.
    """
    def __init__(self, input_file, verbose = True):

        self.__verbose = verbose

        # Building the lists self.__var_allowed_list, self.__var_must_exist, self.__unit_allowed_list
        # and  self.__unit_must_exist
        self.__initialize_control_lists()

        # Reading and parsing the file
        str_input_file = read_file(input_file, ignore_char="#")

        # Building the list of dictionaries
        self.var_list_dic = self.populate_list_dic(str_input_file, "!new_var",
                                                   self.__var_allowed_list, self.__var_must_exist)

        self.unit_list_dic = self.populate_list_dic(str_input_file, "!new_unit",
                                                    self.__unit_allowed_list, self.__unit_must_exist)

        if self.__verbose:
            print("Printing self.var_list_dic")
            for i in self.var_list_dic:
                print("Variable:")
                for j in self.__var_allowed_list:
                    print("\t",j,"%s" %((15 - len(j)) * " "), i[j])
            print("")

            print("Printing self.unit_list_dic")
            for i in self.unit_list_dic:
                print("Unit:")
                for j in self.__unit_allowed_list:
                    print("\t",j,"%s" %((15 - len(j)) * " "), i[j])
            print("")

        # Converting the list of dictionaries into dictionaries of lists
        self.var_dic_list = listdic_to_diclist(self.var_list_dic)
        self.unit_dic_list = listdic_to_diclist(self.unit_list_dic)
        if self.__verbose:
            print("")
            print("Printing the dictionary of lists for variables")
            for i in self.var_dic_list:
                print(i, self.var_dic_list[i])

            print("")
            print("Printing the dictionary of lists for units")
            for i in self.unit_dic_list:
                print(i, self.unit_dic_list[i])
            print("")

    def __initialize_control_lists(self):
        """
        Initialize the control lists
            self.__var_allowed_list is the list of allowed variable field names, e.g. Namespace, Name, Default, ...
            self.__var_must_exist is the list of boolean value controlling if a variable field name must exist.
            Important field name, such as Namespace or Name MUST exists. Other, like Default, can be omitted.
            In such cases, default is set to None

            self.__unit_allowed_list and self.__unit_must_exist are the same except that they refer to unit
            handling.

        :return: None but populate internal class members self.__var_allowed_list, self.__var_can_be_inexistant,
        self.__unit_allowed_list and self.__unit_can_be_inexistent.
        """

        self.__var_allowed_list = [f[0] for f in var_fields]    # List of allowed variable field names
        self.__var_must_exist   = [f[1] for f in var_fields]    # List of flag to check if a variable field name can be inexistant

        self.__unit_allowed_list = [f[0] for f in unit_fields]    # List of allowed unit field names
        self.__unit_must_exist   = [f[1] for f in unit_fields]    # List of flag to check if a unit field name can be inexistant

    def populate_list_dic(self, str_file: list, target_word: str, allowed_fields: list, must_exist: list):
        '''
        Populate a list of dictionary using the input written in the str_file str list. The file might look like this:
        !target_word
            Namespace = TimeAxis
            ...


        Each new element of the list is initialized once we encounter the flag "!target_word" in the file. Following
        this flag, the field name is on the left of each equal sign and the value on the right. The equal sign is used
        as a delimiter and therefore should NEVER be used in the naming of the field and/or value

        :param str_file:        list    List of string where each element is a relevant line of the file.
        :param target_word:     str     Target word that initialize the building of a new element of the list
        :param allowed_fields:  list    List of string of allowed field name. Throw an error if the field name is not
                                        in this list
        :param must_exist:      list    List of boolean flags to check if a particular field must be user defined or not
        :return:                list    Return a list of dictionaries built as aforementioned
        '''

        i = 0
        target_found = False
        output_list = []
        local_dic = {}
        while i < len(str_file):
            if str_file[i][0] == "!" and target_word in str_file[i]:
                target_found = True
                i += 1
                if len(local_dic) != 0:
                    output_list.append(local_dic)
                    local_dic = {}
                continue

            if str_file[i][0] == "!" and (not (target_word in str_file[i])):
                target_found = False
                i += 1
                continue

            if not target_found:
                i +=1
                continue

            words = str_file[i].split("=")
            for j in range(0, len(words)):
                words[j] = words[j].strip(" ").strip("\t")
            words[0] = words[0].lower()

            assert(len(words) == 2)
            assert(words[0] in allowed_fields)

            local_dic[words[0]] = words[1]

            i += 1

        if len(local_dic) != 0:
            output_list.append(local_dic)
            local_dic = {}

        output_list = self.fill_list_dic(output_list, allowed_fields, must_exist)
        return output_list


    def fill_list_dic(self, list_dic: list, allowed_fields: list, must_exist: list):
        """
        Ensure that each element of the list_dic contains ALL the fields in allowed fields. If a field is not contained,
        then the None value is added.

        :param list_dic: list           List of dictionary. Each element represent a variable or unit
        :param allowed_fields: list     List of allowed field
        :param must_exist: list         List of must_exist flags for the allowed_field
        :return:
        """

        for i in range(0, len(list_dic)):
            for j in range(0, len(allowed_fields)):
                if not(allowed_fields[j] in list_dic[i]):
                    if must_exist[j]:
                        print(list_dic[i])
                        print("Error... field %s MUST exist" % allowed_fields[j])
                        assert(False)
                    list_dic[i][allowed_fields[j]] = None

        return list_dic