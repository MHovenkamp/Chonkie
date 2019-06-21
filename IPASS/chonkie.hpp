#ifndef CHONKIE_HPP
#define CHONKIE_HPP

#include "hwlib.hpp"
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

    void draw( hwlib::glcd_oled & display ){
        //top lines
        for(uint16_t i = 0; i <= length; i++){
            display.write( hwlib::xy( start.x + i, start.y ) );
            display.write( hwlib::xy( start.x + i, start.y + height ) );
        }
        //side lines
        for(uint16_t j = 0; j <= height; j++){
            display.write( hwlib::xy( start.x , start.y+ j ) );
            display.write( hwlib::xy( start.x + length , start.y + j ) );
        }
        //filled parts
        for(uint16_t y = start.y; y < start.y + height; y++){
            for(uint16_t x = start.x; x < start.x + filled; x++){
                display.write( hwlib::xy( x , y ) );
            }
        }
    }

    void setfilled( int value ){
        filled = (length * value)/100;
        hwlib::cout << filled << hwlib::endl;
    }
};

class lives{
public:
    healthbar happiness;
    healthbar hunger;
    healthbar thirst;
    healthbar sleep;
    
    lives():
        happiness( healthbar( hwlib::xy( 95 , 5 ))),
        hunger( healthbar( hwlib::xy( 95 , 20 ))),
        thirst( healthbar( hwlib::xy( 95 , 35 ))),
        sleep( healthbar( hwlib::xy( 95 , 50 )))
    {}

    void draw( hwlib::glcd_oled & display ){
        happiness.draw( display );
        hunger.draw( display );
        thirst.draw( display );
        sleep.draw( display );
    }

    void set( int happinessLevel, int hungerLevel, int thirstLevel, int sleepLevel ){
        happiness.setfilled( happinessLevel );
        hunger.setfilled( hungerLevel );
        thirst.setfilled( thirstLevel );
        sleep.setfilled( sleepLevel );
    }
};

#endif //CHONKIE_HPP