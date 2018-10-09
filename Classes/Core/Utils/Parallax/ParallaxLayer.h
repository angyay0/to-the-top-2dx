//
//  ParallaxLayer.hpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "cocos2d.h"

class ParallaxLayer: public cocos2d::ParallaxNode {
public:
    static ParallaxLayer *create();
    void updateLayer();
};
