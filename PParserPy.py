from utils import *
from Variable import Variable
from UnitConvertor import UnitConvertor


class PParserPy:
    """
    Class that handles the reading and parsing of the pppy.in file.
    """
    def __init__(self, input_file="pppy.in", name="ReadInput", verbose=True):

        # Fetch the basic members from the object initializer
        self.__input_file = input_file
        self.__name = name
        self.__verbose = verbose

        # Initialize and populate the variable list with variables defined in the input_file
        self.variable_list = []
        self.__parse_variables()
        if self.__verbose:
            print("Here are the user defined variables")
            for i in self.variable_list:
                print(i)

        # Initialize the UnitConvertor and teach it the conversions as defined in the input_file
        self.unitconvertor = UnitConvertor()
        self.__parse_units()
        if self.__verbose:
            print("Here are the user defined unit conversion + inverse conversions + unit conversions")
            print(self.unitconvertor)

        # Initialize the header file (list of string where each element is a line)
        self.__header_file = []
        self.__read_prototype()
        self.__rename_prototype()
        self.__look_for_variable_call()
        self.__unit_conversion_call()
        self.__definition_of_get_functions_call()
        self.__user_defined_variables_call()
        self.__generate_input_file_call()

        f = open("%s.h" %self.__name, "w+")
        for i in self.__header_file:
            f.write("%s\n" % i)
        f.close()

    def __parse_variables(self):
        """
        Parse the variables in the input file (filename stored in self.__input_file). Each variable is defined
        after the !new_var flag.
        After running this member function, the self.variable_list is populated as a list of Variabe objects.
        :return: None (populate the self.variable_list list)
        """
        str_input_file = read_file(self.__input_file, ignore_char="#")

        var_list = []
        local_list = []
        save_flag = False
        for line in str_input_file:
            if "!new_var" in line:
                if save_flag:
                    var_list.append(local_list)
                    local_list = []
                save_flag = True
                continue
            if "!new_unit" in line:
                save_flag = False
                continue
            if save_flag:
                local_list.append(line)
                continue

        if len(local_list) != 0:
            var_list.append(local_list)
            local_list = []

        for i in var_list:
            x = Variable()
            x.parse(i)
            self.variable_list.append(x)

    def __parse_units(self):
        str_input_file = read_file(self.__input_file, ignore_char="#")

        var_list = []
        local_list = []
        save_flag = False
        for line in str_input_file:
            if "!new_unit" in line:
                if save_flag:
                    var_list.append(local_list)
                    local_list = []
                save_flag = True
                continue
            if "!new_var" in line:
                save_flag = False
                continue
            if save_flag:
                local_list.append(line)
                continue
        if save_flag:
            var_list.append(local_list)

        for unit in var_list:
            dic = {}
            for line in unit:
                words = line.strip("\n").strip(" ").strip("\t").split("=")
                words = [f.strip("\n").strip(" ").strip("\t") for f in words]
                dic[words[0].lower()] = words[1]
            assert(is_subset(list(dic.keys()), ["external unit", "internal unit", "conversion"]))
            self.unitconvertor.add_unit(dic["external unit"], dic["internal unit"], dic["conversion"])

    def __read_prototype(self):
        f = open("Prototype.h", "r")
        for i in f:
            self.__header_file.append(i.strip("\n"))
        f.close()

    def __rename_prototype(self):
        for i in range(0, len(self.__header_file)):
            self.__header_file[i] = self.__header_file[i].replace("PROTOTYPE", "%s" % self.__name.upper())
            self.__header_file[i] = self.__header_file[i].replace("Prototype", "%s" % self.__name)
            self.__header_file[i] = self.__header_file[i].replace("prototype", "%s" % self.__name.lower())

    def __look_for_variable_call(self):
        new_file = []
        for i in range(0, len(self.__header_file)):
            if "//LOOK_FOR_VARIABLE_CALL" not in self.__header_file[i]:
                new_file.append(self.__header_file[i])
            else:
                for variable in self.variable_list:
                    new_file.append("\t\t\tthis->LookForVariable(%s, std::string(\"%s\"));" % (variable["cpp_name"], variable["user_name"]))
        self.__header_file = new_file[:]

    def __unit_conversion_call(self):
        """
        Look for the //UNIT_CONVERSION_CALL flag in self.__header_file and replace it with
        the appropriate unit conversion call for each variable for which a unit conversion
        is necessary.
        :return:
        """
        new_file = []
        for i in range(0, len(self.__header_file)):
            if "//UNIT_CONVERSION_CALL" not in self.__header_file[i]:
                new_file.append(self.__header_file[i])
            else:
                for variable in self.variable_list:
                    if variable["external unit"] is not None:
                        new_file.append("\t\t\tthis->%s *= %s;"
                                        % (variable["cpp_name"], self.unitconvertor[variable["external unit"]][variable["internal unit"]]))
        self.__header_file = new_file[:]

    def __definition_of_get_functions_call(self):
        new_file = []
        for i in range(0, len(self.__header_file)):
            if "//DEFINITION_OF_GET_FUNCTIONS" not in self.__header_file[i]:
                new_file.append(self.__header_file[i])
            else:
                for variable in self.variable_list:
                    type = variable["type"]
                    if type in ["string"]:
                        type = "std::" + type
                    new_file.append("\t\t%s %s() { return %s;}" % (type, variable["get_name"], variable["cpp_name"]))
        self.__header_file = new_file[:]

    def __generate_input_file_call(self):
        new_file = []
        for i in range(0, len(self.__header_file)):
            if "//GENERATE_INPUT_FILE" not in self.__header_file[i]:
                new_file.append(self.__header_file[i])
            else:
                for variable in self.variable_list:
                    type = variable["type"]

                    if type == "string":
                        type = "std::" + type

                    new_file.append("\t\t\twrite << \"%s\" << \"    \" << %s << std::endl;"
                                    % (variable["user_name"], variable["cpp_name"]))
        self.__header_file = new_file[:]


    def __user_defined_variables_call(self):
        new_file = []
        for i in range(0, len(self.__header_file)):
            if "//USER_DEFINED_VARIABLES" not in self.__header_file[i]:
                new_file.append(self.__header_file[i])
            else:
                for variable in self.variable_list:
                    type = variable["type"]
                    default = variable["default"]

                    if type == "string":
                        type = "std::" + type
                        default = "\"" + default + "\""

                    if type == "bool":
                        if default == "0" or default.lower() == "false":
                            default = "false"
                        if default == "1" or default.lower() == "true":
                            default = "true"

                    new_file.append("\t\t%s %s = %s;" % (type, variable["cpp_name"], default))
        self.__header_file = new_file[:]

