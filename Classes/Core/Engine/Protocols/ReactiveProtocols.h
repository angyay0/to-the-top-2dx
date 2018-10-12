//
//  ReactiveProtocols.h
//  ToTheTop
//
//  Created by Eduardo Pérez on 10/10/18.
//

#ifndef ReactiveProtocols_h
#define ReactiveProtocols_h

#include "GameObject.h"

class GameHUDClickProtocol {
public:
    virtual void onHUDItemClickedCallback(cocos2d::Ref *pSender) = 0;
};

class DyDClickProtocol {
public:
    virtual void onDyItemClickedCallback(cocos2d::Ref *pSender) = 0;
};

class GameObjectContainerProtocol {
private:
    cocos2d::Vector<GameObject*> gameObjects;
public:
    virtual void cleanGameObjects() = 0;
    virtual void createInitialGameObjects() = 0;
};
#endif /* ControlProtocols_h */
