//
//  ControlProtocols.h
//  ToTheTop
//
//  Created by Eduardo Pérez on 10/10/18.
//

#ifndef ReactiveProtocols_h
#define ReactiveProtocols_h

class GameHUDClickProtocol {
public:
    virtual void onHUDItemClickedCallback(cocos2d::Ref *pSender) = 0;
};

class DyDClickProtocol {
public:
    virtual void onDyItemClickedCallback(cocos2d::Ref *pSender) = 0;
};

#endif /* ControlProtocols_h */
