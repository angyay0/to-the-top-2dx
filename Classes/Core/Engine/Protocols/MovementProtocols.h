//
//  MovementProtocols.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

#ifndef MovementProtocols_h
#define _MovementProtocols_h

//Accelerometer Constants
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.6
#define KRESTACCELY -0.25
#define KRESTACCELZ -0.40
#define KMAXDIFFX 0.20
#define KADJUSTSIDE 1.95
#define KGRAVITYFACTOR 9.8

class SimpleMovementProtocol {
public:
    virtual void moveYAxis(float min,float max,float dt) = 0;
    virtual void moveXAxis(float min,float max,float dt) = 0;
};
#endif
