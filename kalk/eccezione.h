#ifndef ECCEZIONE_H
#define ECCEZIONE_H
#include <string>
class eccezione
{
private:
    std::string testo;
public:
    eccezione(std::string);
    std::string getTesto();
};

#endif // ECCEZIONE_H
