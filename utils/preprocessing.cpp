#include "preprocessing.hpp"
#include "util.hpp"


#include <iostream>
#include <fstream>


bool Preprocessing::initialized = false;
std::map<std::string, unsigned char, std::greater<std::string> > Preprocessing::correspondances;
std::map<std::string, std::string, std::greater<std::string> > Preprocessing::string_correspondances;


Preprocessing::Preprocessing(const std::string& path, bool update) :
    updated_data(false)
{
    separators = {'|','#',' ','/','-','\''};
    init();
    reset_path(path,update);
}

void Preprocessing::reset_path(const std::string& path, bool update)
{
    updated_data = false;
    path_to_data = path;

    read(path,raw);

    if(update)
        update_priv();
}

const std::vector<std::vector<unsigned char> >& Preprocessing::first_processing()
{
    load_in_vec(raw, first_cut);

    std::vector<unsigned char> tmp;
    for(unsigned int i=0;i<first_cut.size();i++)
	{
        replace_seq_by_string(first_cut[i], tmp, string_correspondances);
        first_cut[i] = tmp;
		replace_seq_by(first_cut[i], tmp, correspondances);
		first_cut[i] = tmp;
	}

    return first_cut;
}

const std::vector<std::vector<std::string> >& Preprocessing::second_processing()
{
    second_cut.resize(first_cut.size());

	std::vector<std::string> words;
	for(unsigned int i=0;i<first_cut.size();i++)
	{
		load_in_string(first_cut[i], words, separators);
        second_cut[i] = words;
	}

    return second_cut;
}

const std::vector<std::vector<std::string> >& Preprocessing::third_processing()
{
    for(unsigned int i=0;i<second_cut.size();i++)
        for(unsigned int j=0;j<second_cut[i].size();j++)
            second_cut[i][j] = regexing(second_cut[i][j]);

    return second_cut;
}

std::string Preprocessing::regexing(const std::string& s)
{
    std::string ret = s;

    #ifdef REGEX_ENABLED

    boost::regex reg("\\\"");
    ret = boost::regex_replace(s,reg,"");

    reg = boost::regex("ass.*$");
    ret = boost::regex_replace(ret,reg,"ass");

    reg = boost::regex("a\\$\\$");
    ret = boost::regex_replace(ret,reg,"ass");

    reg = boost::regex("a\\$\\$.*$");
    ret = boost::regex_replace(ret,reg,"ass");

    reg = boost::regex("a\\*\\*.*$");
    ret = boost::regex_replace(ret,reg,"ass");

    reg = boost::regex("f(\\*)");
    ret = boost::regex_replace(ret,reg,"fuck");

    //reg = boost::regex("f(\\*)*ck.*");
    //ret = boost::regex_replace(ret,reg,"fuck");

    reg = boost::regex("f.*uckin.*$");
    ret = boost::regex_replace(ret,reg,"fuck");

    reg = boost::regex("f.?.?.?.?uck.?.?.?.?.?.?.?.?.?.?you$");
    ret = boost::regex_replace(ret,reg,"fuckyou");

    reg = boost::regex("f.?.?.?.?uck.*$");
    ret = boost::regex_replace(ret,reg,"fuck");

    reg = boost::regex("(\\*)+");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("\\$[0-9]+k?");
    ret = boost::regex_replace(ret,reg,"dollars");

    reg = boost::regex("\\$stupid");
    ret = boost::regex_replace(ret,reg,"stupid");

    reg = boost::regex("&amp");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("&nbsp");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("\\\\x.{2}");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("^[0-9]+k.*$");
    ret = boost::regex_replace(ret,reg,"dollars");

    reg = boost::regex("^[0-9]+th.*$");
    ret = boost::regex_replace(ret,reg,"date");

    reg = boost::regex("^[0-9]+mn.*$");
    ret = boost::regex_replace(ret,reg,"time");

    reg = boost::regex("^[0-9]{4}[0-9]*[^0-9]+$");
    ret = boost::regex_replace(ret,reg,"number");

    reg = boost::regex("^[0-9]{4}");
    ret = boost::regex_replace(ret,reg,"year");

    reg = boost::regex("^[0-9]{2}.*$");
    ret = boost::regex_replace(ret,reg,"number");

    reg = boost::regex("^\\:.*$");
    ret = boost::regex_replace(ret,reg,"smiley");

    reg = boost::regex("<3");
    ret = boost::regex_replace(ret,reg,"love");

    reg = boost::regex("<[^>]*>");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("<[^>]*>");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex(">");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("<");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("^@.*$");
    ret = boost::regex_replace(ret,reg,"pseudo");

    reg = boost::regex("@");
    ret = boost::regex_replace(ret,reg,"a");

    reg = boost::regex("\\[[^\\]]\\]");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("\\\\tick");
    ret = boost::regex_replace(ret,reg,"tick");

    reg = boost::regex("\\\\t");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("\\\\u[0-9a-f]{4}");
    ret = boost::regex_replace(ret,reg,"");

    reg = boost::regex("extra*$");
    ret = boost::regex_replace(ret,reg,"extra");

    reg = boost::regex("extre*$");
    ret = boost::regex_replace(ret,reg,"extreme");

    reg = boost::regex("face.*.*.*$");
    ret = boost::regex_replace(ret,reg,"face");

    reg = boost::regex("fag.*$");
    ret = boost::regex_replace(ret,reg,"fag");

    reg = boost::regex("fail.*$");
    ret = boost::regex_replace(ret,reg,"fail");

    reg = boost::regex("faith.*$");
    ret = boost::regex_replace(ret,reg,"faith");

    reg = boost::regex("fak.*$");
    ret = boost::regex_replace(ret,reg,"fak");

    reg = boost::regex("fall.*$");
    ret = boost::regex_replace(ret,reg,"fall");

    reg = boost::regex("fals.*$");
    ret = boost::regex_replace(ret,reg,"fals");

    reg = boost::regex("fanatic.*$");
    ret = boost::regex_replace(ret,reg,"fnatic");

    reg = boost::regex("fantas.*$");
    ret = boost::regex_replace(ret,reg,"fntasie");

    reg = boost::regex("fan.*$");
    ret = boost::regex_replace(ret,reg,"fan");

    reg = boost::regex("stalk.*$");
    ret = boost::regex_replace(ret,reg,"stalk");

    #endif

    return ret;
}

