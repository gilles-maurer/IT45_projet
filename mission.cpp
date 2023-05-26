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
    
    this->kmean_group = -1;
}

Mission::Mission()
{
    this->id = -1;
    this->day = -1;
    this->start_period = -1;
    this->end_period = -1;
    this->skill = "";
    this->speciality = "";
    
    this->kmean_group = -1;
}

Mission::~Mission()
{
}


// SETTERS
void Mission::setKmeanGroup(int kmean_group)
{
    this->kmean_group = kmean_group;
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
    cout << "    Kmean group : " << this->kmean_group << endl;
}