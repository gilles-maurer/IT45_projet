#ifndef _DATA_H
#define _DATA_H

#include <string>
#include "../mission.h"
#include "../employe.h"
#include "../centre.h"

class Data
{
private:

    std::string repo; 

public:
    Data(/* args */);
    Data(std::string repo);
    ~Data();


    // METHODES
    
    int count_lines(std::string file_name);

    Mission *read_missions(int nb_missions);
    Employe *read_employes(int nb_employe);
    Centre *read_centres(int nb_centre);




};





#endif // _DATA_H