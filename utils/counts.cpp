#include <ostream>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

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

int main()
{
    std::vector<std::string> v;
    unsigned int size = split( "This is a test", v, ' ');
	cout << size<<endl;
    for (unsigned int i =0; i<v.size();i++) cout << v[i]<<endl;
    v.clear();
    size = split( " This is    another  test ", v, ' ');

    cout <<"\n"<<size<<endl;
    for (unsigned int i =0; i<v.size();i++) cout << v[i]<<endl;
    return 0;
}
