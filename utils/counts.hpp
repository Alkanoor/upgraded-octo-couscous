#ifndef COUNTS_HPP
#define COUNTS_HPP


#include <vector>
#include <string>


int min(int a,int b);
unsigned int split(const std::string &strToSplit, std::vector<std::string> &splited, char c);
void numberCapitalsPonctuation(const std::string &str, unsigned int &capitals, unsigned int &ponctuation, unsigned int &other);


#endif
