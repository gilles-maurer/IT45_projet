#ifndef _GROUP_KMEAN_H
#define _GROUP_KMEAN_H

#include "../centre.h"
#include "../mission.h"


class Group_kmean
{
private:

    Mission *mission;
    int nb_missions;

    Centre centre;

    Position average_position;


public:
    Group_kmean(/* args */);
    ~Group_kmean();

    // GETTERS
    Position get_average_position();

    Centre get_centre();    
    int get_nb_missions();

    // SETTERS
    void set_average_position(Position average_position);


    // METHODES

    void add_mission(Mission mission);
    void remove_mission(Mission mission);
    void change_centre(Centre centre);

    bool are_same(Group_kmean group);

    Position compute_average_position();

};


#endif // _GROUP_KMEAN_H