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

    Group_kmean *groups;

    bool is_optimised;

public:

    // CONSTRUCTEURS
    kmean(/* args */);
    kmean(Mission *mission, int nb_missions, Centre *centre, int nb_centres);

    // DESTRUCTEURS
    ~kmean();


    // METHODES

    Group_kmean *optimiser(); // fonction qui va optimiser l'affectation des missions aux centres en 
                            // fonction de la position des centres et des missions

    Group_kmean *make_group(); // fonction qui va attribuer un groupe à chaque mission et chaque centre

    bool are_group_list_equals(Group_kmean *groups1, Group_kmean *groups2);
    



};



#endif // _KMEAN_H