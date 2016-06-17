#include "tfidf.hpp"
#include <cmath>
#include <list>
#include <utility>
#include<iostream>

float tf(const std::vector<std::vector<int>>& in, int comm, int word)
{
    float total=(float)in[comm].size();
    float word_count=0.0;
    for(unsigned int i=0; i<in[comm].size(); i++)
    {
        if(in[comm][i]==word)
        word_count+=1;
    }
    return word_count/total;
}
//dans la tfidf classique, ça représente la rareté d'un mot dans le corpus,
//la ça va être la rareté d'un mot dans les bons commentaires
float idf(const std::vector<std::vector<int>>& in, int word)
{
    int d=in.size();
    int d_word=0;
    for (int i = 0; i<d; i++)
    {
        for(unsigned int j = 0; j<in[i].size(); j++)
        {
            if(in[i][j]==word )
            {
                d_word++;
                break;
            }
        }
    }
    return log((float)d/(float)d_word);
}

float idf_train(const std::vector<std::vector<int>>& in, int word)
{
    int d0=1;
    int d1=1;
    for (unsigned int i = 0; i<in.size(); i++)
    {
        for(unsigned int j = 0; j<in[i].size(); j++)
        {
            if(in[i][j]==word){
                if(in[i][0]==1)
                d0++;
                else
                d1++;
            }
        }
    }
    return log((float)d1/(float)d0);
}


float tfidf(const std::vector<std::vector<int>>& in, int comm, int word)
{
    float tfidf=tf(in,comm,word)*idf(in,word);
    return tfidf;
}

float tfidf_trained(const std::vector<std::vector<int>>& in, int comm,const std::vector<float>& idf)
{
    float word_length_bonus=6;
    float tfidf=0;
    for(unsigned int i=1; i<in[comm].size(); i++)
    tfidf+=idf[in[comm][i]];
    return tfidf/(float)(in[comm].size()+word_length_bonus); //rend les commentaires plus long plus toxics.
}

bool comp(std::pair<int,float>a,std::pair<int,float>b)
{
    return a.second<b.second;
}
bool comp2(std::pair<float,float>a,std::pair<float,float>b)
{
    return a.second>b.second;
}
std::pair<float,float> threshold(const std::vector<std::vector<int>>& in, const std::vector<float>& tfidf_score)
{
    std::cout.flush();
    int nb_onesR=0,nb_zerosL=0,nb_zerosR=0, nb_onesL=0, total=0;
    std::list<std::pair<float,float>>score;
    std::list<std::pair<int,float>> result;
    for(unsigned int i=0; i<tfidf_score.size(); i++)
    {
        result.push_back(std::pair<int,float>(in[i][0],tfidf_score[i]));
        if(in[i][0]==1)
        nb_zerosR++;
        else
        nb_onesR++;
    }
    total=nb_zerosR+nb_onesR;
    result.sort(comp);
    for(auto i=result.begin(); i!=result.end(); i++)
    {
        if((*i).first==225)
        {
            nb_onesL++;
            nb_onesR--;
        }
        else
        {
            nb_zerosL++;
            nb_zerosR--;
        }
        score.push_back(std::pair<float,float>((*i).second,1-(float)(nb_onesL+nb_zerosR)/total));
    }
    score.sort(comp2);

    return *score.begin();
}
