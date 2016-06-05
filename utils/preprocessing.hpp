#ifndef PREPROCESSING_HPP_INCLUDED
#define PREPROCESSING_HPP_INCLUDED


#include <functional>
#include <vector>
#include <string>
#include <map>
#include <set>


//lot of copies of same data are made here (raw, first_cut and second_cut represent approximately the same data), but no need to improve at the moment
class Preprocessing
{
    public:
        Preprocessing(const std::string& path, bool update = true);         // path to data and update paramater (if set to false, won't preprocess data until specific functions will be called by user)

        void reset_path(const std::string& path, bool update = true);       // path to data and update paramater (if set to false, won't preprocess data until specific functions will be called by user)

        const std::vector<std::vector<unsigned char> >& first_processing(); // basic computation of data (encoded chars are replaced by readable ones)
        const std::vector<std::vector<std::string> >& second_processing();  // computation which gives words unsing separators

        template <typename T>
        std::vector<T> apply(const std::function<T(const std::vector<std::string>&)>& func); // method that allows us to get the mapped result of a function through all the lines of the input

        void set_separators(const std::set<unsigned char>& sep, bool update = false);

        const std::vector<std::vector<std::string> >& get_words() const;

    private:
        static bool initialized;
        static std::map<std::string, unsigned char> correspondances;

        std::set<unsigned char> separators;

        std::string path_to_data;
        std::vector<unsigned char> raw;
        std::vector<std::vector<unsigned char> > first_cut;
        std::vector<std::vector<std::string> > second_cut;

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
