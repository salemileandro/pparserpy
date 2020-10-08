from .parser import Parser


def main(arg_list):
    print(" _ __  _   _ _ __ ___  ___ _ __ _ __  _ __  ")
    print("| '_ \\| | | | '__/ __|/ _ \\ '__| '_ \\| '_ \\ ")
    print("| |_) | |_| | |  \\__ \\  __/ |  | |_) | |_) |")
    print("| .__/ \\__, |_|  |___/\\___|_|  | .__/| .__/ ")
    print("|_|    |___/                   |_|   |_|    ")
    print("")
    print("Author: Leandro Salemi")
    print("E-mail: salemileandro@gmail.com")
    print("")

    if len(arg_list) != 3:
        print("!!! Error !!!")
        print("Exactly 2 argument must be passed to PParserPy !")
        print("PParserPy must be executed as:")
        print("\t${MY_PATH_TO_PYTHON}/python3 ${MY_PATH_TO_PPARSERPY}/main.py INPUT_FILE NAME_OF_INPUTREADER")
        print("")
        assert(False)

    x = Parser(arg_list[1], name=arg_list[2], verbose=False)
    x.write_header()

    print("Header file %s.h generated !" % arg_list[2])
    print("")
