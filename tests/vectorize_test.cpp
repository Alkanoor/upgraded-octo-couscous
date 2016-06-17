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

    std::ofstream words_out("output/train_all_words.txt",std::ios::out);
    words_out<<v.get_counter();
    for(int i=0;i<10;i++)
        words_out<<std::endl;
    words_out<<v.get_counter_different_comments();
    words_out.close();

    std::ofstream clean_out("output/train_all_words_less.txt",std::ios::out);
    print_map_sorted(clean_out,v.get_counter(),500,true);
    for(int i=0;i<10;i++)
        clean_out<<std::endl;
    print_map_sorted(clean_out,v.get_counter_different_comments(),500,true);
    clean_out.close();


    p = Preprocessing("../data/test.csv");
    p.save_in_file("output/test_modified.txt");

    words = p.get_words();
    v = Vectorizer(words,true,false);

    words_out.open("output/test_all_words.txt",std::ios::out);
    words_out<<v.get_counter();
    for(int i=0;i<10;i++)
        words_out<<std::endl;
    words_out<<v.get_counter_different_comments();

    clean_out.open("output/test_all_words_less.txt",std::ios::out);
    print_map_sorted(clean_out,v.get_counter(),500,true);
    for(int i=0;i<10;i++)
        clean_out<<std::endl;
    print_map_sorted(clean_out,v.get_counter_different_comments(),500,true);

    return 0;
}
