#include <iostream>
#include <cmath>
#include <map>

#include "learner.hpp"


Learner::Learner(int n_iter_for_threshold, float ratio, float a, float b, float k, float delta) :
    n_iter(n_iter_for_threshold),
    ratio(ratio),
    a(a),
    b(b),
    k(k),
    delta(delta)
{}

void Learner::fit()
{
    compute_idf();

    avg = 0;
    for(unsigned int i=0;i<train_words.size();i++)
        avg += (float)train_words[i].size()/(float)train_words.size();

    std::cout<<"Average length : "<<avg<<std::endl;

    scores.resize(train_words.size());
    float score_min = 0, score_max = 0;
    for(unsigned int i=0;i<train_words.size();i++)
    {
        scores[i] = score_tfidf(train_words[i]);
        if(!i)
        {
            score_min = scores[i];
            score_max = scores[i];
        }
        else if(scores[i]>score_max)
            score_max = scores[i];
        else if(scores[i]<score_min)
            score_min = scores[i];
    }
    std::cout<<(score_max-score_min)/(float)n_iter<<" "<<scores.size()<<std::endl;

    int max_cool = 0;
    float best_f = 0, best_score = 0;
    for(float f=score_min;f<=score_max;f+=(score_max-score_min)/(float)n_iter)
    {
        int cool = 0;
        for(unsigned int j=0;j<scores.size();j++)
            if(scores[j]<f&&train_target[j]==1)
                cool++;
            else if(scores[j]>=f&&train_target[j]!=1)
                cool++;
        if(cool>max_cool)
        {
            max_cool = cool;
            best_f = f;
            best_score = (float)cool/(float)scores.size();
        }
    }

    threshold = best_f;
    std::cout<<"Inside fitting, best score is "<<best_score<<std::endl;
}

void Learner::predict()
{
    predicted.resize(test_words.size());
    for(unsigned int i=0;i<predicted.size();i++)
        predicted[i] = (score_tfidf(test_words[i])>threshold);
}

float Learner::score(const std::vector<int>& classified, const std::vector<int>& ref)
{
    float score = 0;
    for(unsigned int i=0;i<classified.size();i++)
        if(classified[i]==ref[i])
            score++;
    return score/(float)classified.size();
}

void Learner::set_train_words(const std::vector<std::vector<int> >& vectorized)
{train_words = vectorized;}

void Learner::set_test_words(const std::vector<std::vector<int> >& vectorized)
{test_words = vectorized;}

float Learner::partial_cross_val(const std::vector<std::vector<int> >& vectorized, const std::vector<int>& target, float test_ratio, float cur_fold)
{
    train_words.clear();
    test_words.clear();
    train_target.clear();
    test_target.clear();

    if(vectorized.size()!=target.size())
    {
        std::cerr<<"Sizes don't match for cross val"<<std::endl;
        return -1;
    }

    int l = test_ratio*vectorized.size();
    int o = cur_fold*vectorized.size();
    for(int i=0;i<(int)vectorized.size();i++)
        if(i<l)
        {
            test_words.push_back(vectorized[(i+o)%vectorized.size()]);
            test_target.push_back(target[(i+o)%vectorized.size()]);
        }
        else
        {
            train_words.push_back(vectorized[(i+o)%vectorized.size()]);
            train_target.push_back(target[(i+o)%vectorized.size()]);
        }

    fit();     //on train_words
    predict(); //on test_words
    return score(predicted,test_target);
}

std::vector<float> Learner::cross_val(const std::vector<std::vector<int> >& vectorized, const std::vector<int>& target, float ratio)
{
    std::vector<float> scores;
    for(float i=0;i<1;i+=ratio)
        scores.push_back(partial_cross_val(vectorized,target,ratio,i));
    return scores;
}

void Learner::compute_idf()
{
    int max = 0;
    for(unsigned int i=0;i<train_words.size();i++)
        for(unsigned int j=0;j<train_words[i].size();j++)
            if(train_words[i][j]>max)
                max = train_words[i][j];

    idf.resize(max+1);
    counter_positive.resize(max+1);
    counter_negative.resize(max+1);

    for(int i=0;i<max+1;i++)
    {
        counter_positive[i] = 0;
        counter_negative[i] = 0;
    }

    for(unsigned int i=0;i<train_words.size();i++)
        for(unsigned int j=0;j<train_words[i].size();j++)
        {
            if(train_target[i]==1)
                counter_positive[train_words[i][j]]++;
            else
                counter_negative[train_words[i][j]]++;
        }

    for(int i=0;i<max+1;i++)
    {
        float tmp = log(a+counter_positive[i]+counter_negative[i]);
        if(tmp<=1)
            idf[i] = 0;
        else
            idf[i] = log((ratio*counter_positive[i]+a)/((1-ratio)*counter_negative[i]+a))*log(tmp);
    }

    for(int i=0;i<max+1;i++)
        idf[i] = log((counter_positive[i]+0.5)/(counter_negative[i]+0.5));
}

float Learner::score_tfidf(const std::vector<int>& v)
{
    float score = 0;
    std::map<int,float> freqs;
    for(unsigned int j=0;j<v.size();j++)
        if(!freqs.count(v[j]))
            freqs[v[j]] = 1./(float)(v.size());
        else
            freqs[v[j]] += 1./(float)(v.size());

    /*for(auto it : freqs)
        score += idf[it.first]*(((it.second*(k+1))/(it.second+k*(1-b+b*(float)v.size()/avg)))+delta);*/

    for(auto it : freqs)
        score += idf[it.first]*it.second;

    return score;
}
