#include "../utils/comparaison_train_test.hpp"
#include "../utils/preprocessing.hpp"

#include <fstream>


int main()
{
	Comparaison_Train_Test for_dictionary;
	
	#ifdef REGEX_ENABLED
	std::cout<<"We are in type regex"<<std::endl;
	#else
	std::cout<<"We are in type non regex"<<std::endl;
	#endif
	
	
    Preprocessing p("../data/train.csv");
	auto words = p.get_words();
    Vectorizer v(words);
	for_dictionary.load_dictionary(v.get_dictionary());
	
	std::ofstream after_regexing("output/train_after_preprocessing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        for(unsigned int j=0;j<words[i].size();j++)
            after_regexing<<words[i][j]<<" ";
        after_regexing<<std::endl;
    }
    after_regexing.close();
	
	#ifdef REGEX_ENABLED
	v.save_to_file("output/vectorized_train_regex_non_lemmatisation.txt");
	for_dictionary.save_dictionary("output/dictionary_regex_non_lemmatisation.txt");
	#else
	v.save_to_file("output/vectorized_train_non_regex_non_lemmatisation.txt");
	for_dictionary.save_dictionary("output/dictionary_non_regex_non_lemmatisation.txt");
	#endif
	

    Preprocessing p2("../data/test.csv");
	words = p2.get_words();
    Vectorizer v2(words);
	for_dictionary.load_dictionary(v2.get_dictionary());
	
	after_regexing.open("output/test_after_preprocessing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        for(unsigned int j=0;j<words[i].size();j++)
            after_regexing<<words[i][j]<<" ";
        after_regexing<<std::endl;
    }
    after_regexing.close();
	
	#ifdef REGEX_ENABLED
	v2.save_to_file("output/vectorized_test_regex_non_lemmatisation.txt");
	#else
	v2.save_to_file("output/vectorized_test_non_regex_non_lemmatisation.txt");
	#endif

	
    Comparaison_Train_Test comparaison("output/train_after_preprocessing.txt","output/test_after_preprocessing.txt");
	
	#ifdef REGEX_ENABLED
    comparaison.save_dictionary("output/dictionary_regex_lemmatisation.txt");
    Vectorizer::save(comparaison.train(),"output/vectorized_train_regex_lemmatisation.txt");
    Vectorizer::save(comparaison.test(),"output/vectorized_test_regex_lemmatisation.txt");
	#else
	comparaison.save_dictionary("output/dictionary_non_regex_lemmatisation.txt");
    Vectorizer::save(comparaison.train(),"output/vectorized_train_non_regex_lemmatisation.txt");
    Vectorizer::save(comparaison.test(),"output/vectorized_test_non_regex_lemmatisation.txt");
	#endif

    return 0;
}
