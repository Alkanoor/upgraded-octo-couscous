#include "../utils/vectorizer.hpp"
#include "../utils/learner.hpp"
#include "../utils/util.hpp"

#include <fstream>

int main()
{
	auto vectorized_raw = Vectorizer::load("output/vectorized_train_regex_non_lemmatisation.txt");
	std::vector<std::vector<int> > vectorized(vectorized_raw.size());
	std::vector<int> to_predict(vectorized_raw.size());

	for(unsigned int i=0;i<vectorized.size();i++)
	{
		if(vectorized_raw[i][0]!=1)
			to_predict[i] = 1;
		else
			to_predict[i] = 0;
		vectorized[i].resize(vectorized_raw[i].size()-1);
		for(unsigned int j=1;j<vectorized_raw[i].size();j++)
			vectorized[i][j-1] = vectorized_raw[i][j];
	}

	Learner l(1000,0.2);
	std::cout<<l.cross_val(vectorized,to_predict,0.023);

    return 0;
}
