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

    auto pins = hwlib::port_out_from( s0, s1, s2, s3 );
    freqMeasuringtool test( frequenty );
    colorSensor sensor( frequenty , pins );

    for(;;){
        hwlib::wait_ms(500);
        hwlib::cout << "START MEASUREMENT" << hwlib::endl;
        sensor.calculateRGB();
        sensor.calculatelightIntensity();
        sensor.nameColorMode2();
        sensor.printRGB();
        hwlib::cout << "END MEASUREMENT" << hwlib::endl;
    }
}

