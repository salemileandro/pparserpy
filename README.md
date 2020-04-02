# PParserPy
Author: Leandro Salemi <br>
E-mail: salemileandro@gmail.com

Small python utility to generate C++ header-only input parser.

## Introduction
PParserPy is a lightweigth generator of C++ header file for user-friendly input parsing. The idea is to write an input file for PParserPy for your project that will handle the generation of the C++ header file. The PParserPy input file allows you to define two kind of quantities:
1. Variables, declared with the `!new_var` flag.
2. Unit conversion, declared with the `!new_unit` flag.

Variables are defined by several fields. Some are compulsory, others might be ommited. The compulsory fields are : <br>
1. Namespace: The category to which the variable belong to<br>
2. Name: The name of the variable (pick something that is easy to understand)<br>
3. Type: A type, at this stage int, bool, double, string and their vector (vector of int, vector of double, ...) are defined


The facultative fields are:<br>
4. Default: A default value, that is a value that will be assigned to the variable if the user does not define it. Can be set to None, in which case, the default is set to 0 for int, double, false for bool and "" to string<br>
5. External Unit: The name of the external unit. Can be set to None, in which case no conversion will be performed<br>
6. Internal Unit: The name of the internal unit. Can be set to None, in which case no conversion will be performed<br>
7. Comment: A brief comment that could help understand better the meaning of the variable<br>


Unit conversion objects are defined by 3 compulsory fields:<br>
1. External Unit: The name of the external unit.<br>
2. Internal Unit: The name of the internal unit.<br>
3. Conversion: The conversion factor, i.e. the number you need to multiply your value in external unit to obtain internal unit.



## Usage 
PParserPy does not require external libraries as it only depends on Python standard libraries. You will need a python3 installation though. It is always best to learn through an example. Let's say that we want to solve the 1D diffusion equation.

`d_phi(x,t)/d_t = D d^2_phi(x,t)/d_x^2`

where phi(x,t) is the density at position x and time t and D the diffusion constant. To solve this problem using a brute force finite-difference method, one would need to define: <br>
- A 2D grid (x, t), where x would go from `x_start` to `x_end` with `N_x` points and t from `t_start` to `t_end` with `N_t` points <br>
- The diffusion consant `D`<br>
(Note that this is a quite minimalistic definition of a solver ... One would need to define boundary and initial conditions, but we will just disregard those for the sake of simplicity !). <br>
Let' also assume, for the sake of this example, that for some (obscure) reason we require the user to input`x_start` to `x_end` in meters (m) but want to work internally in centimeters (cm).



We first define the input file for PParserPy . Let's call it pppy.in:<br>
pppy.in: 
```
# Input file for PParserPy for the 1D diffusion equation problem

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = X_Start    # The variable will be then referred to by Grid.X_start
  Type          = double     # The type is floating point (double precision)
  Default       = 0.0        # By default our spatial domain starts at 0.0 m
  External Unit = m          # External units in meters (m)
  Internal Unit = cm         # Internal units in centimeters (cm)
  Comment       = Left boundary of the real space axis x

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = X_End      # The variable will be then referred to by Grid.X_start
  Type          = double     # The type is floating point (double precision)
  Default       = 10.0       # By default our spatial domain ends at 10.0 m
  External Unit = m          # External units in meters (m)
  Internal Unit = cm         # Internal units in centimeters (cm)
  Comment       = Right boundary of the real space axis x

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = N_X        # The variable will be then referred to by Grid.N_X
  Type          = int        # The type is floating point (double precision)
  Default       = 1000       # By default our spatial domain contains 1000 points
  External Unit = None
  Internal Unit = None
  Comment       = Number of points along the x axis. Include the boundary points.

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = T_Start    # The variable will be then referred to by Grid.T_Start
  Type          = double     # The type is floating point (double precision)
  Default       = 0.0        # By default our time domain starts at 0
  External Unit = None       # External units will be the same as internal
  Internal Unit = None
  Comment       = Starting point in the time axis

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = T_End      # The variable will be then referred to by Grid.T_End
  Type          = double     # The type is floating point (double precision)
  Default       = 100.0      # By default our time domain ends at 100
  External Unit = None       # External units will be the same as internal
  Internal Unit = None
  Comment       = Ending point in the time axis

!new_var                     # The !new_var flag defines a new variable
  Namespace     = Grid
  Name          = N_T        # The variable will be then referred to by Grid.N_T
  Type          = int        # The type is floating point (double precision)
  Default       = 1000       # By default our time domain contains 1000 points
  External Unit = None
  Internal Unit = None
  Comment       = Number of points along the x axis. Include the boundary points.
 
!new_unit # The !new_unit flag defines a new unit conversion rule
  External Unit = m    # meter ( everything after a # is a comment)
  Internal Unit = cm   # centimenter
  Conversion = 1e2     # conversion from m to cm, i.e. x[cm] = 1e2 * x[m]
```


