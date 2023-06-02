#ifndef _MISSION_H
#define _MISSION_H

#include <string>

class Mission {
private:

    int id; 
    int id_skill; 
    int day; // valeur entre 1 et 7
    int start_period;
    int end_period;
    std::string skill; 
    std::string speciality; 

    float *distance;

public:
    Mission(int id, int day, int start_period , int end_period, std::string skill, std::string speciality);
    
    Mission();

    ~Mission();

    // GETTERS
    int getId();
    int getIdSkill();
    std::string getSkill();
    std::string getSpeciality();

    float getDistance(Mission mission, int nb_centres);

    int getDay();
    int getDuration();
    int getStart();
    int getEnd();

    // SETTERS
    void setIdSkill(int id_skill);
    void setDistance(float *distance);


    // METHODES
    void print();

};


#endif // _MISSION_H
