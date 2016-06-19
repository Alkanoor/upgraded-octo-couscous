#include <fstream>
#include <array>
#include <cmath>

#include "comparaison_train_test.hpp"


Comparaison_Train_Test::Comparaison_Train_Test()
{}

Comparaison_Train_Test::Comparaison_Train_Test(const std::string& dict_path)
{
    load_dictionary(dict_path);
}

Comparaison_Train_Test::Comparaison_Train_Test(const std::string& train_path, const std::string& test_path)
{
	Preprocessing p1(train_path);
    train_words = p1.get_words();
    Preprocessing p2(test_path);
    test_words = p2.get_words();

    update();
}

Comparaison_Train_Test::Comparaison_Train_Test(const std::vector<std::vector<std::string> >& v1, const std::vector<std::vector<std::string> >& v2) :
    train_words(v1),
    test_words(v2)
{
    update();
}

void Comparaison_Train_Test::load_dictionary(const std::string& dict_path)
{
    common_dictionary.clear();
    common_conversed_dictionary.clear();

    std::ifstream ifs(dict_path.c_str());
    std::string tmp;
    while(ifs>>tmp)
    {
        int a;
        ifs>>a;
        common_dictionary[tmp] = a;
        common_conversed_dictionary[a] = tmp;
    }
}

void Comparaison_Train_Test::load_dictionary(const std::map<std::string,int>& dict)
{
    common_dictionary = dict;
    common_conversed_dictionary.clear();

    for(auto it : common_dictionary)
        common_conversed_dictionary[it.second] = it.first;

    update_train();
    update_test();
}

void Comparaison_Train_Test::save_dictionary(const std::string& path)
{
    std::ofstream ofs(path.c_str(),std::ios::out);
    for(auto it : common_dictionary)
        ofs<<it.first<<" "<<it.second<<std::endl;
}

void Comparaison_Train_Test::load_train(const std::vector<std::vector<std::string> >& train)
{
    train_words = train;
    update_train();
}

void Comparaison_Train_Test::load_test(const std::vector<std::vector<std::string> >& test)
{
    test_words = test;
    update_test();
}

std::vector<std::vector<int> > Comparaison_Train_Test::train() const
{return train_vec;}

std::vector<std::vector<int> > Comparaison_Train_Test::test() const
{return test_vec;}

const std::map<std::string,int>& Comparaison_Train_Test::get_dictionary() const
{return common_dictionary;}

int Comparaison_Train_Test::is_begin_of(const std::string& s1, const std::string& s2, int min_size)
{
    unsigned int i=0;
    for(;i<s1.size()&&i<s2.size()&&s1[i]==s2[i];i++)
        ;
    if((int)i<min_size)
        return 0;
    return i;
}

int Comparaison_Train_Test::contains(const std::string& s1, const std::string& s2, int min_size, std::string& root)
{
    for(unsigned int i=0;i+min_size<s1.size();i++)
    {
        std::string tmp = s1.substr(i,s1.size()-i);
        int s = is_begin_of(tmp,s2,min_size);
        if(s)
        {
            root = tmp.substr(0,s);
            return s;
        }
    }
    return 0;
}

int Comparaison_Train_Test::contains_subword(const std::string& s1, const std::string& s2, int min_size, std::string& root)
{
    for(unsigned int i=0;i+min_size<s2.size();i++)
    {
        std::string tmp = s2.substr(i,s2.size()-i);
        if(contains(s1,tmp,min_size,root))
            return root.size();
    }
    return 0;
}

float Comparaison_Train_Test::distance(const std::string& s1, const std::string& s2, std::string& root)
{
    int s = contains_subword(s1,s2,3,root);
    if(s)
    {
        int m = std::min(s1.size(),s2.size());
        if(m<4)
            m = 4;

        bool ok = false;
        if(is_begin_of(s1,s2,m*3/4+1))
            ok = true;
        else if((s1[0]<'a'||s1[0]>'z')&&is_begin_of(s1.substr(1,s1.size()-1),s2,m*3/4+2))
            ok = true;
        else if((s2[0]<'a'||s2[0]>'z')&&is_begin_of(s1,s2.substr(1,s2.size()-1),m*3/4+2))
            ok = true;
        else if((s1[0]<'a'||s1[0]>'z')&&(s2[0]<'a'||s2[0]>'z')&&is_begin_of(s1.substr(1,s1.size()-1),s2.substr(1,s2.size()-1),m*3/4+2))
            ok = true;
        if(!ok)
            return -1;

        float ratio = ((s1.size()>s2.size())?(float)s2.size()/(float)s1.size():(float)s1.size()/(float)s2.size());
        //std::cout<<ret/(float)(1+abs(m-s))<<" "<<s<<" "<<ratio<<" "<<(float)s*(log(1.01-ratio)-log(1.01))/(log(0.01)-log(1.01))/(float)(1+abs(m-s))<<std::endl;
        return (float)s*(log(1.01-ratio)-log(1.01))/(log(0.01)-log(1.01))/(float)(1.0+abs(m-s));
    }
    return -1;
}

void Comparaison_Train_Test::update_train()
{
    train_vec.resize(train_words.size());
    for(unsigned int i=0;i<train_vec.size();i++)
    {
        train_vec[i].clear();
        for(unsigned int j=0;j<train_words[i].size();j++)
            if(common_dictionary.count(train_words[i][j]))
                train_vec[i].push_back(common_dictionary[train_words[i][j]]);
    }
}

