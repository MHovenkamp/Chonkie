#ifndef colorSensor_HPP
#define colorSensor_HPP

#include "hwlib.hpp"
#include "freqMeasure.hpp"
#include "../../hwlib/library/hwlib.hpp"

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
    
    char getColor();
    std::array<int, 3> getRGB();
    void setRed();
    void setGreen();
    void setBlue();
    void flush();
    int calculateColor();
    void calculateRGB();
    void shrinkValueRGB();
    void printRGB();
    void nameColorMode1();
    void nameColorMode2();
};
#endif //COLORSENSOR_HPP