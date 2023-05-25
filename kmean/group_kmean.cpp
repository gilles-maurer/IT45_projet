#include "group_kmean.h"


Group_kmean::Group_kmean(/* args */)
{
}

Group_kmean::~Group_kmean()
{
}

// GETTERS
Position Group_kmean::get_average_position() {
    return this->average_position;
}

Centre Group_kmean::get_centre() {
    return this->centre;
}

int Group_kmean::get_nb_missions() {
    return this->nb_missions;
}

// SETTERS
void Group_kmean::set_average_position(Position average_position) {
    this->average_position = average_position;
}


// METHODES

void Group_kmean::add_mission(Mission mission) {

    Mission *new_missions = new Mission[nb_missions + 1];

    for (int i = 0; i < nb_missions; i++) {
        new_missions[i] = this->mission[i];
    }

    new_missions[nb_missions] = mission;

    this->mission = new_missions;
}

void Group_kmean::remove_mission(Mission mission) {

    Mission *new_missions = new Mission[nb_missions - 1];

    int index = 0;

    for (int i = 0; i < nb_missions; i++) {
        if (this->mission[i].getId() != mission.getId()) {
            new_missions[index] = this->mission[i];
            index++;
        }
    }

    this->mission = new_missions;

}

void Group_kmean::change_centre(Centre centre) {

    this->centre = centre;

}

bool Group_kmean::are_same(Group_kmean group) {

    if (this->nb_missions != group.nb_missions) {
        return false;
    }

    for (int i = 0; i < nb_missions; i++) {
        if (this->mission[i].getId() != group.mission[i].getId()) {
            return false;
        }
    }

    return true;
}


Position Group_kmean::compute_average_position() {

    Position average_position;

    for (int i = 0; i < nb_missions; i++) {
        average_position = average_position + mission[i].getPosition(); // surcharge de l'opérateur +
    }

    average_position = average_position / nb_missions; // surcharge de l'opérateur /

    return average_position;
}




