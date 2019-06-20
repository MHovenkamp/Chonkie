#ifndef colorSensor_HPP
#define colorSensor_HPP

#include "hwlib.hpp"
#include "freqMeasure.hpp"
#include "../../hwlib/library/hwlib.hpp"

class colorSensor: public freqMeasure{
private:
    std::array<int,2> zone1 = {0,32};
    std::array<int,2> zone2 = {32,64};
    std::array<int,2> zone3 = {64,96};
    std::array<int,2> zone4 = {96,128};
    std::array<int,2> zone5 = {128,160};
    std::array<int,2> zone6 = {160,192};
    std::array<int,2> zone7 = {192,224};
    std::array<int,2> zone8 = {224,255};
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

    void setRed();
    void setGreen();
    void setBlue();
    void flush();
    int calculateColor();
    void calculateRGB();
    void shrinkValueRGB();
    void printRGB();
    void nameColor();
};
#endif //COLORSENSOR_HPP