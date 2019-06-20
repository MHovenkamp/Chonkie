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
        std::array<uint_fast32_t, 30> testsamples;
        for(unsigned int i = 0; i < 30; i++){
            testsamples[i] = pin.read();
        }
        uint_fast32_t high = 0;
        for(unsigned int j = 0; j < 30; j++){
            if( testsamples[j] > high ){
                high = testsamples[j];
            }
        }
        while(pin.read() < high);
        while(pin.read() == high);
        t1 = hwlib::now_us();
        while(pin.read() < high);
        while(pin.read() == high);
        t2 = hwlib::now_us();
    }

    int calculate(){
        uint_fast64_t duration = t2-t1;
        frequenty = duration;
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
    char color = 'X';
public:
    colorSensor( hwlib::target::pin_adc & freq, hwlib::target::pin_out & s0, hwlib::target::pin_out & s1, hwlib::target::pin_out & s2, hwlib::target::pin_out & s3 ):
        freqMeasure( freq ),
        s0( s0 ),
        s1( s1 ),
        s2( s2 ),
        s3( s3 )
    {s0.write(0);
    s1.write(1);}

    void setRed(){
        s2.write(0);
        s3.write(0);
        flush();
    }

    void setGreen(){
        s2.write(1);
        s3.write(1);
        flush();
    }

    void setBlue(){
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

    int calculatecolor(){
        const int sampleSize = 25;
        std::array<int,sampleSize> samples;
        for (unsigned int i = 0; i < sampleSize; i++){
            sample();
            samples[i]= calculate();
        }
        int value = 0;
        for (unsigned int j = 0; j < sampleSize; j++){
            value += samples[j];
        }
        return value/sampleSize;
    }

    void calculateRGB(){
        //red
        setRed();
        flush();
        red = calculatecolor();
        //Green
        setGreen();
        flush();
        green = calculatecolor();
        //Blue
        setBlue();
        flush();
        blue = calculatecolor();
        easyUp();
    }

    void easyUp(){
        hwlib::cout << "_______________________________" << hwlib::endl;
        int highest = red;
        int lowest = blue;
        int last = 0;
        if( red > green && red > blue ){
            highest = red;
        }
        if( green > red && green > blue ){
            highest = green;
        }
        if( blue > green && blue > red ){
            highest = blue;
        }
        if( red < green && red < blue ){
            lowest = red;
        }
        if( green < red && green < blue ){
            lowest = green;
        }
        if( blue < green && blue < red ){
            lowest = blue;
        }
        while( lowest > 0 ){
            red = red/2;
            green = green/2;
            blue = blue/2;
            if( red < green && red < blue ){
                lowest = red;
            }
            if( green < red && green < blue ){
                lowest = green;
            }
            if( blue < green && blue < red ){
                lowest = blue;
            }
            if( red > green && red > blue ){
                highest = red;
            }   
            if( green > red && green > blue ){
                highest = green;
            }
            if( blue > green && blue > red ){
                highest = blue;
            }
            if (lowest == last || highest < 255){
                break;
            }
            last = lowest;
        }   
    }

    void printRGB(){
        hwlib::cout << "Red: " << red << hwlib::endl;
        hwlib::cout << "Green: " << green << hwlib::endl;
        hwlib::cout << "Blue: " << blue << hwlib::endl;
        hwlib::cout << "Color " << color << hwlib::endl;
    }

    void nameColor(){
        std::array<int,2> zone1 = {0,32};
        std::array<int,2> zone2 = {32,64};
        std::array<int,2> zone3 = {64,96};
        std::array<int,2> zone4 = {96,128};
        std::array<int,2> zone5 = {128,160};
        std::array<int,2> zone6 = {160,192};
        std::array<int,2> zone7 = {192,224};
        std::array<int,2> zone8 = {224,255};
        std::array<std::array<int,2>,8> zones = {zone1, zone2, zone3, zone4, zone5, zone6, zone7, zone8};
        int redZone = 0;
        int greenZone = 0;
        int blueZone = 0;
        for( unsigned int i = 0; i < 8; i++ ){
            if( red >= zones[i][0] && red <= zones[i][1]){
                redZone = i+1;
            }
            if( green >= zones[i][0] && green <= zones[i][1]){
                greenZone = i+1;
            }
            if( blue >= zones[i][0] && blue <= zones[i][1]){
                blueZone = i+1;
            }
        }
        if( redZone == 2 || redZone == 3 ){
            if( greenZone == 5 || greenZone == 6 ){
                if( blueZone == 2 || blueZone == 3 ){
                    color = 'R';
                }
            }
        }
        if( redZone == 6 || redZone == 7 ){
            if( greenZone == 5 || greenZone == 6 ){
                if( blueZone == 4 || blueZone == 5 ){
                    color = 'G';
                }
            }
        }
        if( redZone == 5 || redZone == 6 ){
            if( greenZone == 4 || greenZone == 5 ){
                if( blueZone == 2 || blueZone == 3 ){
                    color = 'B';
                }
            }
        }
        if( redZone == 5 || redZone == 6 ){
            if( greenZone == 6 || greenZone == 7 ){
                if( blueZone == 7 || blueZone == 8 ){
                    color = 'Y';
                }
            }
        }
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
    for(;;){
        sensor.calculateRGB();
        sensor.nameColor();
        sensor.printRGB();
    }
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

