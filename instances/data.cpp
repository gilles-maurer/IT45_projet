#include "data.h"
#include <iostream>
#include <fstream>

using namespace std;

Data::Data(/* args */)
{
}

Data::Data(std::string repo)
{
    this->repo = repo;
}

Data::~Data()
{
}


// METHODES

int Data::count_lines(string file_name)
{

    string full_file_name = this->repo + file_name;
    ifstream file(full_file_name.c_str(), ios::in);

    if(file) {
        string line;
        int nb_missions = 0;

        while(getline(file, line)) {
            nb_missions++;
        }

        file.close();

        return nb_missions;
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return -1;
    }

}

Mission *Data::read_missions(int nb_missions)
{

    Mission *list_mission = new Mission[nb_missions];

    string full_file_name = this->repo + "missions.csv";
    ifstream file(full_file_name.c_str(), ios::in);

    if(file) {

        string line;
        int i = 0;


        while(getline(file, line)) {

            cout << line << endl;

            int id, day, start_period, end_period;
            string skill, speciality; 

            // line = "id,day,start_period,end_period,skill,speciality"

            id = read_int_from_line(line);
            day = read_int_from_line(line);
            start_period = read_int_from_line(line);
            end_period = read_int_from_line(line);
            
            skill = read_string_from_line(line);
            speciality = read_string_from_line(line);

            Mission new_mission(id, day, start_period, end_period, skill, speciality);

            list_mission[i] = new_mission;

            i++;

        }

    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return NULL;
    }

    return list_mission;    
}

Employe *Data::read_employes(int nb_employe)
{
    Employe *list_employe = new Employe[nb_employe];

    string full_file_name = this->repo + "employees.csv";
    ifstream file(full_file_name.c_str(), ios::in);

    if(file) {

        string line;
        int i = 0;

        while(getline(file, line)) {

            cout << line << endl;

            int id, center_id;
            string skill, speciality; 

            // line = "id,center_id,skill,speciality"

            id = read_int_from_line(line);
            center_id = read_int_from_line(line);
            
            skill = read_string_from_line(line);
            speciality = read_string_from_line(line);

            Employe new_employe(id, center_id, skill, speciality);

            list_employe[i] = new_employe;

            i++;

        }

    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return NULL;
    }

    return list_employe; 
}


Centre *Data::read_centres(int nb_centre)
{

    Centre *list_centre = new Centre[nb_centre];

    string full_file_name = this->repo + "centres.csv";
    ifstream file(full_file_name.c_str(), ios::in);

    if(file) {

        string line;
        int i = 0;

        while(getline(file, line)) {

            cout << line << endl;

            int id;
            string name; 

            // line = "id,name"

            id = read_int_from_line(line);
            name = read_string_from_line(line);

            Centre new_centre(id, name);

            list_centre[i] = new_centre;

            i++;

        }

    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return NULL;
    }

    return list_centre;

}

float **Data::read_distance(int nb_missions, int nb_centres) {

    float **distance = new float*[nb_missions+nb_centres];

    for(int i = 0; i < nb_missions+nb_centres; i++) {
        distance[i] = new float[nb_missions+nb_centres];
    }

    string full_file_name = this->repo + "distances.csv";
    ifstream file(full_file_name.c_str(), ios::in);

    if(file) {

        string line;
        int i = 0;

        while(getline(file, line)) {
            
            for (int j = 0; j < nb_missions+nb_centres; j++){
            
                distance[i][j] = read_float_from_line(line);
            }

            i++;

        }

    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return NULL;
    }

    return distance;

}

int Data::read_int_from_line(string &line) 
{
    int index = line.find(",");
    int result = stoi(line.substr(0, index));
    line = line.substr(index + 1);

    return result;
}

float Data::read_float_from_line(string &line)
{
    int index = line.find(",");
    float result = stof(line.substr(0, index));
    line = line.substr(index + 1);

    return result;
}

string Data::read_string_from_line(string &line)
{
    int index = line.find(",");
    string result = line.substr(0, index);
    line = line.substr(index + 1);

    return result;
}


