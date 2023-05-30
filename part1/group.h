#ifndef _GROUP_H
#define _GROUP_H

#include "../centre.h"
#include "../mission.h"

#include <string>
#include <iostream>

class Group {
private:

    Centre centre; 
    Mission *list_missions;

    int nb_missions;

public:
    Group();
    ~Group();

    // GETTERS
    Centre getCentre();
    Mission *getListMissions();
    int getNbMissions();

    // SETTERS
    void setCentre(Centre centre);
    void setListMissions(Mission *list_missions);

    // METHODES
    void print();
    void addMission(Mission mission);


};



#endif // _GROUP_H