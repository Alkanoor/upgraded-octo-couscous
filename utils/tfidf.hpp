#ifndef TFIDF_HPP_INCLUDED
#define TFIDF_HPP_INCLUDED
#include <vector>
#include <utility>

float tfidf(const std::vector<std::vector<int>>& in, int comm, int word); //tfidf classique
float tfidf_trained(const std::vector<std::vector<int>>& in, int comm, const std::vector<float>& idf);
//le coeff idf est calculé sur les occurences dans les bons commentaire au lieu de tous.
float idf_train(const std::vector<std::vector<int>>& in, int word);
std::pair<float,float> threshold(const std::vector<std::vector<int>>& in, const std::vector<float>& score); //retourne une pair seuil/score théorique.
#endif
