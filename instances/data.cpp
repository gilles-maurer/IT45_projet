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

    if(file)
    {
        string line;
        int nb_missions = 0;

        while(getline(file, line))
        {
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
    return NULL;
}

Employe *Data::read_employes(int nb_employe)
{
    return NULL;
}


Centre *Data::read_centres(int nb_centre)
{
    return NULL;
}

