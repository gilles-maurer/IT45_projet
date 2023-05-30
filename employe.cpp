#include "employe.h"
#include <iostream>


using namespace std;


Employe::Employe()
{
    this->id = -1; 
    this->centre_id = -1;
    this->skill = "";
    this->speciality = "";
}

Employe::Employe(int id, int centre_id, string skill, string speciality)
{
    this->id = id;
    this->centre_id = centre_id;
    this->skill = skill;
    this->speciality = speciality;
}

Employe::~Employe()
{
}


// GETTERS
int Employe::getId()
{
    return this->id;
}

int Employe::getCentreId()
{
    return this->centre_id;
}

string Employe::getSkill()
{
    return this->skill;
}

// METHODES
void Employe::print()
{
    cout << "Employe " << this->id << " : " << endl;
    cout << "    centre_id : " << this->centre_id << endl;
    cout << "    skill : " << this->skill << endl;
    cout << "    speciality : " << this->speciality << endl;
}


