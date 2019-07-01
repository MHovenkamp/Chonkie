#include "hwlib.hpp"
#include "../../library/freqMeasuringtool.hpp"
#include "../../library/colorSensor.hpp"

int main( void ){
    hwlib::wait_ms(500);

    auto s0 = hwlib::target::pin_out( hwlib::target::pins::d2 );
    auto s1 = hwlib::target::pin_out( hwlib::target::pins::d3 );
    auto s2 = hwlib::target::pin_out( hwlib::target::pins::d4 );
    auto s3 = hwlib::target::pin_out( hwlib::target::pins::d5 );
    auto frequenty = hwlib::target::pin_in( hwlib::target::pins::d8 );       
    int value = 0;

    auto pins = hwlib::port_out_from( s0, s1, s2, s3 );
    freqMeasuringtool test( frequenty );
    colorSensor sensor( frequenty , pins );

    for(;;){
        hwlib::wait_ms(500);
        sensor.calculateRGB();
        sensor.nameColorMode2();
        sensor.printRGB();
        value = test.read();
        hwlib::cout << value << hwlib::endl;
    }
}

