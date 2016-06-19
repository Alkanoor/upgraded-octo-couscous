#ifndef LEARNER_HPP_INCLUDED
#define LEARNER_HPP_INCLUDED


#include <vector>


class Learner
{
    public:
        Learner(int n_iter_for_threshold = 1000, float ratio = 0.5, float a = 0.5, float b = 0.75, float k = 1.5, float delta = 0);

        void fit();
        void predict();
        float score(const std::vector<int>& classified, const std::vector<int>& ref);

        void set_train_words(const std::vector<std::vector<int> >& vectorized);
        void set_test_words(const std::vector<std::vector<int> >& vectorized);

        float partial_cross_val(const std::vector<std::vector<int> >& vectorized, const std::vector<int>& target, float test_ratio, float cur_fold);
        std::vector<float> cross_val(const std::vector<std::vector<int> >& vectorized, const std::vector<int>& target, float ratio);

        void compute_idf();
        float score_tfidf(const std::vector<int>& v);

    private:
        int n_iter;
        float ratio, a, b, k, delta, avg;

        float threshold;

        std::vector<std::vector<int> > test_words;
        std::vector<std::vector<int> > train_words;
        std::vector<int> train_target;
        std::vector<int> test_target;
        std::vector<int> predicted;

        std::vector<float> idf, counter_positive, counter_negative, scores;
};


#endif
