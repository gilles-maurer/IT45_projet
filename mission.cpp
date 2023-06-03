#include "mission.h"
#include <iostream>

using namespace std;



Mission::Mission(int id, int day, int start_period, int end_period,string skill, string speciality)
{
    this->id = id;
    this->day = day;
    this->start_period = start_period;
    this->end_period = end_period;
    this->skill = skill;
    this->speciality = speciality;
 
    this->id_skill = -1;
}

Mission::Mission()
{
    this->id = -1;
    this->day = -1;
    this->start_period = -1;
    this->end_period = -1;
    this->skill = "";
    this->speciality = "";
}

Mission::~Mission()
{
}

// GETTERS
int Mission::getId()
{
    return this->id;
}

int Mission::getIdSkill()
{
    return this->id_skill;
}

string Mission::getSkill()
{
    return this->skill;
}

string Mission::getSpeciality()
{
    return this->speciality;
}

float Mission::getDistance(Mission mission, int nb_centres)
{
    cout << "distance" << endl;
    return this->distance[mission.getId() + nb_centres - 1];
}

int Mission::getDay()
{
    return this->day;
}

int Mission::getDuration()
{
    return (this->end_period - this->start_period) / 60;
}

int Mission::getStart()
{
    return this->start_period / 60;
}

int Mission::getEnd()
{
    return this->end_period / 60;
}

// SETTERS
void Mission::setIdSkill(int id_skill)
{
    this->id_skill = id_skill;
}

void Mission::setDistance(float *distance)
{
    this->distance = distance;
}

// METHODES
void Mission::print()
{
    cout << "Mission " << this->id << " : " << endl;
    cout << "    Day : " << this->day << endl;
    cout << "    Start period : " << this->start_period << endl;
    cout << "    End period : " << this->end_period << endl;
    cout << "    Skill : " << this->skill << endl;
    cout << "    Speciality : " << this->speciality << endl;
}