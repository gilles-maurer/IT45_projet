#ifndef _CENTRE_H
#define _CENTRE_H

#include <string>
#include "position.h"

class Centre {
private:

    int id;
    std::string name;

    Position position;

    int kmean_group;

public:
    Centre(/* args */);
    ~Centre();

    // GETTERS
    int getId();
    std::string getName();
    Position getPosition();
    int getKmeanGroup();





    // SETTERS
    void setKmeanGroup(int kmean_group);

};


#endif // _CENTRE_H