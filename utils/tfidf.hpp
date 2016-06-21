#ifndef TFIDF_HPP_INCLUDED
#define TFIDF_HPP_INCLUDED
#include <vector>
#include <utility>

float tfidf_trained(const std::vector<std::vector<int>>& in, int comm, const std::vector<float>& idf,float word_length_bonus);
//le coeff idf est calculé sur les occurences dans les bons commentaire au lieu de tous.
std::vector<float> idf_train(const std::vector<std::vector<int>>& in, int word);
#endif
