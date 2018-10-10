//
//  DynDLayer.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

#ifndef DynDLayer_h
#define DynDLayer_h

#include "cocos2d.h"
#include "ReactiveProtocols.h"

USING_NS_CC;

typedef enum {
    _PauseLayer,
    _GOLayer,
    _GMLayer,
    _IMLayer
} DDLayerType;

class DynDLayer: public cocos2d::Layer {
private:
    DDLayerType type;
    DyDClickProtocol *clickHandler;
public:
    virtual bool init();
    void setupFor(DDLayerType type);
    void setupInteraction(DyDClickProtocol *handler);
    void updateDyDLayer(float dt);
    
    void onClick(Ref *pSender);
    
    CREATE_FUNC(DynDLayer);
};

#endif /* DynDLayer_h */
