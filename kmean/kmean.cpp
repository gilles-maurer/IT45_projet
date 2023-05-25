#include "kmean.h"


// CONSTRUCTEURS
kmean::kmean(/* args */)
{
}

kmean::kmean(Mission *mission, int nb_mission, Centre *centre, int nb_centres)
{
    this->mission = mission;
    this->nb_missions = nb_mission;
    this->centre = centre;
    this->nb_centres = nb_centres;

    Group_kmean *groups = new Group_kmean[nb_centres];

    bool is_optimised = false;
}

// DESTRUCTEURS
kmean::~kmean()
{
}


// METHODES

Group_kmean *kmean::optimiser() {

    for (int i = 0; i < nb_centres; i++) { // on initialise les groupes avec les centres
        groups[i].change_centre(centre[i]);
        groups[i].set_average_position(centre[i].getPosition());
    }

    while (!is_optimised) { // tant que les groupes ne sont pas optimisés

        Group_kmean *new_groups = make_group(); // on change les missions de groupe

        for (int i = 0; i < nb_centres; i++) { // on calcule les nouveaux points moyens des groupes
            new_groups[i].set_average_position(new_groups[i].compute_average_position());
        }

        if (are_group_list_equals(groups, new_groups)) { // on regarde si on a atteint l'optimum
            is_optimised = true;
        } else {
            groups = new_groups;
        }

    }
        
}


Group_kmean *kmean::make_group() {

    Group_kmean *new_groups = new Group_kmean[nb_centres];

    for (int i = 0; i < nb_centres; i++) {
        new_groups[i].change_centre(groups[i].get_centre());
    }

    for(int j = 0; j < nb_missions; j++) { // on parcourt toutes les missions

        float min_distance = mission[j].getPosition().distance(groups[0].get_average_position());
        int index_min_distance = 0;

        for (int k = 1; k < nb_centres; k++) { // on parcourt tout les points moyens des groupes

            float distance = mission[j].getPosition().distance(groups[k].get_average_position());

            if (distance < min_distance) {
                min_distance = distance;
                index_min_distance = k;
            }

        }

        new_groups[index_min_distance].add_mission(mission[j]);

    }

    return new_groups;
}


bool kmean::are_group_list_equals(Group_kmean *groups1, Group_kmean *groups2) {

    bool are_equals = true;

    for (int i = 0; i < nb_centres; i++) {
        if (!groups1[i].are_same(groups2[i])) {
            are_equals = false;
        }
    }

    return are_equals;
}