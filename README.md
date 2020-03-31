# PParserPy
Author: Leandro Salemi
E-mail: salemileandro@gmail.com

Small python utility to generate C++ header-only input parser.

## Usage 
First, the user needs to define an input file for PParserPy. A typical input file will look like that <br><br>
pparserpy.in: 
```
# Template for the pparserpy input file. the "#" char defines comment
# Supported field names:
#   -> Namespace, Name, Type, Default, External Unit, Internal Unit, Comment.
#   -> Conversion (only needed for !new_unit)
# Supported types:
#   -> int, double, string, bool

!new_var  # The !new_var flag defines a new variable
  Namespace     = TimeAxis
  Name          = Start
  Type          = double
  Default       = 0.0
  External Unit = fs    # femtosecond ( everything after a # is a comment)
  Internal Unit = s     # second
  Comment       = Starting time for the simulation.
 
!new_unit # The !new_unit flag defines a new unit conversion rule
  External Unit = fs    # femtosecond ( everything after a # is a comment)
  Internal Unit = s     # second
  Conversion = 1e-15    # conversion from fs to s, i.e. x[s] = conversion * x[fs]
```
