#include "ReadInput.h"

int main()
{
	ReadInput input_reader("myinput.txt");

	std::cout << "Testing Get_Test_Var0    ";
	std::cout << input_reader.Get_Test_Var0() << std::endl;

	std::cout << "Testing Get_Test_Var1    ";
	std::cout << input_reader.Get_Test_Var1() << std::endl;

	std::cout << "Testing Get_Test_Var2    ";
	std::cout << input_reader.Get_Test_Var2() << std::endl;

	std::cout << "Testing Get_Test_Var3    ";
	std::cout << input_reader.Get_Test_Var3() << std::endl;

	std::cout << "Testing Get_Test_Var4    ";
	std::cout << input_reader.Get_Test_Var4() << std::endl;

	std::cout << "Testing Get_Test_Var5    ";
	std::cout << std::endl;
	auto v0 = input_reader.Get_Test_Var5();
	for(auto elem:  v0)
	    std::cout << elem << std::endl;
   std::cout << std::endl;

	std::cout << "Testing Get_Test_Var6    ";
	std::cout << std::endl;
	auto v1 = input_reader.Get_Test_Var6();
	for(auto elem:  v1)
	    std::cout << elem << std::endl;
   std::cout << std::endl;

	std::cout << "Testing Get_Test_Var7    ";
	std::cout << std::endl;
	auto v2 = input_reader.Get_Test_Var7();
	for(auto elem:  v2)
	    std::cout << elem << std::endl;
   std::cout << std::endl;

	std::cout << "Testing Get_Test_Var8    ";
	std::cout << std::endl;
	auto v3 = input_reader.Get_Test_Var8();
	for(auto elem:  v3)
	    std::cout << elem << std::endl;
   std::cout << std::endl;

	std::cout << "Testing Get_Test_Var9    ";
	std::cout << std::endl;
	auto v4 = input_reader.Get_Test_Var9();
	for(auto elem:  v4)
	    std::cout << elem << std::endl;
   std::cout << std::endl;

	return 0;
}
