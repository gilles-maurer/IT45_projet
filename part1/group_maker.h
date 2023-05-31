#ifndef _GROUP_MAKER_H
#define _GROUP_MAKER_H

#include "group.h"
#include "../mission.h"
#include "../centre.h"

#include <iostream>


class GroupMaker 
{
private:

    Group *list_groups;

    int nb_missions;
    int nb_centres;
    Mission *list_missions;
    Centre *list_centres;


public:
    GroupMaker(/* args */);
    GroupMaker(int nb_missions, int nb_centres, Mission *list_missions, Centre *list_centres);
    ~GroupMaker();

    // GETTERS
    Group *getListGroups();

    // METHODES
    void makeGroups();
    
    void printGroups();

    Centre findClosestCentre(Mission mission);



};





#endif // _GROUP_MAKER_H