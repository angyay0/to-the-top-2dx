//
//  MovementProtocols.hpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

class SimpleMovementProtocol {
public:
    virtual void moveYAxis(float min,float max,float dt) = 0;
    virtual void moveXAxis(float min,float max,float dt) = 0;
};
