#include "preprocessing.hpp"
#include "util.hpp"


bool Preprocessing::initialized = false;
std::map<std::string,unsigned char> Preprocessing::correspondances;


Preprocessing::Preprocessing(const std::string& path, bool update) :
    updated_data(false)
{
    separators = {'|','#',' '};
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
    updated_data = true;
}

void Preprocessing::init()
{
    if(!initialized)
    {
        correspondances[",\"\"\""] = '|';
    	correspondances["\"\"\""] = '#';
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

        initialized = true;
    }
}
