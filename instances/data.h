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

    float **read_distance(int nb_missions, int nb_centres);

    int read_int_from_line(std::string &line);
    float read_float_from_line(std::string &line);
    std::string read_string_from_line(std::string &line);

};





#endif // _DATA_H