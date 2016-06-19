#include "../utils/comparaison_train_test.hpp"
#include "../utils/util.hpp"


int main()
{
    Comparaison_Train_Test comparaison("../data/train_after_preprocessing.txt","../data/test_after_preprocessing.txt");
    comparaison.save_dictionary("output/dictionary.txt");

    Vectorizer::save(comparaison.train(),"output/vectorized_train.txt");
    Vectorizer::save(comparaison.test(),"output/vectorized_test.txt");

    return 0;
}
