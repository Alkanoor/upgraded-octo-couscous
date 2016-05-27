﻿#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED


#include <ostream>
#include <vector>
#include <map>
#include <set>


//place tous les octets d'un fichier dans un tableau, retourne true si le fichier existe, false sinon
bool read(const std::string& path, std::vector<unsigned char>& ret);

//renvoie les dimensions du tableau des mots séparés (surtout utile pour de très gros fichiers mais utilisé dans les fonctions suivantes)
void split_and_count(const std::vector<unsigned char>& in, unsigned int& maxSize, unsigned int& nbLines, const std::set<unsigned char>& separators);

//découpe un tableau d'octets en lignes (selon un séparateur qui peut être changé)
unsigned int load_in_vec(const std::vector<unsigned char>& in, std::vector<std::vector<unsigned char> >& ret, unsigned char separator = '\n');

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon plusieurs séparateurs qui peuvent être changés)
unsigned int load_in_string(const std::vector<unsigned char>& in, std::vector<std::string>& ret, const std::set<unsigned char>& separators);

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon un séparateur qui peut être changé)
unsigned int load_in_string(const std::vector<unsigned char>& in, std::vector<std::string>& ret, unsigned char separator = '\n');

/**
A faire : découper selon des mots
En attendant : on remplace les mots par un caractère qui jouera le rôle de séparateur
Le dernier paramètre correspond au nombre maximal d'occurences à remplacer (max_occur <= 0 conserve toutes les occurences) (par exemple si on veut séparer le premier chiffre du commentaire, on ne veux remplacer que la première occurence du séparateur entre les deux pour chaque ligne)
Retourne le nombre d'occurences effectivement remplacées
**/
unsigned int replace_seq_by(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::map<std::string,unsigned char>& separators_replacement, int max_occur = -1);
//cas particulier
unsigned int replace_seq_by(const std::vector<unsigned char>& in, std::vector<unsigned char>& ret, const std::string& separator, unsigned char to_replace_by, int max_occur = -1);


//pour afficher facilement des vecteurs
template <typename T>
std::ostream& operator<<(std::ostream& ofs, const std::vector<T>& v)
{
	for(unsigned int i=0;i<v.size();i++)
        ofs<<v[i];
    ofs<<std::endl;
	return ofs;
}

//pour convertir des vecteurs en string (ne présente pas un intérêt fou mais est utilisé dans le cpp associé)
template <typename T>
void to_string(const std::vector<T>& v, std::string& ret)
{
    ret.resize(v.size());
    for(unsigned int i=0;i<v.size();i++)
        ret[i] = (char)(v[i]);
}


#endif
