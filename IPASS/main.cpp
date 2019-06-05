#include "hwlib.hpp"


class healthbar{
private:
    hwlib::xy start;
    int height = 10;
    int length = 30;
    int filledpercentage = 100;
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
        filledpercentage = value;
        filled = (length * filledpercentage)/100;
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

int main( void ){	  
    namespace target = hwlib::target;
   
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
   
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
    auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
     
    display.clear();

    lives chonkie;
    chonkie.set(100, 20, 40, 80);
    chonkie.draw( display );


    for( uint16_t i = 0; i < display.size.y ; i++ ){
        display.write( hwlib::xy( 90, i ) );
    }
   display.flush();
}
