#ifndef CHONKIE_HPP
#define CHONKIE_HPP

#include "hwlib.hpp"
#include "library/colorSensor.hpp"
#include "buildingBlocks.hpp"
#include "../../hwlib/library/hwlib.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________


/// @file

/// \brief
/// healthbar ADT
/// \details
/// This is an ADT that controls a healtbar. It has an hwlib::xy and an int height, length and filled. It is dependend on the hwlib library.
/// https://github.com/wovo/hwlib

class healthbar{
private:
    hwlib::xy start;
    int height = 10;
    int length = 30;
    int filled = 0;
public:

    /// \brief
    /// healthbar() constructor
    /// \details
    /// This constructor creates an healtbar given an hwlib::xt start.
    healthbar( hwlib::xy start ):
        start( start )
    {};

    /// \brief
    /// draw() function
    /// \details
    /// This function draws a healtbar with the values height, length and the amount it is supposed to be filled. It has to be given a hwlib::glcd_oled window.
    void draw( hwlib::glcd_oled & display );

    /// \brief
    /// setfilled() function
    /// \details
    /// This function sets the filled value of the healtbar. It should be filled with a number on a scale of 0 to 100.
    void setfilled( int value );
};

/// @file

/// \brief
/// lives ADT
/// \details
/// This is an ADT that controls the lives of something. It has 4 healthbars and has a colorSensor. 
/// It also holds an activity that influences its health with the four Level ints.
/// It is dependand on the library hwlib.
/// https://github.com/wovo/hwlib
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

    /// \brief
    /// lives constructor
    /// \details
    /// This constructor needs the input of a hwlib::target::pin_in and a hwlib::port_out of 4 hwlib::port_out. It also sets the base level of hunger, thirst and sleep to full.
    /// hapiness is an average of hunger, thirst and sleep.
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

    /// \brief
    /// draw() function
    /// \details
    /// This function draws the four healtbars it has to be given a hwlib::glcd_oled window.
    void draw( hwlib::glcd_oled & display );

    /// \brief
    /// set() function
    /// \details
    /// This function sets the four healtbars with the health levels..
    void set();

    /// \brief
    /// manageHealth() function
    /// \details
    /// This function manages the health bars. it slowly decreases their values until the corresponding color is seen before the sensor. or darknesss is registered
    /// if the color is seen it wil increase the healt of that specific healtbar.
    /// Blue == Drinking
    /// Red == eating
    /// light < 1000 == sleeping
    char manageHealth();
};


/// @file

/// \brief
/// chonkie ADT: public lives
/// \details
/// This is an ADT that controls a little creature's animantions. It is dependant on the hwlib library
/// https://github.com/wovo/hwlib
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

    /// \brief
    /// chonkie constructor
    /// \details
    /// This constructor constructs a little creature using a hwlib::target::pin_in, hwlib::port_out consisting of 4 hwlib::port_out, hwlib::glcd_oled and an hwlib::xy
    /// it constructs a lives value and it creates some "bodyparts".
    chonkie( hwlib::target::pin_in & freq , hwlib::port_out & pins, hwlib::glcd_oled & display, hwlib::xy coordinaat ):
        lives( freq, pins ),
        border( rectangle( display, hwlib::xy( 5 , 5 ), hwlib::xy( 80, 60 ))),
        display( display ),
        coordinaat( coordinaat ),
        body( hwlib::circle( coordinaat, 20, hwlib::white)),
        leftEye( hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white)),
        rightEye( hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white)),
        leftPupil( hwlib::circle( hwlib::xy( coordinaat.x - 8, coordinaat.y), 2, hwlib::white)),
        rightPupil( hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white)),
        leftEyeDeath( display, hwlib::xy(coordinaat.x -10, coordinaat.y), hwlib::xy( coordinaat.x - 5, coordinaat.y + 5)),
        rightEyeDeath( display, hwlib::xy(coordinaat.x + 5, coordinaat.y), hwlib::xy( coordinaat.x + 10, coordinaat.y + 5)),
        mouth( hwlib::circle( hwlib::xy( coordinaat.x, coordinaat.y + 4), 5, hwlib::white))
    {}
    /// \brief
    /// print() function
    /// \details
    /// This function prints the border, body and the left and right eye.
    void print();

    /// \brief
    /// updateIdle() function
    /// \details
    /// This function makes the character look left and right if there is no other animation.
    void updateIdle();

    /// \brief
    /// animationCheck() function
    /// \details
    /// This function checks which animation to play and then plays it.
    void animationCheck();

    /// \brief
    /// deathCheck() function
    /// \details
    /// This function checks if the creature is "dead" if it is it ends the game and prints a dead creature.
    bool deathCheck();

    /// \brief
    /// death() function
    /// \details
    /// This function prints a dead creature.
    void death();

    /// \brief
    /// eat() function
    /// \details
    /// This function makes the character chew by creating a little mouth.
    void eat();

    /// \brief
    /// drink() function
    /// \details
    /// This function makes the character drink by flooding half the screen.
    void drink();

    /// \brief
    /// sleep() function
    /// \details
    /// This function makes the character sleep and sometimes open their eyes a little
    void sleep();
};
#endif //CHONKIE_HPP