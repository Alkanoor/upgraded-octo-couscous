#include <fstream>

#include "vectorizer.hpp"


Vectorizer::Vectorizer(const std::vector<std::vector<std::string> >& words, bool update, bool train)
{
	reset_words(words, update, train);
}

void Vectorizer::reset_words(const std::vector<std::vector<std::string> >& words, bool update, bool train)
{
	this->words = words;
	if(update)
		vectorize(train);
}

void Vectorizer::vectorize(bool train)
{
    index.clear();
    index_to_words.clear();
    counter.clear();
    counter_different_comments.clear();
	insults_counter.clear();
	non_insults_counter.clear();

	n_insults = 0;

    for(unsigned int i=0;i<words.size();i++)
	{
		bool insult = false;
		if(words[i][0]=="1")
		{
			n_insults++;
			insult = true;
		}

        std::set<std::string> in_comment;
        for(unsigned int j=0;j<words[i].size();j++)
        {
            if(index.count(words[i][j]))
			{
			    if(!in_comment.count(words[i][j]))
                    counter_different_comments[words[i][j]]++;
			    counter[words[i][j]]++;
				if(insult&&train)
					insults_counter[words[i][j]]++;
				else if(train)
					non_insults_counter[words[i][j]]++;
			}
            else
			{
			    if(!in_comment.count(words[i][j]))
                    counter_different_comments[words[i][j]] = 1;
			    counter[words[i][j]] = 1;
                index[words[i][j]] = index.size();
                index_to_words[index[words[i][j]]] = words[i][j];
				if(insult&&train)
					insults_counter[words[i][j]] = 1;
				else if(train)
					non_insults_counter[words[i][j]] = 1;
			}
			in_comment.insert(words[i][j]);
        }
	}

    std::cout<<index.size()<<" words, "<<insults_counter.size()<<" insulting words, "<<non_insults_counter.size()<<" non insulting words"<<std::endl;

	vectorized.resize(words.size());
	int i=0;
	for(auto comment : words)
    {
        vectorized[i].resize(comment.size());
        int j=0;
        for(auto word : comment)
        {
            vectorized[i][j] = index[word];
            j++;
        }
		i++;
    }
}

const std::vector<std::vector<int> >& Vectorizer::get_vectorized() const
{return vectorized;}

const std::map<std::string,int>& Vectorizer::get_dictionary() const
{return index;}

const std::map<int,std::string>& Vectorizer::get_index_to_words() const
{return index_to_words;}

const std::map<std::string,int>& Vectorizer::get_counter() const
{return counter;}

const std::map<std::string,int>& Vectorizer::get_counter_different_comments() const
{return counter_different_comments;}

const std::map<std::string,int>& Vectorizer::get_insult_words() const
{return insults_counter;}

const std::map<std::string,int>& Vectorizer::get_non_insult_words() const
{return non_insults_counter;}

double Vectorizer::get_ratio_insults() const
{return (double)n_insults/(double)words.size();}

void Vectorizer::save_to_file(const std::string& path)
{
    save(vectorized,path);
}

void Vectorizer::load_from_file(const std::string& path)
{
    vectorized = load(path);
}

void Vectorizer::save(const std::vector<std::vector<int> >& vectorized, const std::string& path)
{
    std::ofstream ofs(path.c_str(),std::ios::out);
    for(unsigned int i=0;i<vectorized.size();i++)
    {
        ofs<<vectorized[i].size()<<" ";
        for(unsigned int j=0;j<vectorized[i].size();j++)
            ofs<<vectorized[i][j]<<" ";
        ofs<<std::endl;
    }
}

std::vector<std::vector<int> > Vectorizer::load(const std::string& path)
{
    std::vector<std::vector<int> > ret;

    std::ifstream ifs(path.c_str(),std::ios::in);
    int tmp;
    int cur_size, counter = -1;
    while(ifs>>tmp)
    {
        if(counter<0)
        {
            ret.push_back(std::vector<int>(tmp,0));
            cur_size = tmp-1;
            counter = tmp-1;
        }
        else
        {
            ret[ret.size()-1][cur_size-counter] = tmp;
            counter--;
        }
    }
    return ret;
}

double Vectorizer::score(double a, double b, double c, double d)
{return 1./((a+b+c)*(a+b+c))*std::min((a+d)*(a+d),(b+d)*(b+d));}
