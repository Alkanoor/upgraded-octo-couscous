#include "tfidf.hpp"
#include <cmath>
#include<iostream>

float tf(std::vector<std::vector<int>> in, int comm, int word)
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
float idf(std::vector<std::vector<int>> in, int word)
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

float idf_train(std::vector<std::vector<int>> in, int word)
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


float tfidf(std::vector<std::vector<int>> in, int comm, int word)
{
    float tfidf=tf(in,comm,word)*idf(in,word);
    return tfidf;
}

float tfidf_trained(std::vector<std::vector<int>> in, int comm,std::vector<float> idf)
{
    float tfidf=0;
    for(unsigned int i=1; i<in[comm].size(); i++)
    tfidf+=idf[in[comm][i]];
    return tfidf/(float)in[comm].size();
}
