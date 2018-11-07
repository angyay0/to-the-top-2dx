//
//  ParallaxLayer.hpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef ParallaxLayer_h
#define ParallaxLayer_h

#define HORIZONTAL_MOVEMENT 0
#define VERTICAL_MOVEMENT 1

#define STANDALONE_PARALLAX_SPRITE_1 20
#define STANDALONE_PARALLAX_SPRITE_2 21

#include "cocos2d.h"

class ParallaxLayer: public cocos2d::ParallaxNode {
private:
    bool removeAfterRoll;
    bool stopAtEndRoll;
    float bg_min_spd;
    float bg_max_spd;
    float min_factor_spd;
    float max_factor_spd;
    float pfactor;
    float pdistance;
    int orientation;
    cocos2d::Point point;
public:
    static ParallaxLayer *create();
    void updateLayer();
    void setupMovementFactor(float bg_min_spd,float bg_max_spd,float min_factor_spd,float max_factor_spd,float factor,float distance,int orientation);
    void setupBehavior(bool remove,bool stop);
    void move(float dt);
    cocos2d::Point getPointSpeed();
};
#endif
