#include "tfidf.hpp"
#include <cmath>
#include <list>
#include <utility>
#include<iostream>



float idf_train(const std::vector<std::vector<int>>& in, int word)
{
    int d0=1;
    int d1=1;
    int ones=1,zeros=1;
    for (unsigned int i = 0; i<in.size(); i++)
    {
        if(in[i][0]==1)
        zeros++;
        else
        ones++;
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
    return log((float)(d1*zeros)/(float)(d0*ones));
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
