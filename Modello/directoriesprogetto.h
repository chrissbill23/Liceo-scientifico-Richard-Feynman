#ifndef DIRECTORIESPROGETTO
#define DIRECTORIESPROGETTO

#include <string>
using namespace std;

class DirectoriesProgetto{
private:
    static string pathDB;
public:
    static string pathStudDB();
    static string pathImpiegatoDB();
    static string pathMessDB();
};

#endif // DIRECTORIESPROGETTO

