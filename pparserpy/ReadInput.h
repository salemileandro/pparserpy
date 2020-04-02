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


			this->LookForVariable(test_var0_, std::string("Test.Var0"));
			this->LookForVariable(test_var1_, std::string("Test.Var1"));
			this->LookForVariable(test_var2_, std::string("Test.Var2"));
			this->LookForVariable(test_var3_, std::string("Test.Var3"));
			this->LookForVariable(test_var4_, std::string("Test.Var4"));
			this->LookForVariable(test_var5_, std::string("Test.Var5"));
			this->LookForVariable(test_var6_, std::string("Test.Var6"));
			this->LookForVariable(test_var7_, std::string("Test.Var7"));
			this->LookForVariable(test_var8_, std::string("Test.Var8"));
			this->LookForVariable(test_var9_, std::string("Test.Var9"));

			this->test_var1_ *= 3.28084;
			for(unsigned i=0; i<test_var6_.size(); i++)
			{
				test_var6_[i] *= 3.28084;
			}

		}

		~ReadInput(){};

		double Get_Test_Var0() { return test_var0_;}
		double Get_Test_Var1() { return test_var1_;}
		int Get_Test_Var2() { return test_var2_;}
		bool Get_Test_Var3() { return test_var3_;}
		std::string Get_Test_Var4() { return test_var4_;}
		std::vector<double> Get_Test_Var5() { return test_var5_;}
		std::vector<double> Get_Test_Var6() { return test_var6_;}
		std::vector<int> Get_Test_Var7() { return test_var7_;}
		std::vector<bool> Get_Test_Var8() { return test_var8_;}
		std::vector<std::string> Get_Test_Var9() { return test_var9_;}



		void GenerateInputFile(std::string filename)
		{
			std::ofstream write(filename.c_str());
			assert(write.is_open());
			write << "Test.Var0" << "                     " << test_var0_ << std::endl;
			write << "Test.Var1" << "                     " << test_var1_ << std::endl;
			write << "Test.Var2" << "                     " << test_var2_ << std::endl;
			write << "Test.Var3" << "                     " << test_var3_ << std::endl;
			write << "Test.Var4" << "                     " << test_var4_ << std::endl;

			write << "Test.Var5" << "                     ";
			for(unsigned i=0; i<test_var5_.size(); i++)
				write << test_var5_[i] << " ";
			write << std::endl;


			write << "Test.Var6" << "                     ";
			for(unsigned i=0; i<test_var6_.size(); i++)
				write << test_var6_[i] << " ";
			write << std::endl;


			write << "Test.Var7" << "                     ";
			for(unsigned i=0; i<test_var7_.size(); i++)
				write << test_var7_[i] << " ";
			write << std::endl;


			write << "Test.Var8" << "                     ";
			for(unsigned i=0; i<test_var8_.size(); i++)
				write << test_var8_[i] << " ";
			write << std::endl;


			write << "Test.Var9" << "                     ";
			for(unsigned i=0; i<test_var9_.size(); i++)
				write << test_var9_[i] << " ";
			write << std::endl;

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

		double test_var0_ = 10.0;
		double test_var1_ = 10.0;
		int test_var2_ = 1;
		bool test_var3_ = true;
		std::string test_var4_ = "This_is_my_string_sentence";
		std::vector<double> test_var5_ = {0,1,2,3};
		std::vector<double> test_var6_ = {0,1,2,3};
		std::vector<int> test_var7_ = {0,1,2,3};
		std::vector<bool> test_var8_ = {0,1,0,1};
		std::vector<std::string> test_var9_ = {"This","is","my","string","sentence"};
};

#endif // READINPUT_H
