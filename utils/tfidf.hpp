#ifndef TFIDF_HPP_INCLUDED
#define TFIDF_HPP_INCLUDED
#include <vector>


float tfidf(std::vector<std::vector<int>> in, int comm, int word); //tfidf classique
float tfidf_trained(std::vector<std::vector<int>> in, int comm,std::vector<float> idf);
//le coeff idf est calculé sur les occurences dans les bons commentaire au lieu de tous.
float idf_train(std::vector<std::vector<int>> in, int word);
#endif
