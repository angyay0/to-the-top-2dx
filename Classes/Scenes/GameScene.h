//
//  GameScene.h
//  3TGame
//
//  Created by Eduardo Pérez on 11/10/18.
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ReactiveProtocols.h"
#include "GameObject.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Constants.h"

USING_NS_CC;

class GameScene: public Scene,public GameHUDClickProtocol{
private:
    ParallaxLayer *parallaxMap;
    Player *player;
    GameObject *boardObject;
    PlayerHability learnedHab;
    bool isGameOver;
    bool isPaused;
    bool isOnRespawnTask;
    int level;
    
    //Functions
    void update(float dt);
    void buildLevel(bool respawn);
    void moveSpritesBlock(float dt);
    void cleanLevelElements(bool respawn);
    void solveCollisionFor(Node *player,Node *object);
    void displayView(int type);
public:
    static Scene *createScene();
    virtual bool init();
    bool createGameScene();
    
    virtual void onAcceleration(Acceleration *acc, Event *event);
    virtual void onHUDItemClickedCallback(cocos2d::Ref *pSender);
    virtual bool onContactBegin(PhysicsContact& contact);
    
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_h */