void Comparaison_Train_Test::update_test()
{
    test_vec.resize(test_words.size());
    for(unsigned int i=0;i<test_vec.size();i++)
    {
        test_vec[i].clear();
        for(unsigned int j=0;j<test_words[i].size();j++)
            if(common_dictionary.count(test_words[i][j]))
                test_vec[i].push_back(common_dictionary[test_words[i][j]]);
    }
}

void Comparaison_Train_Test::update()
{
    Vectorizer v(train_words);
    common_dictionary = v.get_dictionary();
    common_conversed_dictionary = v.get_index_to_words();

    std::string root;
    std::vector<std::array<std::string,3> > links;
    /*for(auto it : common_dictionary)
    {
        float cur_max = -1;
        std::string cur_root, cur_word;
        for(auto it2 : common_dictionary)
            if(it2.first!=it.first)
            {
                float f = distance(it.first,it2.first,root);
                if(f>cur_max)
                {
                    cur_max = f;
                    cur_root = root;
                    cur_word = it2.first;
                }
            }
        if(cur_max>0.8)
        {
            links.push_back(std::array<std::string,3>({it.first,cur_root,cur_word}));
            std::cout<<"So for "<<it.first<<" we have "<<cur_max<<" "<<cur_root<<std::endl;
        }
    }*/

    //update_links(links);
    //links.clear();

    Vectorizer v2(test_words);
    auto test_dictionary = v2.get_dictionary();

    for(auto it : test_dictionary)
        if(!common_dictionary.count(it.first))
        {
            std::cout<<"==================================="<<std::endl;
            std::cout<<it.first<<" unknown =>"<<std::endl;
            float cur_max = -1;
            std::string cur_root, cur_word;
            for(auto it2 : common_dictionary)
                if(it2.first!=it.first)
                {
                    float f = distance(it.first,it2.first,root);
                    if(f>cur_max)
                    {
                        cur_max = f;
                        cur_root = root;
                        cur_word = it2.first;
                    }
                }
            if(cur_max>0.8)
            {
                common_dictionary[it.first] = common_dictionary[cur_word];
                links.push_back(std::array<std::string,3>({it.first,cur_root,cur_word}));
                std::cout<<"So for (2) "<<it.first<<" we have "<<cur_max<<" "<<cur_root<<std::endl;
            }
        }

    //update_links(links);

    update_train();
    update_test();
}

void Comparaison_Train_Test::update_links(const std::vector<std::array<std::string,3> >& links)
{
    std::cout<<"Sizes : "<<std::endl;
    std::cout<<common_conversed_dictionary.size()<<" "<<common_dictionary.size()<<std::endl;
    int min = 10, max = 10;
    for(auto it : common_conversed_dictionary)
        if(it.first<min)
            min = it.first;
        else if(it.first>max)
            max = it.first;
    std::cout<<"Min max (conversed) : "<<min<<" "<<max<<std::endl;
    for(auto it : common_dictionary)
        if(it.second<min)
            min = it.second;
        else if(it.second>max)
            max = it.second;
    std::cout<<"Min max (normal) : "<<min<<" "<<max<<std::endl;
    for(unsigned int i=0;i<links.size();i++)
    {
        std::string root = links[i][1];
        if(common_dictionary.count(root))
        {
            common_dictionary[links[i][0]] = common_dictionary[root];
            common_dictionary[links[i][2]] = common_dictionary[root];
            std::cout<<"Putting parent of "<<links[i][0]<<" : "<<root<<" "<<common_dictionary[root]<<std::endl;
            std::cout<<"Putting parent of "<<links[i][2]<<" : "<<root<<" "<<common_dictionary[root]<<std::endl;
            std::string cur = links[i][0];
            while(common_conversed_dictionary[common_dictionary[cur]]!=cur)
            {
                cur = common_conversed_dictionary[common_dictionary[cur]];
                common_dictionary[cur] = common_dictionary[root];
                std::cout<<"Putting parent of "<<cur<<" : "<<root<<" "<<common_dictionary[root]<<std::endl;
            }
            cur = links[i][2];
            while(common_conversed_dictionary[common_dictionary[cur]]!=cur)
            {
                cur = common_conversed_dictionary[common_dictionary[cur]];
                common_dictionary[cur] = common_dictionary[root];
                std::cout<<"Putting parent of "<<cur<<" : "<<root<<" "<<common_dictionary[root]<<std::endl;
            }
        }
        else
        {
            if(common_conversed_dictionary.count(common_conversed_dictionary.size()+1))
            {
                std::cerr<<"Conversed dictionary should not contain this too big value "<<common_dictionary.size()<<std::endl;
                return;
            }
            int cur_size = common_conversed_dictionary.size()+1;
            common_dictionary[root] = cur_size;
            common_conversed_dictionary[common_dictionary[root]] = root;
            common_dictionary[links[i][0]] = common_dictionary[root];
            common_dictionary[links[i][2]] = common_dictionary[root];
            std::cout<<"Creating parent of "<<links[i][0]<<" and "<<links[i][2]<<" => "<<root<<" "<<common_dictionary[root]<<std::endl;
        }
    }
}
