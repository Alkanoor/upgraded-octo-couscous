#include "counts.hpp"

#include <map>
#include <set>


int min(int a,int b)
{
   return a<=b ? a:b ;
}

unsigned int split(const std::string &strToSplit, std::vector<std::string> &splited, char c)
{
    unsigned int index = 0;
    for (unsigned int i=0;i<strToSplit.size();i++)
    {
    	if(strToSplit[i]==c)
    	{
    		splited.push_back(strToSplit.substr(index, i-index+1));
    		index = i+1;
    	}
    	else if (i==strToSplit.size()-1)
    	{
        	splited.push_back(strToSplit.substr(index, i-index+1));
        	return splited.size();
    	}
    }
    return splited.size();

}

void numberCapitalsPonctuation(const std::string &str, unsigned int &capitals, unsigned int &ponctuation, unsigned int &other)
{
    other=0;
	capitals=0;
	ponctuation=0;

	for (unsigned int index = 0;index<str.size();index++)
	{
		if(str[index]=='!') ponctuation++;
		else if(str[index]>='A' && str[index]<='Z') capitals ++;
		else other++;
	}

}
