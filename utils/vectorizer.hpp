#ifndef VECTORIZER_HPP_INCLUDED
#define VECTORIZER_HPP_INCLUDED


#include "preprocessing.hpp"

#include <iostream>
#include <cmath>


class Vectorizer
{
    public:
        Vectorizer(const std::vector<std::vector<std::string> >& words = std::vector<std::vector<std::string> >(), bool update = true, bool train = true);

		void reset_words(const std::vector<std::vector<std::string> >& words, bool update = true, bool train = true);

        void vectorize(bool train = true);

        const std::vector<std::vector<int> >& get_vectorized() const;
        const std::map<std::string,int>& get_dictionary() const;                //returns correspondances string/index
        const std::map<int,std::string>& get_index_to_words() const;            //returns correspondances index/string
        const std::map<std::string,int>& get_counter() const;                   //returns counts of words in all the document
        const std::map<std::string,int>& get_counter_different_comments() const;//returns counts of 1 occurence per comment in all the document
		const std::map<std::string,int>& get_insult_words() const;
		const std::map<std::string,int>& get_non_insult_words() const;

		double get_ratio_insults() const;

		void save_to_file(const std::string& path);
		void load_from_file(const std::string& path);

        static void save(const std::vector<std::vector<int> >& vectorized, const std::string& path);
        static std::vector<std::vector<int> > load(const std::string& path);
		static double score(double a, double b, double c, double d);

    private:
        std::vector<std::vector<std::string> > words;
        std::vector<std::vector<int> > vectorized;
        std::map<std::string,int> index;
        std::map<int,std::string> index_to_words;
        std::map<std::string,int> counter;
        std::map<std::string,int> counter_different_comments;
		std::map<std::string,int> insults_counter;
		std::map<std::string,int> non_insults_counter;

		int n_insults;
};


#endif
