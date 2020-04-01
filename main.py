from utils import *
from PParserPy import PParserPy


x = PParserPy("pppy.in", name="ReadInput", verbose=True)

type_list = ["double", "int", "string", "bool"]

type_list = type_list + ["vec " + f for f in type_list]
print(type_list)
