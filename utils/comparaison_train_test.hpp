#ifndef COMPARAISON_HPP_INCLUDED
#define COMPARAISON_HPP_INCLUDED


#include "Vectorizer.hpp"


class Comparaison_Train_Test
{
    public:
        Comparaison_Train_Test(const std::string& train, const std::string& test);
		
		std::map<std::string,std::pair<std::string,float> > minimum_distances_to_unknown words() const;

    private:
        static bool initialized;
        static std::map<std::string, unsigned char, std::greater<std::string> > correspondances;
        static std::map<std::string, std::string, std::greater<std::string> > string_correspondances;
        static std::vector<std::pair<std::string,std::string> > regex_replace;
        static std::vector<std::pair<std::string,std::string> > cur_regexed;

        std::set<unsigned char> separators;

        std::string path_to_data;
        std::vector<unsigned char> raw;
        std::vector<std::vector<unsigned char> > first_cut;
        std::vector<std::vector<std::string> > second_cut;
        std::vector<std::vector<std::string> > third_cut;
        std::vector<std::vector<std::pair<std::string,std::string> > > regex_for_lines;

        bool updated_data;
        void update_priv();

        static void init();
};


template <typename T>
std::vector<T> Preprocessing::apply(const std::function<T(const std::vector<std::string>&)>& func)
{
    if(!updated_data)
        update_priv();

    std::vector<T> ret(second_cut.size());
    for(unsigned int i=0;i<second_cut.size();i++)
        ret[i] = func(second_cut[i]);

    return ret;
}


#endif
