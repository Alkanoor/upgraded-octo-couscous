#include <iostream>

#include "../utils/util.hpp"


int main()
{
	std::vector<unsigned char> raw, tmp;
	std::vector<std::vector<unsigned char> > cut;
	std::cout<<"Read successful ? "<<read("../data/train.csv",raw)<<std::endl;

	std::cout<<load_in_vec(raw, cut)<<" lines in file"<<std::endl;
	std::map<std::string,unsigned char> correspondances;

	correspondances["\\xa0"]=' ';
	correspondances["\\xa1"]=' ';
	correspondances["\\xa3"]=' ';
	correspondances["\\xa9"]=' ';
	correspondances["\\xe1"]='a';
	correspondances["\\xe3"]='a';
	correspondances["\\xe7"]='c';
	correspondances["\\xfd"]='y';
	correspondances["\\xed"]='i';
	correspondances["\\xfa"]='u';
	correspondances["\\xf8"]='o';
	correspondances["\\xf6"]='o';
	correspondances["\\xdc"]='U';
	correspondances["\\xe0"]='a';
	correspondances["\\xe9"]='e';
	correspondances["\\xe8"]='e';
	correspondances["\\xfc"]='u';
	correspondances["\\n"]=' ';
	correspondances["\\xbf"]=' ';
	correspondances["\\xf1"]='n';
	correspondances["\\xc2"]='A';
	correspondances["\\xb7"]=' ';
	correspondances["\\r"]=' ';
	correspondances["\\ufeff"]=' ';
	correspondances["\\u2018"]='\'';
	correspondances["\\u2019"]='\'';
	correspondances["\\u1ee9"]='u';
	correspondances["\\u1ec3"]='e';
	correspondances["\\u1ef1"]='a';
	correspondances["\\u2013"]=' ';
	correspondances["\\u2016"]=' ';
	correspondances["\\u200f"]=' ';
	correspondances["\\u0105"]='a';
	correspondances["\\u0111"]='d';
	correspondances["\\u1ec5"]='e';
	correspondances["\\u1ebf"]='e';
	correspondances["\\u1eb7"]='a';
	correspondances["\\u0169"]='u';
	correspondances["\\u0142"]='l';
	correspondances["\\u201c"]='\"';
	correspondances["\\u201d"]='\"';
	correspondances["\\u201e"]='\"';
	correspondances["\\u2026"]='.';
	correspondances["\\u0161"]='s';
	correspondances["\\u2665"]=' ';
	correspondances["\\u015b"]='s';
	correspondances["\\u203d"]='!';
	correspondances["\\xf3"]='o';
	correspondances["\\u0119"]='e';
	correspondances["\\u017a"]='Z';
	correspondances["\\u017e"]='Z';
	correspondances["\\u017c"]='Z';
	correspondances["\\u0107"]='c';
	correspondances["\\xe5"]='a';
	correspondances["\\xe4"]='a';
	correspondances["\\U0001f308"]=' ';
	correspondances["\\U0001f3e9"]=' ';
	correspondances["\\U0001f48b"]=' ';
	correspondances["\\\\"]=' ';
	correspondances["\\ "]=' ';

	for(unsigned int i=0;i<cut.size();i++)
	{
		std::cout<<replace_seq_by(cut[i], tmp, correspondances)<<std::endl;
		std::cout<<"=> "<<tmp<<std::endl;
		cut[i] = tmp;
	}



	return 0;
}
