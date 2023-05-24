#ifndef _KMEAN_H
#define _KMEAN_H

#include "../centre.h"
#include "../mission.h"
#include "group_kmean.h"


class kmean {

private:

    Mission *mission;
    int nb_missions;
    Centre *centre;
    int nb_centres;

    Position *average_position;

public:

    // CONSTRUCTEURS
    kmean(/* args */);
    kmean(Mission *mission, int nb_missions, Centre *centre, int nb_centres);

    // DESTRUCTEURS
    ~kmean();


    // METHODES
    void make_group(); // fonction qui va attribuer un groupe à chaque mission et chaque centre

    Position compute_average_position(Group_kmean group);
    



};



#endif // _KMEAN_H