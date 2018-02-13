#include<eccezione.h>

eccezione::eccezione(std::string s):testo(s){}

std::string eccezione::getTesto(){return testo;}
