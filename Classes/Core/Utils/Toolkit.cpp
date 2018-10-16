//
//  Toolkit.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "Toolkit.h"

Toolkit *Toolkit::instance = NULL;

Toolkit *Toolkit::getInstance(){
    if (!instance){
        instance = new Toolkit;
    }    
    return instance;
}
