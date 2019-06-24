#ifndef CHONKIE_HPP
#define CHONKIE_HPP

#include "hwlib.hpp"
#include "colorSensor.hpp"
#include "buildingBlocks.hpp"
#include "../../hwlib/library/hwlib.hpp"

class healthbar{
private:
    hwlib::xy start;
    int height = 10;
    int length = 30;
    int filled = 0;
public:
    healthbar( hwlib::xy start ):
        start( start )
    {};

    void draw( hwlib::glcd_oled & display );
    void setfilled( int value );
};

class lives{
public:
    colorSensor sensor; 
    healthbar happiness;
    healthbar hunger;
    healthbar thirst;
    healthbar sleep;
    int hungerLevel;
    int thirstLevel;
    int sleepLevel;
    int happinessLevel;
    
    lives( hwlib::target::pin_adc & freq, colorSensor & sensor ):
        sensor( freq, sensor ),
        happiness( healthbar( hwlib::xy( 95 , 5 ))),
        hunger( healthbar( hwlib::xy( 95 , 20 ))),
        thirst( healthbar( hwlib::xy( 95 , 35 ))),
        sleep( healthbar( hwlib::xy( 95 , 50 )))
    {   
        hungerLevel = 100;
        thirstLevel = 100;
        sleepLevel = 100;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }

    void draw( hwlib::glcd_oled & display );
    void set();
    void manageHealth();
};

class chonkie: public lives{
private:
    rectangle border;
    hwlib::glcd_oled & display;
    hwlib::xy coordinaat;
    hwlib::circle body;
    hwlib::circle leftEye;
    hwlib::circle rightEye;
    hwlib::circle leftPupil;
    hwlib::circle rightPupil;
    bool left;
    bool right;
public:
    chonkie( hwlib::target::pin_adc & freq , colorSensor & sensor, hwlib::glcd_oled & display, hwlib::xy coordinaat ):
        lives( freq, sensor ),
        border( rectangle( display, 5 , 5 , 80, 60)),
        display( display ),
        coordinaat( coordinaat ),
        body( hwlib::circle( coordinaat, 20, hwlib::white)),
        leftEye( hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white)),
        rightEye( hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white)),
        leftPupil( hwlib::circle( hwlib::xy( coordinaat.x - 8, coordinaat.y), 2, hwlib::white)),
        rightPupil( hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white))
    {}

    void print();
    void updateIdle();
    bool deathCkeck();
};
#endif //CHONKIE_HPP