void Preprocessing::update_case()
{
    for(unsigned int i=0;i<second_cut.size();i++)
        for(unsigned int j=0;j<second_cut[i].size();j++)
            for(unsigned int k=0;k<second_cut[i][j].size();k++)
                if(second_cut[i][j][k]>='A'&&second_cut[i][j][k]<='Z')
                    second_cut[i][j][k] = second_cut[i][j][k]-'A'+'a';
}

void Preprocessing::rescale_ascii()
{
    for(unsigned int i=0;i<second_cut.size();i++)
        for(unsigned int j=0;j<second_cut[i].size();)
        {
            bool del = true;
            for(unsigned int k=0;k<second_cut[i][j].size();k++)
                if(second_cut[i][j][k]>='A'&&second_cut[i][j][k]<='Z')
                    del = false;
                else if(second_cut[i][j][k]>='a'&&second_cut[i][j][k]<='z')
                    del = false;
                else if(second_cut[i][j][k]>='0'&&second_cut[i][j][k]<='9')
                    del = false;
            if(del)
                second_cut[i].erase(second_cut[i].begin()+j);
            else
                j++;
        }
}

void Preprocessing::save_in_file(const std::string& path, bool title, bool endline) const
{
    std::ofstream ofs(path.c_str(),std::ios::trunc|std::ios::out);

    for(unsigned int i=0;i<second_cut.size();i++)
    {
        if(title)
            ofs<<"=============================== Comment number "<<i<<std::endl;
        for(auto j : second_cut[i])
            if(endline)
                ofs<<j<<std::endl;
            else
                ofs<<j<<" ";
        ofs<<std::endl;
    }
}

void Preprocessing::set_separators(const std::set<unsigned char>& sep, bool update)
{
    separators = sep;
    if(!updated_data)
        second_processing();
}

const std::vector<std::vector<std::string> >& Preprocessing::get_words() const
{return second_cut;}

void Preprocessing::update_priv()
{
    first_processing();
    second_processing();
    rescale_ascii();
    update_case();
    third_processing();
    rescale_ascii();
    updated_data = true;
}

