//
//  MainMenuScene.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef MainMenuScene_h
#define MainMenuScene_h

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class MainMenuScene: public Layer {
public:
    static cocos2d::Scene *createScene();
    virtual bool init();    
    void onOptionSelectedCallback(Ref *pSender);
    
    CREATE_FUNC(MainMenuScene);
};

#endif /* MainMenuScene_h */
