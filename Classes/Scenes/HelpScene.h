//
//  HelpScene.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef HelpScene_h
#define HelpScene_h

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class HelpScene: public Layer {
public:
    static Scene *createScene();
    virtual bool init();
    void onOptionSelectedCallback(Ref *pSender);
    
    CREATE_FUNC(HelpScene);
};

#endif /* HelpScene_h */
