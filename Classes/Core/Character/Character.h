//
//  Character.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "GameObject.h"
#include <stdio.h>

class Character:public GameObject {
protected:
    int points;
public:
    virtual bool initWith(const std::string &sprite,struct GOAttributes attributes);
    void setPoints(int points);
    int getPoints();
};
