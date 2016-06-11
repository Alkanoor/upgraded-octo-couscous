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
    auto scores = v.get_scores();
    print_map_sorted(std::cout,scores,20)<<std::endl;

    return 0;
}