void Preprocessing::init()
{
    if(!initialized)
    {
        std::ifstream others("../data/correspondancesAdded.txt");
        if(!others)
            std::cerr<<"No file for correspondances found !"<<std::endl;
        else
        {
            std::string tmp1, tmp2;
            while(others>>tmp1)
            {
                others>>tmp2;
                string_correspondances[tmp1] = tmp2;
            }
        }
        string_correspondances["....."] = " ..... ";
        string_correspondances["...."] = " .... ";
        string_correspondances["..."] = " ... ";
        string_correspondances[".."] = " .. ";
        string_correspondances["."] = " . ";
        string_correspondances["!!!!"] = " !!!! ";
        string_correspondances["!!!"] = " !!! ";
        string_correspondances["!!"] = " !! ";
        string_correspondances["!"] = " ! ";
        string_correspondances["???"] = " ??? ";
        string_correspondances["??"] = " ?? ";
        string_correspondances["?"] = " ? ";
        string_correspondances[","] = " , ";
        string_correspondances[";"] = " ; ";
        string_correspondances["("] = " ( ";
        string_correspondances[")"] = " ) ";
        correspondances[", \"\"\""] = '|';
    	correspondances["\"\"\""] = '#';
    	correspondances["\\\\xc2"]=' ';
    	correspondances["\\\\xa0"]=' ';
    	correspondances["\\xa0"]=' ';
    	correspondances["\\xa1"]=' ';
    	correspondances["\\xa3"]=' ';
    	correspondances["\\xa9"]=' ';
    	correspondances["\\xe1"]='a';
    	correspondances["\\xe3"]='a';
    	correspondances["\\xe7"]='c';
    	correspondances["\\xfd"]='y';
    	correspondances["\\xed"]='i';
    	correspondances["\\xfa"]='u';
    	correspondances["\\xf8"]='o';
    	correspondances["\\xf6"]='o';
    	correspondances["\\xdc"]='U';
    	correspondances["\\xe0"]='a';
    	correspondances["\\xe9"]='e';
    	correspondances["\\xe8"]='e';
    	correspondances["\\xfc"]='u';
    	correspondances["\\n"]=' ';
    	correspondances["\\xbf"]=' ';
    	correspondances["\\xf1"]='n';
    	correspondances["\\xc2"]='A';
    	correspondances["\\xb7"]=' ';
    	correspondances["\\r"]=' ';
    	correspondances["\\ufeff"]=' ';
    	correspondances["\\u2018"]='\'';
    	correspondances["\\u2019"]='\'';
    	correspondances["\\u1ee9"]='u';
    	correspondances["\\u1ec3"]='e';
    	correspondances["\\u1ef1"]='a';
    	correspondances["\\u2013"]=' ';
    	correspondances["\\u2016"]=' ';
    	correspondances["\\u200f"]=' ';
    	correspondances["\\u0105"]='a';
    	correspondances["\\u0111"]='d';
    	correspondances["\\u1ec5"]='e';
    	correspondances["\\u1ebf"]='e';
    	correspondances["\\u1eb7"]='a';
    	correspondances["\\u0169"]='u';
    	correspondances["\\u0142"]='l';
    	correspondances["\\u201c"]='\"';
    	correspondances["\\u201d"]='\"';
    	correspondances["\\u201e"]='\"';
    	correspondances["\\u2026"]='.';
    	correspondances["\\u0161"]='s';
    	correspondances["\\u2665"]=' ';
    	correspondances["\\u015b"]='s';
    	correspondances["\\u203d"]='!';
    	correspondances["\\xf3"]='o';
    	correspondances["\\u0119"]='e';
    	correspondances["\\u017a"]='Z';
    	correspondances["\\u017e"]='Z';
    	correspondances["\\u017c"]='Z';
    	correspondances["\\u0107"]='c';
    	correspondances["\\xe5"]='a';
    	correspondances["\\xe4"]='a';
    	correspondances["\\U0001f308"]=' ';
    	correspondances["\\U0001f3e9"]=' ';
    	correspondances["\\U0001f48b"]=' ';
    	correspondances["\\\\"]=' ';
    	correspondances["\\ "]=' ';
    	correspondances["\""]=' ';

        initialized = true;
    }
}
