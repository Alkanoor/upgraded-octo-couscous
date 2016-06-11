#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"
#include "../utils/tfidf.hpp"
#include <iostream>
#include <array>

int main()
{
    std::vector<float> idf;
    std::vector<float> score;
    //std::string word="http:";
    int size;
    Preprocessing p("../data/train.csv");
    p.update_case();
    p.rescale_ascii();
    p.save_in_file("output/modified.txt");


    auto words = p.get_words();
    Vectorizer v(words);
    std::vector<std::vector<int>> vect= v.get_vectorized();
    auto dico = v.get_dictionary();
    size=dico.size();
    idf.resize(size);
    score.resize(vect.size());

    for(int i=0; i<size; i++)
    {
        idf[i] = idf_train(vect,i);
        //std::cout << (float)i/(float)size<<'%'<<std::endl;
    }
    for(unsigned j=0; j<vect.size(); j++)
    {
        score[j]=tfidf_trained(vect,j,idf);
        //std::cout << words[j][0]<<" : "<<score[j]<<std::endl;
    }
    auto t=threshold(vect,score);
    std::cout << "seuil : "<<t.first<<" => score théorique :"<<t.second<<std::endl;
    return 0;
    }
