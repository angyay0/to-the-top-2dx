//
//  Player.hpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef Player_h
#define Player_h

#include "Character.h"
#include "MovementProtocols.h"

class Player: public Character, public SimpleMovementProtocol {
private:
    long score = 0;
    int lives = 0;
    long distance = 0;
    long _runningDistance = 0;
public:
    void setScore(long score);
    void setLives(int lives);
    void setDistance(long distance);
    void setDefaults();
    
    long getScore();
    long getDistance();
    int getLives();
    
    void moveYAxis(float min,float max,float dt);
    void moveXAxis(float min,float max,float dt);
};
#endif
