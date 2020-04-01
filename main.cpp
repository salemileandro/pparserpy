#include "ReadInput.h"

int main()
{
	ReadInput input_reader("myinput3.txt");
	
	std::cout << "Testin the Get functions" << std::endl;
	std::cout << "input_reader.Get_TimeAxis_Start() = " << input_reader.Get_TimeAxis_Start() << std::endl;
	std::cout << "input_reader.Get_TimeAxis_End() = " << input_reader.Get_TimeAxis_End() << std::endl;
	std::cout << "input_reader.Get_TimeAxis_Nsteps() = " << input_reader.Get_TimeAxis_Nsteps() << std::endl;
	std::cout << "input_reader.Get_File_LoadPotential() = " << input_reader.Get_File_LoadPotential() << std::endl;
	std::cout << "input_reader.Get_File_Potential() = " << input_reader.Get_File_Potential() << std::endl;	
	
	auto v = input_reader.Get_Test_VectorDoubleUnitConv();
	std::cout << "input_reader.Get_Test_VectorDoubleUnitConv() = " << std::endl;
	for( auto elem: v )
		std::cout << elem << std::endl;
		
	auto v1 = input_reader.Get_Random_text();
	std::cout << "input_reader.Get_Random_text() = " << std::endl;
	for( auto elem: v1 )
		std::cout << elem << std::endl;

	return 0;
}
