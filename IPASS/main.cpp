#include "hwlib.hpp"
#include "library/freqMeasuringtool.hpp"
#include "chonkie.hpp"
#include "library/colorSensor.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________

int main( void ){
    hwlib::wait_ms(100);
    auto s0 = hwlib::target::pin_out( hwlib::target::pins::d2 );
    auto s1 = hwlib::target::pin_out( hwlib::target::pins::d3 );
    auto s2 = hwlib::target::pin_out( hwlib::target::pins::d4 );
    auto s3 = hwlib::target::pin_out( hwlib::target::pins::d5 );
    auto frequenty = hwlib::target::pin_in( hwlib::target::pins::d8 );  
    
    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
     
    auto pins = hwlib::port_out_from( s0, s1, s2, s3 );
    colorSensor sensor( frequenty , pins );
    chonkie baby( frequenty, pins , display, hwlib::xy(40,33));
    
    display.clear();
    bool death = false;
    for(;;){
        if( death == false ){
            display.clear(); //clear display
            baby.manageHealth(); //decline and restore health
            baby.set(); // set new health
            baby.draw( display ); //healtbars
            baby.print();   //print creature
            baby.animationCheck(); //move creature
            death = baby.deathCheck(); //check if dead
        }
        if( death ){
            display.clear();
            baby.death();
            baby.print();
            display.flush();
            break;
        }
        hwlib::wait_ms(500);
    }
}

