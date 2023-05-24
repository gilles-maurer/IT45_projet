#include "mission.h"

using namespace std;


Mission::Mission(int id, int day, int hour_start, int hour_end, string competence, string speciality, Position position)
{
    this->id = id;
    this->day = day;
    this->hour_start = hour_start;
    this->hour_end = hour_end;
    this->competence = competence;
    this->speciality = speciality;
    this->position = position;
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