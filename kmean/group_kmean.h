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


public:
    Group_kmean(/* args */);
    ~Group_kmean();
};


#endif // _GROUP_KMEAN_H