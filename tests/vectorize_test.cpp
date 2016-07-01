#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"

#include <iostream>
#include <fstream>
#include <array>
#include <ctime>


int main()
{
    int a = time(NULL), b;
    Preprocessing p("../data/train.csv");
    b = time(NULL);
    std::cout<<"Preprocessing : "<<b-a<<std::endl;
    p.save_in_file("output/train_modified.txt");

    auto words = p.get_words();
    auto words_before = p.get_words_before_regex();
    auto regexed = p.get_regexed();

    a = b;
    Vectorizer v(words);
    b = time(NULL);
    std::cout<<"Vectorizer : "<<b-a<<std::endl;

    std::ofstream after_regexing("output/train_after_regexing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        for(unsigned int j=0;j<words[i].size();j++)
            after_regexing<<words[i][j]<<" ";
        after_regexing<<std::endl;
    }
    after_regexing.close();

    std::cout<<v.get_ratio_insults()<<std::endl;

    /*std::ofstream words_out("output/train_all_words.txt",std::ios::out);
    words_out<<v.get_counter();
    for(int i=0;i<10;i++)
        words_out<<std::endl;
    words_out<<v.get_counter_different_comments();
    words_out.close();*/

    std::ofstream words_out("output/train_before_after_regexing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        words_out<<"========================================================"<<std::endl;
        for(unsigned int j=0;j<words_before[i].size();j++)
            words_out<<words_before[i][j]<<" ";
        for(unsigned int j=0;j<regexed[i].size();j++)
            words_out<<regexed[i][j].first<<";"<<regexed[i][j].second<<" ";
        words_out<<std::endl;
        for(unsigned int j=0;j<words[i].size();j++)
            words_out<<words[i][j]<<" ";
        words_out<<std::endl;
    }
    words_out.close();

    std::ofstream clean_out("output/train_all_words_less.txt",std::ios::out);
    print_map_sorted(clean_out,v.get_counter(),500,true);
    for(int i=0;i<10;i++)
        clean_out<<std::endl;
    print_map_sorted(clean_out,v.get_counter_different_comments(),500,true);
    clean_out.close();

    a = b;
    Preprocessing p2("../data/test.csv");
    b = time(NULL);
    std::cout<<"Preprocessing : "<<b-a<<std::endl;
    p2.save_in_file("output/test_modified.txt");

    words = p2.get_words();
    words_before = p2.get_words_before_regex();
    regexed = p2.get_regexed();
    a = b;
    v = Vectorizer(words,true,false);
    b = time(NULL);
    std::cout<<"Vectorizer : "<<b-a<<std::endl;

    after_regexing.open("output/test_after_regexing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        for(unsigned int j=0;j<words[i].size();j++)
            after_regexing<<words[i][j]<<" ";
        after_regexing<<std::endl;
    }

    /*words_out.open("output/test_all_words.txt",std::ios::out);
    words_out<<v.get_counter();
    for(int i=0;i<10;i++)
        words_out<<std::endl;
    words_out<<v.get_counter_different_comments();*/

    words_out.open("output/test_before_after_regexing.txt",std::ios::out);
    for(unsigned int i=0;i<words.size();i++)
    {
        words_out<<"========================================================"<<std::endl;
        for(unsigned int j=0;j<words_before[i].size();j++)
            words_out<<words_before[i][j]<<" ";
        for(unsigned int j=0;j<regexed[i].size();j++)
            words_out<<regexed[i][j].first<<";"<<regexed[i][j].second<<" ";
        words_out<<std::endl;
        for(unsigned int j=0;j<words[i].size();j++)
            words_out<<words[i][j]<<" ";
        words_out<<std::endl;
    }

    clean_out.open("output/test_all_words_less.txt",std::ios::out);
    print_map_sorted(clean_out,v.get_counter(),500,true);
    for(int i=0;i<10;i++)
        clean_out<<std::endl;
    print_map_sorted(clean_out,v.get_counter_different_comments(),500,true);

    return 0;
}
