#include "crossval.hpp"
#include "tfidf.hpp"
#include <algorithm>
#include <list>
#include <array>
#include <iostream>
std::pair<std::vector<std::vector<int>>,std::vector<std::vector<int>>> split(unsigned int n,std::vector<std::vector<int>> vect)
{
    std::vector<std::vector<int>> train,test;
    std::random_shuffle(vect.begin(),vect.end());
    if(n<=vect.size())
    {
        train=std::vector<std::vector<int>>(vect.begin(),vect.begin()+n);
        test=std::vector<std::vector<int>>(vect.begin()+n,vect.end());
    }
    else
    exit(0);
    return std::pair<std::vector<std::vector<int>>,std::vector<std::vector<int>>>(train,test);
}

std::vector<float> crossval_idf(std::vector<std::vector<int>> vect,int dictionnary_size,int n_sample, int n_trash,int sample_size)
{
    std::vector<std::vector<float>> idf;
    idf.resize(dictionnary_size);
    for(int j=0; j<dictionnary_size; j++)
    idf[j].resize(n_sample);
    std::vector<std::vector<int>> sample;
    std::vector<float> final_idf;
    final_idf.resize(dictionnary_size);
    for(int i=0; i<n_sample; i++)
    {
        std::cout << "Sample : "<<i+1<<"/"<<n_sample<<" --- "<<std::endl;
        if(sample_size==0)
        sample=vect;
        else
        sample=split(sample_size,vect).first;
        for(int j=0; j<dictionnary_size; j++)
        idf[j][i] = idf_train(sample,j);
    }
    for(int j=0; j<dictionnary_size; j++)
    std::sort(idf[j].begin(),idf[j].end());
    for(int j=0; j<dictionnary_size; j++)
    final_idf[j]=std::accumulate(idf[j].begin()+n_trash,idf[j].end()-n_trash,0);//pas besoin de moyenner ou quoi je le fait dans le main
    return final_idf;
}
