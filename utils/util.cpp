#include <fstream>

#include "util.hpp"


bool read(const std::string& path, std::vector<unsigned char>& ret)
{
    std::ifstream ifs(path.c_str(),std::ios::in);
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
        nbLines++;
        if(curSize>maxSize)
        maxSize = curSize;
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

unsigned int loadInVec(const std::vector<unsigned char>& in, std::vector<std::vector<unsigned char> >& ret, unsigned char separator)
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
        if(in[i]==separator)
        {
            ret[j] = tmp;
            ret[j].resize(k);
            k=0;
            j++;
        }
        else
        {
            tmp[k] = in[i];
            k++;
        }
    }
    if(k)
    {
        ret[j] = tmp;
        ret[j].resize(k);
    }

    return nbLines;
}

unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, const std::set<unsigned char>& separators)
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
        if(separators.count(in[i]))
        {
            ret[j] = tmp;
            ret[j].resize(k);
            k=0;
            j++;
        }
        else
        {
            tmp[k] = in[i];
            k++;
        }
    }
    if(k)
    {
        ret[j] = tmp;
        ret[j].resize(k);
    }

    return nbLines;
}

unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, unsigned char separator)
{
    std::set<unsigned char> tmp;
    tmp.insert(separator);
    return loadInString(in,ret,tmp);
}
