//
//  Simulation.h
//  carsystem
//
//  Created by Nero on 8/11/15.
//
//

#ifndef __carsystem__Simulation__
#define __carsystem__Simulation__

#include <cocos2d.h>

class InstrumentDial;

class Simulation : public cocos2d::Sprite
{
    typedef std::map<float,float> SimulationLv;
public:
    Simulation();
    CREATE_FUNC(Simulation);
    static Simulation* create(InstrumentDial* speed,InstrumentDial* rotate);
    virtual bool init() override;
    virtual void update(float delta) override;
    
    void speedUp();
    
    void speedDown();
    
    void addSimulateLv(float lv,float ratio);
    
    void setSimulateInfo(const float maxSpeed,const float maxRotate);
private:
    bool _speedUp;
    float _currentLv;
    InstrumentDial* _speed;
    InstrumentDial* _rotate;
    SimulationLv _simulationLv;
};

#endif /* defined(__carsystem__Simulation__) */
