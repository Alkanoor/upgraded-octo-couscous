#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"

#include <iostream>
#include <array>


int main()
{
    Preprocessing p("../data/train.csv");
    p.update_case();
    p.rescale_ascii();
    p.save_in_file("output/modified.txt");

    auto words = p.get_words();
    Vectorizer v(words);

    std::cout<<v.get_ratio_insults()<<std::endl;
    //std::cout<<v.get_dictionary()<<std::endl;
    print_map_sorted(std::cout,v.get_dictionary())<<std::endl;

    return 0;
}
