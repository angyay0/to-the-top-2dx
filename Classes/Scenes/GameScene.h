//
//  GameScene.h
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "ReactiveProtocols.h"
#include "GameObject.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Constants.h"

USING_NS_CC;

class GameScene: public Scene,public GameHUDClickProtocol{
private:
    ParallaxLayer *parallax;
    Player *player;
    GameObject *boardObject;
    void update(float dt);
    
public:
    static Scene *createScene();
    virtual bool init();
    bool createGameScene();
    
    virtual void onAcceleration(Acceleration *acc, Event *event);
    virtual void onHUDItemClickedCallback(cocos2d::Ref *pSender);
    
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_h */
