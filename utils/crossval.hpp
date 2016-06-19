#ifndef CROSSVAL_HPP_INCLUDED
#define CROSSVAL_HPP_INCLUDED
#include <vector>
#include <utility>

std::pair<std::vector<std::vector<int>>,std::vector<std::vector<int>>> split(unsigned int n,std::vector<std::vector<int>> vect); //renvoie aléatoirement n échantillons, la copie est volontaire
std::vector<std::vector<int>> bootstrap(int n,std::vector<std::vector<int>>& vect); //tire n echantillons, avec remise !
std::vector<float> crossval_idf(std::vector<std::vector<int>> vect,int dictionnary_size,int n_sample, int n_trash,int sample_size=0); //si on laisse un paramètre à zero il prend tout.

#endif
