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


			this->LookForVariable(timeaxis_start_, std::string("TimeAxis.Start"));
			this->LookForVariable(timeaxis_end_, std::string("TimeAxis.End"));
			this->LookForVariable(timeaxis_nsteps_, std::string("TimeAxis.Nsteps"));
			this->LookForVariable(file_loadpotential_, std::string("File.LoadPotential"));
			this->LookForVariable(file_potential_, std::string("File.Potential"));
			this->LookForVariable(occupation_n_, std::string("Occupation.n"));
			this->LookForVariable(random_text_, std::string("Random.text"));
			this->LookForVariable(test_vectordoubleunitconv_, std::string("Test.VectorDoubleUnitConv"));

			this->timeaxis_start_ *= 2.4188843265857e-17;
			this->timeaxis_end_ *= 2.4188843265857e-17;
			for(unsigned i=0; i<test_vectordoubleunitconv_.size(); i++)
			{
				test_vectordoubleunitconv_[i] *= 2.4188843265857e-17;
			}

        }

        ~ReadInput(){};

		double Get_TimeAxis_Start() { return timeaxis_start_;}
		double Get_TimeAxis_End() { return timeaxis_end_;}
		int Get_TimeAxis_Nsteps() { return timeaxis_nsteps_;}
		bool Get_File_LoadPotential() { return file_loadpotential_;}
		std::string Get_File_Potential() { return file_potential_;}
		std::vector<int> Get_Occupation_n() { return occupation_n_;}
		std::vector<std::string> Get_Random_text() { return random_text_;}
		std::vector<double> Get_Test_VectorDoubleUnitConv() { return test_vectordoubleunitconv_;}



		void GenerateInputFile(std::string filename)
		{
			std::ofstream write(filename.c_str());
			assert(write.is_open());
			write << "TimeAxis.Start" << "                " << timeaxis_start_ << std::endl;
			write << "TimeAxis.End" << "                  " << timeaxis_end_ << std::endl;
			write << "TimeAxis.Nsteps" << "               " << timeaxis_nsteps_ << std::endl;
			write << "File.LoadPotential" << "            " << file_loadpotential_ << std::endl;
			write << "File.Potential" << "                " << file_potential_ << std::endl;

			write << "Occupation.n" << "                  ";
			for(unsigned i=0; i<occupation_n_.size(); i++)
				write << occupation_n_[i] << " ";
			write << std::endl;


			write << "Random.text" << "                   ";
			for(unsigned i=0; i<random_text_.size(); i++)
				write << random_text_[i] << " ";
			write << std::endl;


			write << "Test.VectorDoubleUnitConv" << "     ";
			for(unsigned i=0; i<test_vectordoubleunitconv_.size(); i++)
				write << test_vectordoubleunitconv_[i] << " ";
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
					for(unsigned i=1; i<words.size(); i++)
					{
						variable.push_back(std::stod(words[i]));
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

		double timeaxis_start_ = 0.0;
		double timeaxis_end_ = 10.0;
		int timeaxis_nsteps_ = 1000;
		bool file_loadpotential_ = false;
		std::string file_potential_ = "potential.dat";
		std::vector<int> occupation_n_ = {1,2,3};
		std::vector<std::string> random_text_ = {"this","is","a","sentence"};
		std::vector<double> test_vectordoubleunitconv_ = {0.0,1.0,2.0,3.0};
};

#endif // READINPUT_H
