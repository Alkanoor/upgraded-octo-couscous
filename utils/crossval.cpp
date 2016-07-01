#include "crossval.hpp"
#include "tfidf.hpp"
#include <algorithm>
#include <list>
#include <array>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <random>
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
    std::vector<float> idf_tmp;
    idf.resize(dictionnary_size);
    for(int j=0; j<dictionnary_size; j++)
    idf[j].resize(n_sample);
    std::vector<std::vector<int>> sample;
    std::vector<float> final_idf;
    final_idf.resize(dictionnary_size);
    for(int i=0; i<n_sample; i++)
    {
        if(sample_size==0)
        sample=vect;
        else
        sample=bootstrap(sample_size,vect);
        idf_tmp=idf_train(sample,dictionnary_size);
        for(int j=0; j<dictionnary_size; j++)
        idf[j][i] = idf_tmp[j];
    }
    for(int j=0; j<dictionnary_size; j++)
    std::sort(idf[j].begin(),idf[j].end());
    for(int j=0; j<dictionnary_size; j++)
    for(int i=0; i<n_sample; i++)
    final_idf[j]+=idf[j][i];//std::accumulate(idf[j].begin()+n_trash,idf[j].end()-n_trash,0);//pas besoin de moyenner ou quoi je le fait dans le main
    return final_idf;
}

std::vector<std::vector<int>> bootstrap(int n,std::vector<std::vector<int>>& vect)
{
    std::vector<std::vector<int>> ret;
    int max=vect.size();
    std::srand(time(NULL));
    std::mt19937_64 rng=std::mt19937_64(time(NULL));
    int index;
    ret.resize(n);
    for(int i=0; i<n; i++)
    {
        index=rng()%max;
        ret[i]=vect[index];
    }
    return ret;
}

float bagging(int dico_size,std::vector<std::vector<int>>train,std::vector<std::vector<int>>test,float sample_size,float trash_size,float shift_parameter, float power_parameter, float word_length_bonus,int n_sample)
{
    std::vector<float> idf=crossval_idf(train,dico_size,n_sample,trash_size,sample_size);
    float meanidf=0,variance=0;
    float sign;
    std::vector<float>score;
    score.resize(test.size());
    for(int i=0; i<dico_size; i++)
    {
        meanidf += idf[i]/(float)dico_size;
    }
    for(int i=0; i<dico_size; i++)
    {
        idf[i] = (idf[i]-meanidf);
    }
    for(int i=0; i<dico_size; i++)
    {
        variance += (idf[i]*idf[i])/(float)dico_size;
    }
    for(int i=0; i<dico_size; i++)
    {
        idf[i] /= sqrt(variance);
    }
    for(int i=0; i<dico_size; i++)
    {
        idf[i]+= shift_parameter;
        sign=std::signbit(idf[i])?-1:1;
        idf[i]=fabs(idf[i]);
        idf[i] = sign*pow(idf[i],power_parameter); //je boost un peu la variance de sorte que le mots peu sgnificatif impacte moins.
    }
    for(unsigned j=0; j<test.size(); j++)
    {
        score[j]=tfidf_trained(test,j,idf,word_length_bonus);
        //if(!((j+1)%10))
        //std::cout << vect_test[j][0]<<" : "<<score[j]<<std::endl;
    }

    int max_cool = 0;
    float best_f = 0, best_score = 0;
    for(float f=-2;f<4;f+=0.001)
    {
        int cool = 0;
        for(unsigned int j=0;j<test.size();j++)
            if(score[j]<f&&test[j][0]==1)
                cool++;
            else if(score[j]>=f&&test[j][0]!=1)
                cool++;
        if(cool>max_cool)
        {
            max_cool = cool;
            best_f = f;
            best_score = (float)cool/(float)test.size();
            //std::cout<<"New best : "<<f<<" "<<cool<<" "<<best_score<<std::endl;
        }
    }
    if(best_f==0)
    {
        score.resize(train.size());
        for(unsigned j=0; j<train.size(); j++)
        {
            score[j]=tfidf_trained(train,j,idf,word_length_bonus);
        }
        for(float f=-3;f<3;f+=0.001)
        {
            int cool = 0;
            for(unsigned int j=0;j<train.size();j++)
                if(score[j]<f&&train[j][0]==1)
                    cool++;
                else if(score[j]>=f&&train[j][0]!=1)
                    cool++;
            if(cool>max_cool)
            {
                max_cool = cool;
                best_f = f;
                best_score = (float)cool/(float)train.size();
            }
        }
    }
    return best_score;
}
float cross_validation(int dico_size,int n_fold,std::vector<std::vector<int>>train,std::vector<std::vector<int>>test,float sample_size,float trash_size,float shift_parameter, float power_paramater, float word_length_bonus,int n_sample)
{
    float score=0;
    for(int i=0;i<n_fold; i++)
    {
        score+=bagging(dico_size,train,test,sample_size, trash_size, shift_parameter, power_paramater, word_length_bonus,n_sample);
    }
    return score/(float)n_fold;
}
