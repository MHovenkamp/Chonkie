#include "hwlib.hpp"
#include "freqMeasure.hpp"
#include "chonkie.hpp"
#include "colorSensor.hpp"
//#include "../../hwlib/library/hwlib.hpp"

int main( void ){
    hwlib::wait_ms(100);
    auto s0 = hwlib::target::pin_out( hwlib::target::pins::d2 );
    auto s1 = hwlib::target::pin_out( hwlib::target::pins::d3 );
    auto s2 = hwlib::target::pin_out( hwlib::target::pins::d4 );
    auto s3 = hwlib::target::pin_out( hwlib::target::pins::d5 );
    auto frequenty = hwlib::target::pin_adc( hwlib::target::ad_pins::a5 );  
    
    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
     
    colorSensor sensor( frequenty , s0, s1, s2, s3 );
    lives levens( frequenty, sensor );
    chonkie baby( frequenty, sensor , display, hwlib::xy(40,33));
    
    display.clear();
    for(;;){
        // display.clear();
        // sensor.calculateRGB();
        // sensor.nameColorMode1();
        // hwlib::cout << sensor.getColor() << hwlib::endl;
        display.clear();
        levens.manageHealth();
        levens.set();
        levens.draw( display );
        baby.print();
        baby.updateIdle();
        display.flush();
        hwlib::wait_ms(500);
    }
}
