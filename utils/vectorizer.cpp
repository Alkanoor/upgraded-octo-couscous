#include "vectorizer.hpp"


Vectorizer::Vectorizer(const std::vector<std::vector<std::string> >& words, bool update, double a, double b) :
	a(a),
	b(b)
{
	reset_words(words, update);
}

void Vectorizer::reset_words(const std::vector<std::vector<std::string> >& words, bool update)
{
	this->words = words;
	if(update)
		vectorize();
}

#include <iostream>
void Vectorizer::vectorize()
{
    counter.clear();
	insults_counter.clear();
	non_insults_counter.clear();
	scores.clear();

	n_insults = 0;

    for(unsigned int i=0;i<words.size();i++)
	{
		bool insult = false;
		if(words[i][0]=="1")
		{
			n_insults++;
			insult = true;
		}

        for(unsigned int j=0;j<words[i].size();j++)
            if(counter.count(words[i][j]))
			{
				if(insult)
					insults_counter[words[i][j]]++;
				else
					non_insults_counter[words[i][j]]++;
			}
            else
			{
                counter[words[i][j]] = counter.size();
				if(insult)
					insults_counter[words[i][j]] = 1;
				else
					non_insults_counter[words[i][j]] = 1;
			}
	}

    std::cout<<counter.size()<<" "<<insults_counter.size()<<" "<<non_insults_counter.size()<<std::endl;
	for(auto it=counter.begin(); it!=counter.end(); it++)
	{
		double m1=0, m2=0;
		if(insults_counter.count(it->first))
			m1 = (double)insults_counter[it->first]/(double)n_insults;
		if(non_insults_counter.count(it->first))
			m2 = (double)non_insults_counter[it->first]/(double)(words.size()-n_insults);
		scores[it->first] = score(m1,m2,a,b);
		if(scores[it->first]<0.1)
            std::cout<<"OHOHOHO "<<scores[it->first]<<" "<<it->first<<" => "<<insults_counter[it->first]<<" "<<non_insults_counter[it->first]<<std::endl;
	}
	std::cout<<scores.size()<<std::endl;

	vectorized.resize(words.size());
	int i=0;
	for(auto comment : words)
    {
        vectorized[i].resize(comment.size());
        int j=0;
        for(auto word : comment)
        {
            vectorized[i][j] = counter[word];
            j++;
        }
        i++;
    }
}

const std::vector<std::vector<int> >& Vectorizer::get_vectorized() const
{return vectorized;}

const std::map<std::string,int>& Vectorizer::get_dictionary() const
{return counter;}

const std::map<std::string,int>& Vectorizer::get_insult_words() const
{return insults_counter;}

const std::map<std::string,int>& Vectorizer::get_non_insult_words() const
{return non_insults_counter;}

const std::map<std::string,double>& Vectorizer::get_scores() const
{return scores;}

double Vectorizer::get_ratio_insults() const
{return (double)n_insults/(double)words.size();}

double Vectorizer::score(double a, double b, double c, double d)
{return 1./((a+b+c)*(a+b+c))*std::min((a+d)*(a+d),(b+d)*(b+d));}

