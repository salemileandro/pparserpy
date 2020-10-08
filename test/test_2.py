import pyrserpp
import sys

print(sys.path)

print(pyrserpp.Leandroadd(3.0, 4.0))

exit()




import os
from .PParserPy import *
from .Variable import  *
import shutil



if os.path.exists(os.path.join(os.path.dirname(__file__), "myinput.txt")):
    os.remove(os.path.join(os.path.dirname(__file__), "myinput.txt"))


test_list = [("double", "10.0", "None", "None"),
             ("double", "10.0", "m", "feet"),
             ("int", "1", "None", "None"),
             ("bool", "1", "None", "None"),
             ("string", "This_is_my_string_sentence", "None", "None"),
             ("vector double", "0 1 2 3", "None", "None"),
             ("vector double", "0 1 2 3", "m", "feet"),
             ("vector int", "0 1 2 3", "None", "None"),
             ("vector bool", "0 1 0 1", "None", "None"),
             ("vector string", "This is my string sentence", "None", "None"),
             ]

idx = 0
ppin = "pparserpy_test.in"
f = open(ppin, "w+")
for t in test_list:
    f.write("!new_var\n")
    f.write("\tNamespace     = Test\n")
    f.write("\tName          = Var%d\n" % idx)
    idx += 1
    f.write("\tType          = %s\n" % t[0])
    f.write("\tDefault       = %s\n" % t[1])
    f.write("\tExternal Unit = %s\n" % t[2])
    f.write("\tInternal Unit = %s\n" % t[3])
    f.write("\tComment       = Testing a variable of type %s with units %s % s\n" % (t[0], t[2], t[3]))
    f.write("\n")

for x in [("m", "feet", "3.28084"),("fs", "s", "1e-15")]:
    f.write("!new_unit\n")
    f.write("\tExternal Unit = %s\n" % x[0])
    f.write("\tInternal Unit = %s\n" % x[1])
    f.write("\tConversion    = %s\n" % x[2])
    f.write("\n")
f.close()


x = PParserPy(ppin, name="ReadInput", verbose=False)
x.write_header()

print("Header file %s.h generated !" % "ReadInput")
print("")


idx = 0
f = open("main.cpp", "w+")
f.write("#include \"ReadInput.h\"\n")
f.write("\n")
f.write("int main()\n")
f.write("{\n")
f.write("	ReadInput input_reader(\"myinput.txt\");\n")
f.write("\n")
for var in x.variable_list:
    f.write("	std::cout << \"Testing %s    \";\n" % var["get_name"])
    if "vector" in var["type"]:
        f.write("	std::cout << std::endl;\n")
        f.write("	auto v%d = input_reader.%s();\n" % (idx, var["get_name"]))
        f.write("	for(auto elem:  v%d)\n" % (idx))
        f.write("	    std::cout << elem << std::endl;\n")
        f.write("   std::cout << std::endl;\n")
        f.write("\n")
        idx += 1
    else:
        f.write("	std::cout << input_reader.%s() << std::endl;\n" % var["get_name"])
        f.write("\n")
f.write("	return 0;\n")
f.write("}\n")
f.close()

os.system("make")
os.system("./main")