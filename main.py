from PParserPy import PParserPy
import sys

print(" ____  ____                          ____        ")
print("|  _ \|  _ \ __ _ _ __ ___  ___ _ __|  _ \ _   _ ")
print("| |_) | |_) / _` | '__/ __|/ _ \ '__| |_) | | | |")
print("|  __/|  __/ (_| | |  \__ \  __/ |  |  __/| |_| |")
print("|_|   |_|   \__,_|_|  |___/\___|_|  |_|    \__, |")
print("                                           |___/ ")
print("")
print("Author: Leandro Salemi")
print("E-mail: salemileandro@gmail.com")
print("")


arg_list = sys.argv
if len(arg_list) != 2:
    print("!!! Error !!!")
    print("Exactly 1 argument must be passed to PParserPy !")
    print("PParserPy must be executed as:")
    print("\t${MY_PATH_TO_PYTHON}/python3 ${MY_PATH_TO_PPARSERPY}/main.py name_of_inputreader_class")
    print("")
    assert(False)

x = PParserPy("pppy.in", name=arg_list[1], verbose=False)

print("Header file %s.h generated !" % arg_list[1])
print("")