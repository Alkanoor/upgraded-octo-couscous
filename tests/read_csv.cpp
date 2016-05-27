#include <iostream>

#include "../utils/util.hpp"


int main()
{
	std::vector<unsigned char> raw;
	std::cout<<"Read successful ? "<<read("../data/train.csv",raw)<<std::endl;

	std::cout<<raw<<std::endl;
	return 0;
}