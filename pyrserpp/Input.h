#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

class Input
{
	public:

		Input(std::string input_file, char comment = '#')
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


			this->LookForVariable(dmevo_mode_, std::string("DMEvo.Mode"));
			this->LookForVariable(dmevo_computefermi_, std::string("DMEvo.ComputeFermi"));
			this->LookForVariable(dmevo_computeallatoms_, std::string("DMEvo.ComputeAllAtoms"));
			this->LookForVariable(dmevo_selectedatoms_, std::string("DMEvo.SelectedAtoms"));
			this->LookForVariable(matrix_computespin_, std::string("Matrix.ComputeSpin"));
			this->LookForVariable(matrix_computeorbital_, std::string("Matrix.ComputeOrbital"));
			this->LookForVariable(matrix_computespincurrent_, std::string("Matrix.ComputeSpinCurrent"));
			this->LookForVariable(matrix_computeorbitalcurrent_, std::string("Matrix.ComputeOrbitalCurrent"));
			this->LookForVariable(matrix_computespinflux_, std::string("Matrix.ComputeSpinFlux"));
			this->LookForVariable(matrix_computeorbitalflux_, std::string("Matrix.ComputeOrbitalFlux"));
			this->LookForVariable(matrix_computechargedensity_, std::string("Matrix.ComputeChargeDensity"));
			this->LookForVariable(matrix_computechargedensityup_, std::string("Matrix.ComputeChargeDensityUp"));
			this->LookForVariable(matrix_computechargedensitydn_, std::string("Matrix.ComputeChargeDensityDn"));
			this->LookForVariable(matrix_writemomentum_, std::string("Matrix.WriteMomentum"));
			this->LookForVariable(matrix_writeenergy_, std::string("Matrix.WriteEnergy"));
			this->LookForVariable(matrix_writespin_, std::string("Matrix.WriteSpin"));
			this->LookForVariable(matrix_writeorbital_, std::string("Matrix.WriteOrbital"));
			this->LookForVariable(matrix_writespincurrent_, std::string("Matrix.WriteSpinCurrent"));
			this->LookForVariable(matrix_writeorbitalcurrent_, std::string("Matrix.WriteOrbitalCurrent"));
			this->LookForVariable(matrix_writespinflux_, std::string("Matrix.WriteSpinFlux"));
			this->LookForVariable(matrix_writeorbitalflux_, std::string("Matrix.WriteOrbitalFlux"));
			this->LookForVariable(matrix_writechargedensity_, std::string("Matrix.WriteChargeDensity"));
			this->LookForVariable(matrix_writechargedensityup_, std::string("Matrix.WriteChargeDensityUp"));
			this->LookForVariable(matrix_writechargedensitydn_, std::string("Matrix.WriteChargeDensityDn"));
			this->LookForVariable(pert_optics_, std::string("Pert.Optics"));
			this->LookForVariable(pert_spinsusceptibility_, std::string("Pert.SpinSusceptibility"));
			this->LookForVariable(pert_orbitalnsusceptibility_, std::string("Pert.OrbitalnSusceptibility"));
			this->LookForVariable(pert_spinconductivity_, std::string("Pert.SpinConductivity"));
			this->LookForVariable(pert_orbitalconductivity_, std::string("Pert.OrbitalConductivity"));
			this->LookForVariable(pert_ife_, std::string("Pert.IFE"));
			this->LookForVariable(pert_chargedensity_, std::string("Pert.ChargeDensity"));
			this->LookForVariable(pert_chargedensityup_, std::string("Pert.ChargeDensityUp"));
			this->LookForVariable(pert_chargedensitydn_, std::string("Pert.ChargeDensityDn"));
			this->LookForVariable(pert_deltainter_, std::string("Pert.DeltaInter"));
			this->LookForVariable(pert_deltaintra_, std::string("Pert.DeltaIntra"));
			this->LookForVariable(pert_temperature_, std::string("Pert.Temperature"));
			this->LookForVariable(pert_optimization_, std::string("Pert.Optimization"));
			this->LookForVariable(pert_cutoffup_, std::string("Pert.CutOffUp"));
			this->LookForVariable(pert_cutoffdn_, std::string("Pert.CutOffDn"));
			this->LookForVariable(pert_omega_, std::string("Pert.Omega"));
			this->LookForVariable(pert_fermishift_, std::string("Pert.FermiShift"));
			this->LookForVariable(expect_broadeningtype_, std::string("Expect.BroadeningType"));
			this->LookForVariable(expect_broadening_, std::string("Expect.Broadening"));
			this->LookForVariable(expect_dos_, std::string("Expect.DOS"));
			this->LookForVariable(expect_pdos_, std::string("Expect.PDOS"));
			this->LookForVariable(expect_spinmagnetization_, std::string("Expect.SpinMagnetization"));
			this->LookForVariable(expect_orbitalmagnetization_, std::string("Expect.OrbitalMagnetization"));

