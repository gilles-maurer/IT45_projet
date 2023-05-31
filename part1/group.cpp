#include "group.h"

using namespace std;


Group::Group()
{
    this->centre = Centre();
    this->list_missions = new Mission[0];
    this->nb_missions = 0;
}

Group::~Group()
{
}

// GETTERS
Centre Group::getCentre()
{
    return this->centre;
}

Mission *Group::getListMissions()
{
    return this->list_missions;
}

int Group::getNbMissions()
{
    return this->nb_missions;
}

// SETTERS

void Group::setCentre(Centre centre)
{
    this->centre = centre;
}

void Group::setListMissions(Mission *list_missions)
{
    this->list_missions = list_missions;
}

// METHODES

void Group::print()
{
    cout << "Groupe " << " : " << endl;
    cout << "Centre : " << this->centre.getName() << endl;
    cout << "Missions : " << endl;
    for (int i = 0; i < this->nb_missions; i++) {
        cout << "\t" << this->list_missions[i].getIdSkill() << endl;
    }
}

void Group::addMission(Mission mission)
{
    this->nb_missions++;
    Mission *new_list_missions = new Mission[this->nb_missions];

    for (int i = 0; i < this->nb_missions - 1; i++) {
        new_list_missions[i] = this->list_missions[i];
    }

    new_list_missions[this->nb_missions - 1] = mission;
    this->list_missions = new_list_missions;
}

