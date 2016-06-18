#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"
#include "../utils/tfidf.hpp"
#include <iostream>
#include <array>
#include <fstream>
#include <cmath>

int main()
{
    std::fstream out;
    float sign;
    float shift_parameter=0.84;//intuitivement, cela signifie qu'on peut considérer qu'un mot est toxique à partir de ce seuil
    // avec power_parametre on étire les scores autour de shift_parameter;
    float power_parameter=1.9;//1.93 prédisait mieux sur nos données mais moins bien en submission
    float word_length_bonus=6;
    out.open("output/output.txt",std::fstream::out|std::fstream::trunc);
    std::vector<float> idf;
    std::vector<float> score;
    float meanidf=0,variance=0;
    //std::string word="http:";
    int size;
    Preprocessing p("../data/train.csv");
    p.save_in_file("output/modified.txt");
    Preprocessing p_test("../data/test.csv");

    auto words = p.get_words();
    auto words_test=p_test.get_words();

    Vectorizer v(words);
    std::vector<std::vector<int>> vect= v.get_vectorized();
    auto dico = v.get_dictionary();
    size=dico.size();
    idf.resize(size);
    score.resize(vect.size());
    std::vector<std::vector<int>> vect_test;
    std::vector<int> tmp;
    for(unsigned int i=0; i<words_test.size(); i++) //pour les données de test je vectorize moi même, en gardant seulement les mots qu'on avait dans le dico.
    {
        tmp.clear();
        tmp.push_back(1);//parce que la première valeur sera ignorée.
        for(unsigned int j=0; j<words_test[i].size(); j++)
        {
            if(dico.count(words_test[i][j])==1)
            tmp.push_back(dico.at(words_test[i][j]));
        }
        vect_test.push_back(tmp);
    }

    for(int i=0; i<size; i++)
    {
        idf[i] = idf_train(vect,i);
        if(!((i+1)%1000))
            std::cout << (float)i/(float)size<<'%'<<std::endl;
    }
    for(int i=0; i<size; i++)
    {
        meanidf += idf[i]/size;
    }
    for(int i=0; i<size; i++)
    {
        idf[i] = (idf[i]-meanidf);
    }
    for(int i=0; i<size; i++)
    {
        variance += (idf[i]*idf[i])/size;
    }
    for(int i=0; i<size; i++)
    {
        idf[i] /= sqrt(variance);
    }
    for(int i=0; i<size; i++)
    {
        idf[i]+= shift_parameter;
        sign=std::signbit(idf[i])?-1:1;
        idf[i]=fabs(idf[i]);
        idf[i] = sign*pow(idf[i],power_parameter); //je boost un peu la variance de sorte que le mots peu sgnificatif impacte moins.
    }
    for(unsigned j=0; j<vect.size(); j++)
    {
        score[j]=tfidf_trained(vect,j,idf,word_length_bonus);
        if(!((j+1)%10))
        std::cout << words[j][0]<<" : "<<score[j]<<std::endl;
    }

    int max_cool = 0;
    float best_f = 0, best_score = 0;
    for(float f=-1;f<1;f+=0.001)
    {
        int cool = 0;
        for(unsigned int j=0;j<score.size();j++)
            if(score[j]<f&&vect[j][0]==1)
                cool++;
            else if(score[j]>=f&&vect[j][0]!=1)
                cool++;
        if(cool>max_cool)
        {
            max_cool = cool;
            best_f = f;
            best_score = (float)cool/(float)score.size();
            //std::cout<<"New best : "<<f<<" "<<cool<<" "<<best_score<<std::endl;
        }
    }

    std::pair<float,float> t;
    //t = threshold(vect,score);
    t = std::pair<float,float>(best_f,best_score);
    std::cout << "seuil : "<<t.first<<" => score théorique :"<<t.second<<std::endl;
    for(unsigned j=0; j<vect_test.size(); j++)
    {
        score[j]=tfidf_trained(vect_test,j,idf,word_length_bonus);
    }
    score.resize(vect_test.size());

    for(unsigned j=0; j<score.size(); j++)
    {
        if(score[j]>=t.first)
        out<<"1\n";
        else
        out<<"0\n";
    }

    return 0;
}
