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

    this->average_position = new Position[nb_centres];

    for (int i = 0; i < nb_centres; i++) {
        this->average_position[i] = centre[i].getPosition();
    }

}

// DESTRUCTEURS
kmean::~kmean()
{
}


// METHODES

void kmean::make_group() {

    // On va attribuer un groupe à chaque mission et chaque centre
    for (int i = 0; i < this->nb_missions; i++) {
        for (int j = 0; j < this->nb_centres; j++) {
            // On va calculer la distance entre la mission i et le centre j
            // On va attribuer le groupe au centre le plus proche de la mission
     


     
        }
    }


}

Position kmean::compute_average_position(Group_kmean group) {

    Position average_position;

    return average_position;
}