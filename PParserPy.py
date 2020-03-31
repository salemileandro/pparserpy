from utils import *

''' Allowed types '''
legit_var_types = ["double", "int", "string", "bool"]

''' 
    Fields in the input file for !new_var
        Those are list of tuples. 
            The first field of the tuple if the name of the field.
            The second field of the tuple is the can_be_inexistant flag
'''
var_fields = [("namespace", False),
              ("name", False),
              ("type", False),
              ("default", False),
              ("external unit", True),
              ("internal unit", True),
              ("comment", True),
             ]

''' 
    Fields in the input file for !new_unit
        Those are list of tuples. 
            The first field of the tuple if the name of the field.
            The second field of the tuple is the can_be_inexistant flag
'''
unit_fields = [("external unit", False),
               ("internal unit", False),
               ("conversion", False),
              ]


class PParserPy:
    """
    Class that handles the reading and parsing of the pppy.in file.
    """
    def __init__(self, input_file):

        str_input_file = read_file(input_file, ignore_char="#")

        self.var_list_dic = self.populate_list_dic(str_input_file, "!new_var", var_fields)
        self.unit_list_dic = self.populate_list_dic(str_input_file, "!new_unit", unit_fields)

        for i in self.var_list_dic:
            print(i)

        for i in self.unit_list_dic:
            print(i)

        self.var_dic_list = listdic_to_diclist(self.var_list_dic)
        for i in self.var_dic_list:
            print(i, self.var_dic_list[i])


    def populate_list_dic(self, str_file: list, target_word: str, allowed_fields: list):
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

            control_list = []
            for field in allowed_fields:
                control_list.append(field[0])

            assert(len(words) == 2)
            assert(words[0] in control_list)

            local_dic[words[0]] = words[1]

            print(words)
            i += 1

        if len(local_dic) != 0:
            output_list.append(local_dic)
            local_dic = {}

        output_list = self.fill_list_dic(output_list, allowed_fields)
        return output_list

    def fill_list_dic(self, list_dic: list, allowed_fields: list):
        """
        Ensure that each element of the list_dic contains ALL the fields in allowed fields. If a field is not contained,
        then the None value is added.

        :param list_dic:
        :param allowed_fields:
        :return:
        """

        for i in range(0, len(list_dic)):
            for field in allowed_fields:
                if not(field in list_dic[i]):
                    list_dic[i][field] = None

        return list_dic











    #######################################
    ### SANITY CHECK FUNCTIONS (SAFETY) ###
    #######################################