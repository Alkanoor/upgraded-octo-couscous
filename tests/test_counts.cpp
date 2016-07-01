#include "../utils/counts.hpp"

#include <iostream>

using namespace std;

int main()
{
   unsigned int cap,ponc,oth;
   numberCapitalsPonctuation("Bonjour, Bienvenue à l'ENST !!!",cap,ponc,oth);
   cout <<cap<<"\n"<<ponc<<"\n"<<oth<<endl;
    return 0;
}
