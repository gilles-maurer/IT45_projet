#include "group_maker.h"

using namespace std;

GroupMaker::GroupMaker(/* args */)
{
}

GroupMaker::GroupMaker(int nb_missions, int nb_centres, Mission *list_missions, Centre *list_centres)
{
    this->nb_missions = nb_missions;
    this->nb_centres = nb_centres;
    this->list_missions = list_missions;
    this->list_centres = list_centres;
}

GroupMaker::~GroupMaker()
{
}

// METHODES

void GroupMaker::makeGroups()
{
    this->list_groups = new Group[this->nb_centres];

    for (int i = 0; i < this->nb_missions; i++) {
        Mission mission = this->list_missions[i];
        Centre closest_centre = this->findClosestCentre(mission);

        this->list_groups[closest_centre.getId() - 1].addMission(mission);
    }
}

void GroupMaker::printGroups()
{
    for (int i = 0; i < this->nb_centres; i++) {
        this->list_groups[i].print();
    }
    
}

Centre GroupMaker::findClosestCentre(Mission mission)
{
    Centre closest_centre;
    float min_distance = 1000000;

    for (int i = 0; i < this->nb_centres; i++) {
        float distance = this->list_centres[i].getDistance(mission, this->nb_centres);
        if (distance < min_distance)
        {
            min_distance = distance;
            closest_centre = this->list_centres[i];
        }
    }
    
    return closest_centre;
}

