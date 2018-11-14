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
    float currentHealth;
    long currentScore;
    long currentDistance;
    long score;
    int lives;
    long distance;
public:
    PlayerHability playerHab;
    
    void setScore(long score);
    void setLives(int lives);
    void setDistance(long distance);
    void setDefaults();
    void resetLiveLose();
    
    void calculateDamage(float damage);
    void calculateScore(float score);
    
    long getScore();
    long getDistance();
    int getLives();
    float getCurrentHealth();
    
    void moveYAxis(float min,float max,float dt);
    void moveXAxis(float min,float max,float dt);
};
#endif
