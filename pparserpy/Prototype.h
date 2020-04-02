#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class Prototype
{
	public:

		Prototype(std::string input_file, char comment = '#')
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


			//LOOK_FOR_VARIABLE_CALL

			//UNIT_CONVERSION_CALL

		}

		~Prototype(){};

		//DEFINITION_OF_GET_FUNCTIONS



		void GenerateInputFile(std::string filename)
		{
			std::ofstream write(filename.c_str());
			assert(write.is_open());
			//GENERATE_INPUT_FILE
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

		//USER_DEFINED_VARIABLES
};

#endif // PROTOTYPE_H
