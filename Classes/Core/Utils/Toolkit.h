//
//  Toolkit.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef Toolkit_h
#define Toolkit_h

#include <stdio.h>
#include "Constants.h"

class Toolkit {
private:
    Toolkit(){};
    Toolkit(Toolkit const&){};
    Toolkit& operator = (Toolkit const&){};
    static Toolkit *instance;
public:
    static Toolkit *getInstance();
    int** getLevelMap(float level,GAME_DIFFICULTY dif,struct PlayerHability hab);
};
#endif /* Toolkit_h */
