#ifndef COMPARAISON_HPP_INCLUDED
#define COMPARAISON_HPP_INCLUDED


#include "Vectorizer.hpp"


class Comparaison_Train_Test
{
    public:
        Comparaison_Train_Test();
        Comparaison_Train_Test(const std::string& dict_path);
        Comparaison_Train_Test(const std::string& train_path, const std::string& test_path);
        Comparaison_Train_Test(const std::vector<std::vector<std::string> >& v1, const std::vector<std::vector<std::string> >& v2);

        void load_dictionary(const std::string& dict_path);
        void load_dictionary(const std::map<std::string,int>& dict);
        void save_dictionary(const std::string& path);

        void load_train(const std::vector<std::vector<std::string> >& train);
        void load_test(const std::vector<std::vector<std::string> >& test);

		std::vector<std::vector<int> > train() const;
		std::vector<std::vector<int> > test() const;
		const std::map<std::string,int>& get_dictionary() const;

		static int is_begin_of(const std::string& s1, const std::string& s2, int min_size);
        static int contains(const std::string& s1, const std::string& s2, int min_size, std::string& root);
        static int contains_subword(const std::string& s1, const std::string& s2, int min_size, std::string& root);
		static float distance(const std::string& s1, const std::string& s2, std::string& root);

    private:
        std::vector<std::vector<std::string> > train_words;
        std::vector<std::vector<std::string> > test_words;
        std::vector<std::vector<int> > train_vec;
		std::vector<std::vector<int> > test_vec;
		std::map<std::string,int> common_dictionary;
		std::map<int,std::string> common_conversed_dictionary;

		void update_train();
		void update_test();

		void update();
		void update_links(const std::vector<std::array<std::string,3> >& links);
};


#endif
