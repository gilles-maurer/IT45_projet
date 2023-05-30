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


// SETTERS
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