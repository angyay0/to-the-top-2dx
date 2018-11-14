//
//  DynDLayer.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

#ifndef DynDLayer_h
#define DynDLayer_h

#include "cocos2d.h"
#include <stdio.h>
#include "ReactiveProtocols.h"

USING_NS_CC;

typedef enum {
    _PauseLayer,
    _WinLayer,
    _GameOverLayer,
    _GeneralMessageLayer,
    _InteractiveMessageLayer
} DDLayerType;

class DynDLayer: public cocos2d::LayerColor {
private:
    DDLayerType type;
    DyDClickProtocol *clickHandler;
    void configurePause();
    void configureGOver();
    void configureWinner();
public:
    virtual bool init();
    void setupFor(DDLayerType type,std::string data[]);
    void setupInteraction(DyDClickProtocol *handler);
    void updateDyDLayer(float dt);
    
    void onClick(Ref *pSender);
    
    CREATE_FUNC(DynDLayer);
};

#endif /* DynDLayer_h */
