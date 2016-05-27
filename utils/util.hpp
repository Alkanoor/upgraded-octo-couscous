#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED


#include <ostream>
#include <vector>
#include <set>


//place tous les octets d'un fichier dans un tableau, retourne true si le fichier existe, false sinon
bool read(const std::string& path, std::vector<unsigned char>& ret);

//renvoie les dimensions du tableau des mots séparés (surtout utile pour de très gros fichiers mais utilisé dans les fonctions suivantes)
void split_and_count(const std::vector<unsigned char>& in, unsigned int& maxSize, unsigned int& nbLines, const std::set<unsigned char>& separators)

//découpe un tableau d'octets en lignes (selon un séparateur qui peut être changé)
unsigned int loadInVec(const std::vector<unsigned char>& in, std::vector<std::vector<unsigned char> >& ret, unsigned char separator = '\n');

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon plusieurs séparateurs qui peuvent être changés)
unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, const std::set<unsigned char>& separators);

//découpe un tableau d'octets (à utiliser avec une ligne par exemple) en un tableau de mots (selon un séparateur qui peut être changé)
unsigned int loadInString(const std::vector<unsigned char>& in, std::vector<std::string>& ret, unsigned char separator = '\n');

//à faire : découper selon des mots


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
void toString(const std::vector<T>& v, std::string& ret)
{
    ret.resize(v.size());
    for(unsigned int i=0;i<v.size();i++)
        ret[i] = (char)(v[i]);
}


#endif
