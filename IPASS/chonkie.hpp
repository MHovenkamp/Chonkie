#ifndef CHONKIE_HPP
#define CHONKIE_HPP

#include "hwlib.hpp"
#include "library/colorSensor.hpp"
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
protected:
    enum class activities: char{
        drink   = 'D',
        eat     = 'E',
        sleep   = 'S',
        play    = 'P',
        empty   = 'X'
    };
    colorSensor sensor; 
    healthbar happiness;
    healthbar hunger;
    healthbar thirst;
    healthbar sleep;
    char activity;
    int hungerLevel;
    int thirstLevel;
    int sleepLevel;
    int happinessLevel;
public:
    
    lives( hwlib::target::pin_in & freq, hwlib::port_out & pins ):
        sensor( freq, pins ),
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
    char manageHealth();
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
    crosses leftEyeDeath;
    crosses rightEyeDeath;
    hwlib::circle mouth;
    bool left;
    bool mouthBool;
    bool drinkBool;
public:
    chonkie( hwlib::target::pin_in & freq , hwlib::port_out & pins, hwlib::glcd_oled & display, hwlib::xy coordinaat ):
        lives( freq, pins ),
        border( rectangle( display, 5 , 5 , 80, 60)),
        display( display ),
        coordinaat( coordinaat ),
        body( hwlib::circle( coordinaat, 20, hwlib::white)),
        leftEye( hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white)),
        rightEye( hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white)),
        leftPupil( hwlib::circle( hwlib::xy( coordinaat.x - 8, coordinaat.y), 2, hwlib::white)),
        rightPupil( hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white)),
        leftEyeDeath( display, coordinaat.x -10, coordinaat.y, coordinaat.x - 5, coordinaat.y + 5),
        rightEyeDeath( display, coordinaat.x + 5, coordinaat.y, coordinaat.x + 10, coordinaat.y + 5),
        mouth( hwlib::circle( hwlib::xy( coordinaat.x, coordinaat.y + 4), 5, hwlib::white))
    {}

    void print();
    void updateIdle();
    void animationCheck();
    bool deathCkeck();
    void death();
    void eat();
    void drink();
    void sleep();
};
#endif //CHONKIE_HPP