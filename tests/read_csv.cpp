#include <iostream>

#include "../utils/util.hpp"


int main()
{
	std::vector<unsigned char> raw, tmp;
	std::vector<std::vector<unsigned char> > cut;
	std::cout<<"Read successful ? "<<read("../data/train.csv",raw)<<std::endl;

	//std::cout<<raw<<std::endl;
	std::cout<<load_in_vec(raw, cut)<<" lines in file"<<std::endl;
	std::cout<<"Premiere ligne : "<<cut[0]<<std::endl;

	cut.resize(30); //on ne prend que les 30 premières lignes du fichier
	std::map<std::string,unsigned char> correspondances;
	correspondances[",\"\"\""] = '|';
	correspondances["\"\"\""] = '#';
	correspondances["."] = '@';
	for(unsigned int i=0;i<cut.size();i++)
	{
		//Le paramètre 10 est là pour tester qu'on ne remplace que 10 premières occurences maximum des séparateurs. Si on le supprime on voit facilement que tous les séparateurs sont remplacés
		std::cout<<replace_seq_by(cut[i], tmp, correspondances, 10)<<" replacements of ,\"\"\" by | made and . by @ made and \"\"\" by # made"<<std::endl;
		std::cout<<"=> "<<tmp<<std::endl;
		cut[i] = tmp;
	}

	tmp.resize(10); //on ne teste qu'avec les 10 premières lignes
	std::set<unsigned char> separators = {'|','@',' '};
	std::vector<std::string> words;
	for(auto v : cut)
	{
		std::cout<<load_in_string(v, words, separators)<<" non empty words cut from the vector :"<<std::endl;
		for(auto w : words)
			std::cout<<w<<std::endl;
		std::cout<<std::endl;
	}

	return 0;
}
