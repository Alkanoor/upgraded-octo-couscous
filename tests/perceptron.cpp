#include "../utils/preprocessing.hpp"
#include "../utils/vectorizer.hpp"
#include "../utils/util.hpp"
#include "../utils/tfidf.hpp"
#include <iostream>
#include <array>
#include <fstream>
#include <cmath>


void normalize(std::vector<float>& idf)
{
    float meanidf=0, variance=0;
    int size=idf.size();
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
}
int main()
{
    int max_cool = 0;
    float best_f = 0, best_score = 0,perceptron_score=0;
    std::pair<float,float> t;
    std::fstream out;
    out.open("output/output.txt",std::fstream::out|std::fstream::trunc);
    std::vector<float> score;
    float word_length_bonus=6,err;
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
    std::vector<float> idf;
    std::vector<float> idf_learn,best_idf;
    std::vector<int> test_presence(size,0);
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
            {
                tmp.push_back(dico.at(words_test[i][j]));
                test_presence[dico.at(words_test[i][j])]++;
            }
        }
        vect_test.push_back(tmp);
    }
    for(int j=0; j<size;j++)
    if(test_presence[j]<2)
    test_presence[j]=0;
    else
    test_presence[j]=1;
    int max_iter=200; //nombre maximum d'itération sans changer de score.
    idf=idf_train(vect,size);
    normalize(idf);
    for(int i=0; i<size; i++)
    {
        idf[i]+= 0.84;
        float sign=std::signbit(idf[i])?-1:1;
        idf[i]=fabs(idf[i]);
        idf[i] = sign*pow(idf[i],1.9); //je boost un peu la variance de sorte que le mots peu sgnificatif impacte moins.
    }
    normalize(idf);
    for(int i=0; i<max_iter&&perceptron_score<0.9; i++)
    {
        idf_learn=idf;
        for(unsigned int j=0; j<vect.size();j++)
        {
            score[j]=tfidf_trained(vect,j,idf,word_length_bonus);
            if(vect[j][0]==1 && score[j]>0.5)
            {
                err=(0.5-score[j])/(float)vect[j].size();
                for(unsigned int k=1; k<vect[j].size(); k++)
                idf_learn[vect[j][k]]+=0.01*err/(1-best_score);
            }
            else if(vect[j][0]!=1 && score[j]<0.7)
            {
                err=(0.7-score[j])/(float)vect[j].size();
                for(unsigned int k=1; k<vect[j].size(); k++)
                idf_learn[vect[j][k]]+=0.01*err/(1-best_score);
            }
        }
        idf=idf_learn;
        for(int j=0; j<size;j++)
        idf[j]*=test_presence[j];
        normalize(idf);
        for(unsigned int j=0; j<vect.size();j++)
        {
            score[j]=tfidf_trained(vect,j,idf,word_length_bonus);
        }
        max_cool=0;
        for(float f=-1;f<1;f+=0.001)
        {
            int cool = 0;
            for(unsigned int j=0;j<score.size();j++)
                if(score[j]<f&&vect[j][0]==1)
                    cool++;
                else if(score[j]>=f&&vect[j][0]!=1)
                    cool++;
            if(cool>max_cool )
            {
                max_cool = cool;
                best_f = f;
                best_score = (float)cool/(float)score.size();
                //std::cout<<"New best : "<<f<<" "<<cool<<" "<<best_score<<std::endl;
            }
        }
        if(best_score>perceptron_score)
        {
            i=0;
            perceptron_score=best_score;
            best_idf=idf;
        }
        t = std::pair<float,float>(best_f,best_score);
        std::cout<<"score théorique :"<<perceptron_score<<std::endl;
    }
    for(unsigned int j=0; j<vect.size();j++)
    {
        score[j]=tfidf_trained(vect,j,best_idf,word_length_bonus);
    }
    max_cool=0;
    for(float f=-1;f<1;f+=0.001)
    {
        int cool = 0;
        for(unsigned int j=0;j<score.size();j++)
            if(score[j]<f&&vect[j][0]==1)
                cool++;
            else if(score[j]>=f&&vect[j][0]!=1)
                cool++;
        if(cool>max_cool )
        {
            max_cool = cool;
            best_f = f;
            best_score = (float)cool/(float)score.size();
            //std::cout<<"New best : "<<f<<" "<<cool<<" "<<best_score<<std::endl;
        }
    }
    t = std::pair<float,float>(best_f,best_score);
    std::cout << "seuil : "<<t.first<<" => score théorique :"<<t.second<<std::endl;
    //score.resize(vect.size());
    score.resize(vect_test.size());
    for(unsigned j=0; j<vect_test.size(); j++)
    {
        score[j]=tfidf_trained(vect_test,j,best_idf,word_length_bonus);
    }

    for(unsigned j=0; j<score.size(); j++)
    {
        if(score[j]>=t.first)
        out<<"1\n";
        else
        out<<"0\n";
    }
    return 0;
}