			this->pert_deltainter_ *= 0.03674932217565;
			this->pert_deltaintra_ *= 0.03674932217565;
			this->pert_temperature_ *= 3.16683e-06;
			this->pert_cutoffup_ *= 0.03674932217565;
			this->pert_cutoffdn_ *= 0.03674932217565;
			for(unsigned i=0; i<pert_omega_.size(); i++)
			{
				pert_omega_[i] *= 0.03674932217565;
			}
			for(unsigned i=0; i<pert_fermishift_.size(); i++)
			{
				pert_fermishift_[i] *= 0.03674932217565;
			}
			this->expect_broadening_ *= 0.03674932217565;

		}

		~Input(){};

		std::string GetDMEvoMode() { return dmevo_mode_;}
		bool GetDMEvoComputeFermi() { return dmevo_computefermi_;}
		bool GetDMEvoComputeAllAtoms() { return dmevo_computeallatoms_;}
		std::vector<int> GetDMEvoSelectedAtoms() { return dmevo_selectedatoms_;}
		bool GetMatrixComputeSpin() { return matrix_computespin_;}
		bool GetMatrixComputeOrbital() { return matrix_computeorbital_;}
		bool GetMatrixComputeSpinCurrent() { return matrix_computespincurrent_;}
		bool GetMatrixComputeOrbitalCurrent() { return matrix_computeorbitalcurrent_;}
		bool GetMatrixComputeSpinFlux() { return matrix_computespinflux_;}
		bool GetMatrixComputeOrbitalFlux() { return matrix_computeorbitalflux_;}
		bool GetMatrixComputeChargeDensity() { return matrix_computechargedensity_;}
		bool GetMatrixComputeChargeDensityUp() { return matrix_computechargedensityup_;}
		bool GetMatrixComputeChargeDensityDn() { return matrix_computechargedensitydn_;}
		bool GetMatrixWriteMomentum() { return matrix_writemomentum_;}
		bool GetMatrixWriteEnergy() { return matrix_writeenergy_;}
		bool GetMatrixWriteSpin() { return matrix_writespin_;}
		bool GetMatrixWriteOrbital() { return matrix_writeorbital_;}
		bool GetMatrixWriteSpinCurrent() { return matrix_writespincurrent_;}
		bool GetMatrixWriteOrbitalCurrent() { return matrix_writeorbitalcurrent_;}
		bool GetMatrixWriteSpinFlux() { return matrix_writespinflux_;}
		bool GetMatrixWriteOrbitalFlux() { return matrix_writeorbitalflux_;}
		bool GetMatrixWriteChargeDensity() { return matrix_writechargedensity_;}
		bool GetMatrixWriteChargeDensityUp() { return matrix_writechargedensityup_;}
		bool GetMatrixWriteChargeDensityDn() { return matrix_writechargedensitydn_;}
		bool GetPertOptics() { return pert_optics_;}
		bool GetPertSpinSusceptibility() { return pert_spinsusceptibility_;}
		bool GetPertOrbitalnSusceptibility() { return pert_orbitalnsusceptibility_;}
		bool GetPertSpinConductivity() { return pert_spinconductivity_;}
		bool GetPertOrbitalConductivity() { return pert_orbitalconductivity_;}
		bool GetPertIFE() { return pert_ife_;}
		bool GetPertChargeDensity() { return pert_chargedensity_;}
		bool GetPertChargeDensityUp() { return pert_chargedensityup_;}
		bool GetPertChargeDensityDn() { return pert_chargedensitydn_;}
		double GetPertDeltaInter() { return pert_deltainter_;}
		double GetPertDeltaIntra() { return pert_deltaintra_;}
		double GetPertTemperature() { return pert_temperature_;}
		double GetPertOptimization() { return pert_optimization_;}
		double GetPertCutOffUp() { return pert_cutoffup_;}
		double GetPertCutOffDn() { return pert_cutoffdn_;}
		std::vector<double> GetPertOmega() { return pert_omega_;}
		std::vector<double> GetPertFermiShift() { return pert_fermishift_;}
		std::string GetExpectBroadeningType() { return expect_broadeningtype_;}
		double GetExpectBroadening() { return expect_broadening_;}
		bool GetExpectDOS() { return expect_dos_;}
		bool GetExpectPDOS() { return expect_pdos_;}
		bool GetExpectSpinMagnetization() { return expect_spinmagnetization_;}
		bool GetExpectOrbitalMagnetization() { return expect_orbitalmagnetization_;}



		void GenerateInputFile(std::string filename)
		{
			std::ofstream write(filename.c_str());
			assert(write.is_open());
			write << "DMEvo.Mode" << "                         " << dmevo_mode_ << std::endl;
			write << "DMEvo.ComputeFermi" << "                 " << dmevo_computefermi_ << std::endl;
			write << "DMEvo.ComputeAllAtoms" << "              " << dmevo_computeallatoms_ << std::endl;

			write << "DMEvo.SelectedAtoms" << "                ";
			for(unsigned i=0; i<dmevo_selectedatoms_.size(); i++)
				write << dmevo_selectedatoms_[i] << " ";
			write << std::endl;

			write << "Matrix.ComputeSpin" << "                 " << matrix_computespin_ << std::endl;
			write << "Matrix.ComputeOrbital" << "              " << matrix_computeorbital_ << std::endl;
			write << "Matrix.ComputeSpinCurrent" << "          " << matrix_computespincurrent_ << std::endl;
			write << "Matrix.ComputeOrbitalCurrent" << "       " << matrix_computeorbitalcurrent_ << std::endl;
			write << "Matrix.ComputeSpinFlux" << "             " << matrix_computespinflux_ << std::endl;
			write << "Matrix.ComputeOrbitalFlux" << "          " << matrix_computeorbitalflux_ << std::endl;
			write << "Matrix.ComputeChargeDensity" << "        " << matrix_computechargedensity_ << std::endl;
			write << "Matrix.ComputeChargeDensityUp" << "      " << matrix_computechargedensityup_ << std::endl;
			write << "Matrix.ComputeChargeDensityDn" << "      " << matrix_computechargedensitydn_ << std::endl;
			write << "Matrix.WriteMomentum" << "               " << matrix_writemomentum_ << std::endl;
			write << "Matrix.WriteEnergy" << "                 " << matrix_writeenergy_ << std::endl;
			write << "Matrix.WriteSpin" << "                   " << matrix_writespin_ << std::endl;
			write << "Matrix.WriteOrbital" << "                " << matrix_writeorbital_ << std::endl;
			write << "Matrix.WriteSpinCurrent" << "            " << matrix_writespincurrent_ << std::endl;
			write << "Matrix.WriteOrbitalCurrent" << "         " << matrix_writeorbitalcurrent_ << std::endl;
			write << "Matrix.WriteSpinFlux" << "               " << matrix_writespinflux_ << std::endl;
			write << "Matrix.WriteOrbitalFlux" << "            " << matrix_writeorbitalflux_ << std::endl;
			write << "Matrix.WriteChargeDensity" << "          " << matrix_writechargedensity_ << std::endl;
			write << "Matrix.WriteChargeDensityUp" << "        " << matrix_writechargedensityup_ << std::endl;
			write << "Matrix.WriteChargeDensityDn" << "        " << matrix_writechargedensitydn_ << std::endl;
			write << "Pert.Optics" << "                        " << pert_optics_ << std::endl;
			write << "Pert.SpinSusceptibility" << "            " << pert_spinsusceptibility_ << std::endl;
			write << "Pert.OrbitalnSusceptibility" << "        " << pert_orbitalnsusceptibility_ << std::endl;
			write << "Pert.SpinConductivity" << "              " << pert_spinconductivity_ << std::endl;
			write << "Pert.OrbitalConductivity" << "           " << pert_orbitalconductivity_ << std::endl;
			write << "Pert.IFE" << "                           " << pert_ife_ << std::endl;
			write << "Pert.ChargeDensity" << "                 " << pert_chargedensity_ << std::endl;
			write << "Pert.ChargeDensityUp" << "               " << pert_chargedensityup_ << std::endl;
			write << "Pert.ChargeDensityDn" << "               " << pert_chargedensitydn_ << std::endl;
			write << "Pert.DeltaInter" << "                    " << pert_deltainter_ << std::endl;
			write << "Pert.DeltaIntra" << "                    " << pert_deltaintra_ << std::endl;
			write << "Pert.Temperature" << "                   " << pert_temperature_ << std::endl;
			write << "Pert.Optimization" << "                  " << pert_optimization_ << std::endl;
			write << "Pert.CutOffUp" << "                      " << pert_cutoffup_ << std::endl;
			write << "Pert.CutOffDn" << "                      " << pert_cutoffdn_ << std::endl;

			write << "Pert.Omega" << "                         ";
			for(unsigned i=0; i<pert_omega_.size(); i++)
				write << pert_omega_[i] << " ";
			write << std::endl;


			write << "Pert.FermiShift" << "                    ";
			for(unsigned i=0; i<pert_fermishift_.size(); i++)
				write << pert_fermishift_[i] << " ";
			write << std::endl;

			write << "Expect.BroadeningType" << "              " << expect_broadeningtype_ << std::endl;
			write << "Expect.Broadening" << "                  " << expect_broadening_ << std::endl;
			write << "Expect.DOS" << "                         " << expect_dos_ << std::endl;
			write << "Expect.PDOS" << "                        " << expect_pdos_ << std::endl;
			write << "Expect.SpinMagnetization" << "           " << expect_spinmagnetization_ << std::endl;
			write << "Expect.OrbitalMagnetization" << "        " << expect_orbitalmagnetization_ << std::endl;
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

		std::string dmevo_mode_ = "Compute";
		bool dmevo_computefermi_ = true;
		bool dmevo_computeallatoms_ = true;
		std::vector<int> dmevo_selectedatoms_ = {1};
		bool matrix_computespin_ = false;
		bool matrix_computeorbital_ = false;
		bool matrix_computespincurrent_ = false;
		bool matrix_computeorbitalcurrent_ = false;
		bool matrix_computespinflux_ = false;
		bool matrix_computeorbitalflux_ = false;
		bool matrix_computechargedensity_ = false;
		bool matrix_computechargedensityup_ = false;
		bool matrix_computechargedensitydn_ = false;
		bool matrix_writemomentum_ = false;
		bool matrix_writeenergy_ = false;
		bool matrix_writespin_ = false;
		bool matrix_writeorbital_ = false;
		bool matrix_writespincurrent_ = false;
		bool matrix_writeorbitalcurrent_ = false;
		bool matrix_writespinflux_ = false;
		bool matrix_writeorbitalflux_ = false;
		bool matrix_writechargedensity_ = false;
		bool matrix_writechargedensityup_ = false;
		bool matrix_writechargedensitydn_ = false;
		bool pert_optics_ = false;
		bool pert_spinsusceptibility_ = false;
		bool pert_orbitalnsusceptibility_ = false;
		bool pert_spinconductivity_ = false;
		bool pert_orbitalconductivity_ = false;
		bool pert_ife_ = false;
		bool pert_chargedensity_ = false;
		bool pert_chargedensityup_ = false;
		bool pert_chargedensitydn_ = false;
		double pert_deltainter_ = 0.4;
		double pert_deltaintra_ = 0.4;
		double pert_temperature_ = 300.0;
		double pert_optimization_ = 1e-7;
		double pert_cutoffup_ = 1000.0;
		double pert_cutoffdn_ = -1000.0;
		std::vector<double> pert_omega_ = {0.0};
		std::vector<double> pert_fermishift_ = {0.0};
		std::string expect_broadeningtype_ = "Gaussian";
		double expect_broadening_ = 0.026;
		bool expect_dos_ = false;
		bool expect_pdos_ = false;
		bool expect_spinmagnetization_ = false;
		bool expect_orbitalmagnetization_ = false;
};

#endif // INPUT_H
