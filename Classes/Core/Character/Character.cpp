//
//  Character.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "Character.h"

void Character::setPoints(int points){
    auto attributes = this->getAttributes();
    attributes.canInteract = true;
    attributes.canProvidePoints = true;
    attributes.points = points;
}

