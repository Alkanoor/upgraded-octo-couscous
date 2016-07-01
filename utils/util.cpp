#include <fstream>

#include "util.hpp"


bool read(const std::string& path, std::vector<unsigned char>& ret)
{
    std::ifstream ifs(path.c_str(),std::ios::in|std::ios::binary);
    if(!ifs)
        return false;
    ifs.seekg(0,std::ios::end);
    unsigned int size = ifs.tellg();
    ret.resize(size);
    ifs.seekg(0,std::ios::beg);
    ifs.read((char*)&(ret[0]),size);
    return true;
}

void split_and_count(const std::vector<unsigned char>& in, unsigned int& maxSize, unsigned int& nbLines, const std::set<unsigned char>& separators)
{
    unsigned int s=in.size();
    unsigned int curSize = 0;
    maxSize = 0;
    nbLines = 0;
    for(unsigned int i=0;i<s;i++)
        if(separators.count(in[i]))
        {
            if(curSize)
            {
                if(curSize>maxSize)
                    maxSize = curSize;
                nbLines++;
            }
            curSize = 0;
        }
        else
            curSize++;

    if(curSize)
    {
        if(curSize>maxSize)
            maxSize = curSize;
        nbLines++;
    }
}

unsigned int load_in_vec(const std::vector<unsigned char>& in, std::vector<std::vector<unsigned char> >& ret, unsigned char separator)
{
    unsigned int s=in.size();
    unsigned int maxSize = 0, nbLines = 0;
    std::set<unsigned char> separators;
    separators.insert(separator);
    split_and_count(in,maxSize,nbLines,separators);

    ret.resize(nbLines);
    unsigned int j=0,k=0;
    std::vector<unsigned char> tmp(maxSize);
    for(unsigned int i=0;i<s;i++)
    {
        if(in[i]==separator&&k>0)
        {
            ret[j] = tmp;
            ret[j].resize(k);
            k=0;
            j++;
        }
        else if(in[i]!=separator)
        {
            tmp[k] = in[i];
            k++;
        }
    }
    if(k)
    {
        ret[j] = tmp;
        ret[j].resize(k);
        j++;
    }
    ret.resize(j);

    return nbLines;
}

unsigned int load_in_string(const std::vector<unsigned char>& in, std::vector<std::string>& ret, const std::set<unsigned char>& separators)
{
    unsigned int s=in.size();
    unsigned int maxSize = 0, nbLines = 0;
    split_and_count(in,maxSize,nbLines,separators);

    ret.resize(nbLines);
    unsigned int j=0,k=0;
    std::string tmp;
    tmp.resize(maxSize);
    for(unsigned int i=0;i<s;i++)
    {
        if(separators.count(in[i])&&k>0)
        {
            ret[j] = tmp;
            ret[j].resize(k);
            k=0;
            j++;
        }
        else if(!separators.count(in[i]))
        {
            tmp[k] = in[i];
            k++;
        }
    }
    if(k)
    {
        ret[j] = tmp;
        ret[j].resize(k);
        j++;
    }
    ret.resize(j);

    return nbLines;
}

unsigned int load_in_string(const std::vector<unsigned char>& in, std::vector<std::string>& ret, unsigned char separator)
{
    std::set<unsigned char> tmp;
    tmp.insert(separator);
    return load_in_string(in,ret,tmp);
}

unsigned int replace_seq_by(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::map<std::string,unsigned char,std::greater<std::string>>& separators_replacement, int max_occur)
{
    //TODO : optimiser la recherche de sous occurences (non critique)
    unsigned int n_occur = 0, cur = 0;
    unsigned char corresp;
    ret.resize(in.size());
    for(unsigned int i=0;i<in.size();i++)
    {
        int found = -1;
        for(std::map<std::string,unsigned char>::const_iterator it=separators_replacement.begin();it!=separators_replacement.end();it++)
        {
            unsigned int j=0;
            for(;j<it->first.size()&&i+j<in.size()&&in[i+j]==it->first[j];j++)
                ;
            if(j>=it->first.size())
            {
                found = it->first.size();
                corresp = it->second;
                break;
            }
        }

        if(found<=0||(max_occur>0&&(int)n_occur>=max_occur))
            ret[cur] = in[i];
        else
        {
            ret[cur] = corresp;
            i += found-1;
            n_occur++;
        }
        cur++;
    }
    ret.resize(cur);

    return n_occur;
}

unsigned int replace_seq_by(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::string& separator, unsigned char to_replace_by, int max_occur)
{
    std::map<std::string, unsigned char, std::greater<std::string> > tmp;
    tmp[separator] = to_replace_by;
    return replace_seq_by(in,ret,tmp,max_occur);
}

unsigned int replace_seq_by_string(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::map<std::string,std::string,std::greater<std::string> >& separators_replacement, int max_occur)
{
    //TODO : optimiser la recherche de sous occurences (non critique)
    unsigned int n_occur = 0, cur = 0;
    std::string corresp;
    ret.resize(in.size());
    for(unsigned int i=0;i<in.size();i++)
    {
        int found = -1;
        for(std::map<std::string,std::string>::const_iterator it=separators_replacement.begin();it!=separators_replacement.end();it++)
        {
            unsigned int j=0;
            for(;j<it->first.size()&&i+j<in.size()&&in[i+j]==it->first[j];j++)
                ;
            if(j>=it->first.size())
            {
                found = it->first.size();
                corresp = it->second;
                break;
            }
        }

        if(found<=0||(max_occur>0&&(int)n_occur>=max_occur))
        {
            ret[cur] = in[i];
            cur++;
        }
        else
        {
            ret.resize(ret.size()+corresp.size());
            for(unsigned int j=0;j<corresp.size();j++)
                ret[cur+j] = corresp[j];
            cur += (int)corresp.size();
            i += found-1;
            n_occur++;
        }
    }
    ret.resize(cur);

    return n_occur;
}

unsigned int replace_seq_by_string(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::string& separator, const std::string& to_replace_by, int max_occur)
{
    std::map<std::string, std::string, std::greater<std::string> > tmp;
    tmp[separator] = to_replace_by;
    return replace_seq_by_string(in,ret,tmp,max_occur);
}
