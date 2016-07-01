#include "../utils/preprocessing.hpp"
#include "../utils/counts.hpp"
#include "../utils/util.hpp"

#include <iostream>
#include <array>


std::pair<std::array<int,4>,std::string> convert_comment(const std::vector<std::string>& comment)
{
    std::array<int,4> final;
    std::string final_string;

    for(unsigned int i=0;i<4;i++)
        final[i] = 0;

    if(comment[0]=="1")
        final[0] = 1;
    else
        final[0] = 0;
    unsigned int t1, t2, t3;
    for(auto c : comment)
    {
        final_string += c+" ";
        numberCapitalsPonctuation(c,t1,t2,t3);
        final[1] += t1;
        final[2] += t2;
        final[3] += t3;
    }

    return std::pair<std::array<int,4>,std::string>(final,final_string);
}

int main()
{
    Preprocessing p("../data/train.csv");

    std::vector<std::vector<std::string> > words = p.get_words();
    words.resize(30);

    for(auto w : words)
    {
        std::cout<<"New comment :"<<std::endl;
        std::cout<<w<<std::endl;
    }

    std::function<std::pair<std::array<int,4>,std::string>(const std::vector<std::string>& comment)> test = std::bind(convert_comment,std::placeholders::_1);
    std::vector<std::pair<std::array<int,4>,std::string> > converted = p.apply(test);
    for(auto a : converted)
        std::cout<<a.first[0]<<" => "<<a.second<<std::endl<<"Gives "<<a.first[1]<<" "<<a.first[2]<<" "<<a.first[3]<<std::endl;

    return 0;
}
