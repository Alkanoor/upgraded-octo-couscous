#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED


#include <ofstream>
#include <vector>
#include <set>


//place tous les octets d'un fichier dans un tableau, retourne true si le fichier existe, false sinon
bool read(const std::string& path, std::vector<unsigned char>& ret);

//découpe un tableau d'octets en lignes (selon un séparateur qui peut être changé)
unsigned int loadInVec(const std::vector<unsigned char>& in, std::vector<std::vector<unsigned char> >& ret, unsigned char separator = '\n');

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon un séparateur qui peut être changé)
unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, unsigned char separator = '\n');

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon plusieurs séparateurs qui peuvent être changés)
unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, std::set<char> separators);

//à faire : découper selon des mots


//pour afficher facilement des vecteurs
template <typename T>
std::ofstream operator<<(std::ofstream& ofs, const std::vector<T>& v)
{
	for(unsigned int i=0;i<v.size();i++)
        ofs<<v[i];
    ofs<<std::endl;
}

//pour convertir des vecteurs en string (ne présente pas un intérêt fou mais est utilisé dans le cpp associé)
template <typename T>
void toString(const std::vector<T>& v, std::string& ret)
{
    ret.resize(v.size());
    for(unsigned int i=0;i<v.size();i++)
        ret[i] = (char)(v[i]);
}


#endif