If we run PParserPy with this particular input by doing $ python3 ${PATH_TO_PPARSERPY}/pparserpy/main.py ReadInput, we end up with the ReadInput.h file: <br>
ReadInput.h
```
#ifndef READINPUT_H
#define READINPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class ReadInput
{
	public:

		ReadInput(std::string input_file, char comment = '#')
		{
		/* ***************************
		*** READING THE INPUT FILE ***
		******************************/
			if( !this->IsFileExists(input_file) )
			{
				this->GenerateInputFile(input_file);
			}
			this->input_file_ = input_file;
			std::ifstream read(this->input_file_);
			assert(read.is_open());

			std::string tmp;
			std::string line;
			this->input_text_.clear();
			while( !read.eof() )
			{
				std::getline(read, line);
				tmp = "";
				for(unsigned i=0; i<line.size(); i++)
				{
					if(line[i] == comment)
						break;
					else
						tmp += line[i];
				}
				if( tmp.size() > 1)
					this->input_text_.push_back(tmp);
			}
			read.close();


			this->LookForVariable(grid_x_start_, std::string("Grid.X_Start"));
			this->LookForVariable(grid_x_end_, std::string("Grid.X_End"));
			this->LookForVariable(grid_n_x_, std::string("Grid.N_X"));
			this->LookForVariable(grid_t_start_, std::string("Grid.T_Start"));
			this->LookForVariable(grid_t_end_, std::string("Grid.T_End"));
			this->LookForVariable(grid_n_t_, std::string("Grid.N_T"));
			this->LookForVariable(parameter_diffusionconstant_, std::string("Parameter.DiffusionConstant"));

			this->grid_x_start_ *= 100.0;
			this->grid_x_end_ *= 100.0;

		}

		~ReadInput(){};

		double Get_Grid_X_Start() { return grid_x_start_;}
		double Get_Grid_X_End() { return grid_x_end_;}
		int Get_Grid_N_X() { return grid_n_x_;}
		double Get_Grid_T_Start() { return grid_t_start_;}
		double Get_Grid_T_End() { return grid_t_end_;}
		int Get_Grid_N_T() { return grid_n_t_;}
		double Get_Parameter_DiffusionConstant() { return parameter_diffusionconstant_;}



		void GenerateInputFile(std::string filename)
		{
			std::ofstream write(filename.c_str());
			assert(write.is_open());
			write << "Grid.X_Start" << "                  " << grid_x_start_ << std::endl;
			write << "Grid.X_End" << "                    " << grid_x_end_ << std::endl;
			write << "Grid.N_X" << "                      " << grid_n_x_ << std::endl;
			write << "Grid.T_Start" << "                  " << grid_t_start_ << std::endl;
			write << "Grid.T_End" << "                    " << grid_t_end_ << std::endl;
			write << "Grid.N_T" << "                      " << grid_n_t_ << std::endl;
			write << "Parameter.DiffusionConstant" << "   " << parameter_diffusionconstant_ << std::endl;
			write.close();
		}

	protected:

	private:

		inline bool IsFileExists (const std::string& filename)
		{
			std::ifstream f(filename.c_str());
			return f.good();
		}

		std::vector<std::string> Split(std::string str, char separator = ' ')
		{
			std::vector<std::string> words;
			std::string temp;

			temp = "";
			for(unsigned i=0; i<str.size(); i++)
			{
				if(str[i] != separator)
					temp += str[i];
				else
				{
					if( temp != "" )
					{
						words.push_back(temp);
						temp = "";
					}
				}
			}
			if( temp != "" )
			{
				words.push_back(temp);
				temp = "";
			}

			return words;
		}

	/* *******************************************
	*** LookForVariable FUNCTIONS (Multi-Type) ***
	**********************************************/
		void LookForVariable(bool &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					if (words[1] == "0" || words[1] == "false" || words[1] == "False" )
						variable = false;
					if (words[1] == "1" || words[1] == "true" || words[1] == "True" )
						variable = true;
					break;
				}
			}
			return;
		}

		void LookForVariable(int &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable = std::stoi(words[1]);
					break;
				}
			}
			return;
		}

		void LookForVariable(double &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable = std::stod(words[1]);
					break;
				}
			}
			return;
		}

		void LookForVariable(std::string &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable = words[1];
					break;
				}
			}
			return;
		}

		void LookForVariable(std::vector<double> &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable.clear();
					if(words[1].find(':') != std::string::npos && words.size() == 2)
					{
						auto bound = this->Split(words[1], ':');
						assert(bound.size() == 3);
						double x_start = std::stod(bound[0]);
						double x_end   = std::stod(bound[1]);
						int N = std::stoi(bound[2]);
						double dx = (x_end - x_start) / (N - 1);
						variable.resize(N);
						variable[0] = x_start;
						for(unsigned i=1; i<N; i++)
						{
							variable[i] = variable[i-1] + dx;
						}
					}
					else
					{
						for(unsigned i=1; i<words.size(); i++)
						{
							variable.push_back(std::stod(words[i]));
						}
					}
				}
			}
			return;
		}

		void LookForVariable(std::vector<int> &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable.clear();
					for(unsigned i=1; i<words.size(); i++)
					{
						variable.push_back(std::stoi(words[i]));
					}
				}
			}
			return;
		}

		void LookForVariable(std::vector<bool> &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable.clear();
					for(unsigned i=1; i<words.size(); i++)
					{
						if(words[i] == "true" || words[i] == "TRUE" || words[i] == "1")
							variable.push_back(true);
						else if(words[i] == "false" || words[i] == "FALSE" || words[i] == "0")
							variable.push_back(false);
						else
							variable.push_back(false);
					}
				}
			}
			return;
		}

		void LookForVariable(std::vector<std::string> &variable, std::string variable_name)
		{
			for(unsigned i=0; i<this->input_text_.size(); i++)
			{
				auto words = this->Split(input_text_[i]);
				if (variable_name == words[0])
				{
					variable.clear();
					for(unsigned i=1; i<words.size(); i++)
					{
						variable.push_back(words[i]);
					}
				}
			}
			return;
		}

		std::string input_file_;
		std::vector<std::string> input_text_;

		double grid_x_start_ = 0.0;
		double grid_x_end_ = 10.0;
		int grid_n_x_ = 1000;
		double grid_t_start_ = 0.0;
		double grid_t_end_ = 100.0;
		int grid_n_t_ = 1000;
		double parameter_diffusionconstant_ = 1.5;
};

#endif // READINPUT_H
```


You don't really need to read this file, that's the main goal of PParserPy !

```
#include "ReadInput.h"

int main()
{
	ReadInput input_reader("input.in");
	return 0;
}

```

input.in:

```
Grid.X_Start                  0
Grid.X_End                    10
Grid.N_X                      1000
Grid.T_Start                  0
Grid.T_End                    100
Grid.N_T                      1000
Parameter.DiffusionConstant   1.5
```
