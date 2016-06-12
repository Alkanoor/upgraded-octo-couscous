#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"

#include <iostream>
#include <fstream>
#include <array>


int main()
{
    Preprocessing p("../data/train.csv");
    p.save_in_file("output/train_modified.txt");

    auto words = p.get_words();
    Vectorizer v(words);

    std::cout<<v.get_ratio_insults()<<std::endl;
    auto scores = v.get_scores();
    print_map_sorted(std::cout,scores,20)<<std::endl;

    std::ofstream words_out("output/train_all_words.txt",std::ios::out);
    words_out<<v.get_dictionary();
    words_out.close();


    p = Preprocessing("../data/test.csv");
    p.save_in_file("output/test_modified.txt");

    words = p.get_words();
    v = Vectorizer(words);

    words_out.open("output/test_all_words.txt",std::ios::out);
    words_out<<v.get_dictionary();

    return 0;
}
