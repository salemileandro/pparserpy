#include "ReadInput.h"

int main()
{
	ReadInput input_reader("myinput.txt");
	
	std::cout << "Testin the Get functions" << std::endl;
	std::cout << "input_reader.Get_TimeAxis_Start() = " << input_reader.Get_TimeAxis_Start() << std::endl;
	std::cout << "input_reader.Get_TimeAxis_End() = " << input_reader.Get_TimeAxis_End() << std::endl;
	std::cout << "input_reader.Get_TimeAxis_Nsteps() = " << input_reader.Get_TimeAxis_Nsteps() << std::endl;
	std::cout << "input_reader.Get_File_LoadPotential() = " << input_reader.Get_File_LoadPotential() << std::endl;
	std::cout << "input_reader.Get_File_Potential() = " << input_reader.Get_File_Potential() << std::endl;	

	return 0;
}
