#include <string>
using namespace std;

class mission {
private:

    int id; 
    int day; // valeur entre 1 et 7
    int hour_start; // valeur entre 0 et 23
    int hour_end; // valeur entre 0 et 23
    string competence; 
    string speciality; 


public:
    mission(/* args */);
    ~mission();
};

mission::mission(/* args */)
{
}

mission::~mission()
{
}
