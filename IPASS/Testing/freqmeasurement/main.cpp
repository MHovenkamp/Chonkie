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

    s1.write(1);
    s1.flush();

    freqMeasuringtool test( frequenty );

    int value = 0;
    for(;;){
        value = test.read();
        hwlib::cout << value << hwlib::endl;
    }
}

