#include <chrono>
#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

class freqMeasure{
protected: 
    int frequenty;
    uint_fast64_t t1;
    uint_fast64_t t2;
public:
    hwlib::target::pin_adc pin;
    freqMeasure( hwlib::target::pin_adc & pin ):
        pin( pin )
    {}
    freqMeasure( freqMeasure & rhs ):
        pin( rhs.pin )
    {}
    void sample(){
        while(pin.read() < 4095);
        while(pin.read() == 4095);
        t1 = hwlib::now_us();
        while(pin.read() < 4095);
        while(pin.read() == 4095);
        t2 = hwlib::now_us();
    }

    int calculate(){
        uint_fast64_t duration = t2-t1;
        hwlib::cout << "duration" << duration << hwlib::endl;
        int freqS = 1000000/duration;
        frequenty = freqS;
        hwlib::cout << "Frequenty: " << frequenty << hwlib::endl;
        return frequenty;
    }
};

class colorSensor: public freqMeasure{
private:
    hwlib::target::pin_out s0;
    hwlib::target::pin_out s1;
    hwlib::target::pin_out s2;
    hwlib::target::pin_out s3;
    int red = 0;
    int green = 0;
    int blue = 0;
public:
    colorSensor( hwlib::target::pin_adc & freq, hwlib::target::pin_out & s0, hwlib::target::pin_out & s1, hwlib::target::pin_out & s2, hwlib::target::pin_out & s3 ):
        freqMeasure( freq ),
        s0( s0 ),
        s1( s1 ),
        s2( s2 ),
        s3( s3 )
    {}
    void calculateRGB(){
        //red
        setRed();
        flush();
        sample();
        red = calculate();
        //Green
        setGreen();
        flush();
        sample();
        green = calculate();
        //Blue
        setBlue();
        flush();
        sample();
        blue = calculate();
    }
    void setRed(){
        s0.write(1);
        s1.write(1);
        s2.write(0);
        s3.write(0);
        flush();
    }
    void setGreen(){
        s0.write(1);
        s1.write(1);
        s2.write(1);
        s3.write(1);
        flush();
    }
    void setBlue(){
        s0.write(1);
        s1.write(1);
        s2.write(0);
        s3.write(1);
        flush();
    }
    void flush(){
        s0.flush();
        s1.flush();
        s2.flush();
        s3.flush();
    }
};


int main( void ){
    hwlib::wait_ms(100);
    auto s0 = hwlib::target::pin_out( hwlib::target::pins::d2 );
    auto s1 = hwlib::target::pin_out( hwlib::target::pins::d3 );
    auto s2 = hwlib::target::pin_out( hwlib::target::pins::d4 );
    auto s3 = hwlib::target::pin_out( hwlib::target::pins::d5 );
    auto frequenty = hwlib::target::pin_adc( hwlib::target::ad_pins::a5 );
    //freqMeasure pinIn( frequenty );
    colorSensor sensor( frequenty , s0, s1, s2, s3 );
    hwlib::cout << "red" << hwlib::endl;
    sensor.setRed();
    sensor.sample();
    sensor.calculate();
    hwlib::cout << "green" << hwlib::endl;
    sensor.setGreen();
    sensor.sample();
    sensor.calculate();
    hwlib::cout << "blue" << hwlib::endl;
    sensor.setBlue();
    sensor.sample();
    sensors.calculate();
}



// class healthbar{
// private:
//     hwlib::xy start;
//     int height = 10;
//     int length = 30;
//     int filled = 0;
// public:
//     healthbar( hwlib::xy start ):
//         start( start )
//     {};

//     void draw( hwlib::glcd_oled & display ){
//         //top lines
//         for(uint16_t i = 0; i <= length; i++){
//             display.write( hwlib::xy( start.x + i, start.y ) );
//             display.write( hwlib::xy( start.x + i, start.y + height ) );
//         }
//         //side lines
//         for(uint16_t j = 0; j <= height; j++){
//             display.write( hwlib::xy( start.x , start.y+ j ) );
//             display.write( hwlib::xy( start.x + length , start.y + j ) );
//         }
//         //filled parts
//         for(uint16_t y = start.y; y < start.y + height; y++){
//             for(uint16_t x = start.x; x < start.x + filled; x++){
//                 display.write( hwlib::xy( x , y ) );
//             }
//         }
//     }

//     void setfilled( int value ){
//         filled = (length * value)/100;
//         hwlib::cout << filled << hwlib::endl;
//     }
// };

// class lives{
// public:
//     healthbar happiness;
//     healthbar hunger;
//     healthbar thirst;
//     healthbar sleep;
    
//     lives():
//         happiness( healthbar( hwlib::xy( 95 , 5 ))),
//         hunger( healthbar( hwlib::xy( 95 , 20 ))),
//         thirst( healthbar( hwlib::xy( 95 , 35 ))),
//         sleep( healthbar( hwlib::xy( 95 , 50 )))
//     {}

//     void draw( hwlib::glcd_oled & display ){
//         happiness.draw( display );
//         hunger.draw( display );
//         thirst.draw( display );
//         sleep.draw( display );
//     }

//     void set( int happinessLevel, int hungerLevel, int thirstLevel, int sleepLevel ){
//         happiness.setfilled( happinessLevel );
//         hunger.setfilled( hungerLevel );
//         thirst.setfilled( thirstLevel );
//         sleep.setfilled( sleepLevel );
//     }
// };


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

// }

