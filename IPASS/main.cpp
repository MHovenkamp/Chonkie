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
     
    display.clear();

    lives chonkie;
    //freqMeasure pinIn( frequenty );
    colorSensor sensor( frequenty , s0, s1, s2, s3 );
    char x;
    int hap = 100;
    int hunger = 80;
    int thirst = 80;
    int sleep = 80;
    for(;;){
        hunger--;
        thirst--;
        sleep--;
        hwlib::cout << "hunger " << hunger << hwlib::endl;
        chonkie.set(hap, hunger, thirst, sleep);
        chonkie.draw( display );
        display.flush();
        hwlib::wait_ms(500);
        sensor.calculateRGB();
        sensor.nameColorMode1();
        sensor.printRGB();
        hwlib::cin >> x;
        if( x == 'N'){
            break;
        }
    }
}






// int main( void ){	
//     namespace target = hwlib::target;
   
//     auto scl = target::pin_oc( target::pins::scl );
//     auto sda = target::pin_oc( target::pins::sda );
   
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
//     auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
     
//     display.clear();

//     lives chonkie;
//     // chonkie.set(100, 20, 40, 80);
//     // chonkie.draw( display );


//     for( uint16_t i = 0; i < display.size.y ; i++ ){
//         display.write( hwlib::xy( 90, i ) );
//     }
//    //display.flush();
//     int hap = 100;
//     int hunger = 80;
//     int thirst = 80;
//     int sleep = 80;
//     while(true){
//         hunger--;
//         thirst--;
//         sleep--;
//         hwlib::cout << "hunger " << hunger << hwlib::endl;
//         chonkie.set(hap, hunger, thirst, sleep);
//         chonkie.draw( display );
//         display.flush();
//         hwlib::wait_ms(500);
//     }

//}
