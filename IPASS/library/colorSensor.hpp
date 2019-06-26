#ifndef colorSensor_HPP
#define colorSensor_HPP

#include "hwlib.hpp"
#include "freqMeasuringtool.hpp"
#include "../../hwlib/library/hwlib.hpp"


/// @file

/// \brief
/// colorSensor ADT
/// \details
/// This is an ADT that gives the user RGB values of colors. the RGB values are stored seperately as integers.
/// The RGB values do not match the standard RGB codes.
/// This ADT can also give the name of a few colors with two different modes as a char and is stored as a char. 
/// If a char is used multiple times the primary color is capitalized and the secundary color lowercase.
/// this ADT is reliant on hwlb and freqMeasuringtool.
class colorSensor: public freqMeasuringtool{
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
    /// \brief
    /// colorSensor constructor.
    /// \details
    /// This constructor construct the colorSensor with the intput of an hwlib::target::pin_acd and four hwlib::target::pin_out. 
    /// It also sets the frequenty scaling to 2%.
    colorSensor( hwlib::target::pin_adc & freq, hwlib::target::pin_out & s0, hwlib::target::pin_out & s1, hwlib::target::pin_out & s2, hwlib::target::pin_out & s3 ):
        freqMeasuringtool( freq ),
        s0( s0 ),
        s1( s1 ),
        s2( s2 ),
        s3( s3 )
    {s0.write(0);
    s1.write(1);}
    /// \brief
    /// colorSensor constructor with other colorSensor.
    /// \details
    /// This constructor construct the colorSensor with the intput of an hwlib::target::pin_acd and an other colorSensor. 
    /// It also sets the frequenty scaling to 2%.
    colorSensor( hwlib::target::pin_adc & freq, colorSensor & rhs ):
        freqMeasuringtool( freq ),
        s0( rhs.s0 ),
        s1( rhs.s1 ),
        s2( rhs.s2 ),
        s3( rhs.s3 )
    {s0.write(0);
    s1.write(1);}
    
    /// \brief
    /// getColor() function.
    /// \details
    /// This function returns the color as a char.
    char getColor();

    /// \brief
    /// getRGB() function.
    /// \details
    /// This function returns the RGB values as an array of integers int the order red, green, blue.
    std::array<int, 3> getRGB();

    /// \brief
    /// setRed() function.
    /// \details
    /// This function sets the color sensor to read red values and flushes the sensor.
    void setRed();

    /// \brief
    /// setGreen() function.
    /// \details
    /// This function sets the color sensor to read green values and flushes the sensor.
    void setGreen();

    /// \brief
    /// setBlue() function.
    /// \details
    /// This function sets the color sensor to read blue values and flushes the sensor.
    void setBlue();

    /// \brief
    /// setClear() function.
    /// \details
    /// This function sets the color sensor to read clear values and flushes the sensor.
    void setClear();

    /// \brief
    /// flush() function.
    /// \details
    /// This function flushes the chosen settings to the sensor.
    void flush();

    /// \brief
    /// calculateColor() function.
    /// \details
    /// This function takes 25 samples of a single color and takes the average frequenty and returns this as an int.
    int calculateColor();

    /// \brief
    /// calculateRGB() function.
    /// \details
    /// This function sets the three integers corresponding with the colors red, green and blue using the calculateColor function.
    void calculateRGB();

    /// \brief
    /// shrinkValueRGB() function.
    /// \details
    /// this function shrinks the integers red, green and blue integers until their maximum value is 255 or the lowest value becomes 0.
    void shrinkValueRGB();

    /// \brief
    /// printRGB() function.
    /// \details
    /// This function prints the red, green and blue values to the terminal.
    void printRGB();

    /// \brief
    /// nameColorMode1() function.
    /// \details
    /// This function fils the color char with either the color red, green or blue. It is consistent but can be influenced bij ambient light.
    /// If the color in front of the sensor cannot be defined as red, green or blue the color will be filled with an 'X'.
    /// red = 'R
    /// green = 'G'
    /// blue = 'B'
    void nameColorMode1();

    /// \brief
    /// nameColorMode2() function.
    /// \details
    /// This function fils the color char with either the color red, green, blue, brown, yellow, orange or pink. 
    /// It is not very consistent and can be influenced bij ambient light.
    /// If the color in front of the sensor cannot be defined as one of the colors the color will be filled with an 'X'.
    /// red = 'R
    /// green = 'G'
    /// blue = 'B'
    /// brown = 'b'
    /// yellow = 'Y'
    /// orange = 'O'
    /// pink = 'P'
    void nameColorMode2();
};
#endif //COLORSENSOR_HPP