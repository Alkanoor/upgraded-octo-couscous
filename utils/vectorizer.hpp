#ifndef VECTORIZER_HPP_INCLUDED
#define VECTORIZER_HPP_INCLUDED


#include "preprocessing.hpp"

#include <cmath>


class Vectorizer
{
    public:
        Vectorizer(const std::vector<std::vector<std::string> >& words, bool update = true, double a = 0.1, double b = 0.05);

		void reset_words(const std::vector<std::vector<std::string> >& words, bool update = true);

        void vectorize();

        const std::vector<std::vector<int> >& get_vectorized() const;
        const std::map<std::string,int>& get_dictionary() const;
		const std::map<std::string,int>& get_insult_words() const;
		const std::map<std::string,int>& get_non_insult_words() const;
		const std::map<std::string,double>& get_scores() const;
		double get_ratio_insults() const;

		static double score(double a, double b, double c, double d);

    private:
        std::vector<std::vector<std::string> > words;
        std::vector<std::vector<int> > vectorized;
        std::map<std::string,int> counter;
		std::map<std::string,int> insults_counter;
		std::map<std::string,int> non_insults_counter;
		std::map<std::string,double> scores;
		std::map<std::string,double> normalized_for_insult_proba;

		int n_insults;

		double a, b;
};


#endif
