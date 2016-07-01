#include "tfidf.hpp"
#include <cmath>
#include <list>
#include <utility>
#include<iostream>



std::vector<float> idf_train(const std::vector<std::vector<int>>& in,int dico_size)
{
    std::vector<float> idf;
    idf.resize(dico_size);
    std::vector<int> d0(dico_size,1);
    std::vector<int> d1(dico_size,1);
    int ones=1,zeros=1;
    for (unsigned int i = 0; i<in.size(); i++)
    {
        if(in[i][0]==1)
        zeros++;
        else
        ones++;
        for(unsigned int j = 0; j<in[i].size(); j++)
        {
            if(in[i][0]==1)
            d0[in[i][j]]++;
            else
            d1[in[i][j]]++;
        }
    }
    for(int j = 0; j<dico_size; j++)
    {
        idf[j]=log((float)(d1[j]*zeros)/(float)(d0[j]*ones));
    }
    return idf;
}

float tfidf_trained(const std::vector<std::vector<int>>& in, int comm,const std::vector<float>& idf,float word_length_bonus)
{
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
