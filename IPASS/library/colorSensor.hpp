#ifndef colorSensor_HPP
#define colorSensor_HPP

#include "hwlib.hpp"
#include "freqMeasuringtool.hpp"
#include "../../hwlib/library/hwlib.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________

/// @file

/// \brief
/// colorSensor ADT
/// \details
/// This is an ADT that gives the user RGB values of colors. the RGB values are stored seperately as integers.
/// The RGB values do not match the standard RGB codes.
/// This ADT can also give the name of a few colors with two different modes as a char and is stored as a char. 
/// If a char is used multiple times the primary color is capitalized and the secundary color lowercase.
/// this ADT is reliant on hwlb and freqMeasuringtool.
/// https://github.com/wovo/hwlib

class colorSensor: public freqMeasuringtool{
private:
    hwlib::port_out & pins;
    hwlib::color RGB = hwlib::color(0,0,0);
    int red = 0;
    int green = 0;
    int blue = 0;
    int lightIntensity = 0;
    char color = 'X';
public:
    enum class colors: char {
        red     = 'R',
        green   = 'G',
        blue    = 'B',
        yellow  = 'Y',
        pink    = 'P',
        brown   = 'b',
        orange  = 'O',
        empty   = 'X'
    };
    /// \brief
    /// colorSensor constructor.
    /// \details
    /// This constructor construct the colorSensor with the intput of an hwlib::target::in and four pins in an hwlib::port_out. 
    /// It also sets the frequenty scaling to 2%.
    colorSensor( hwlib::target::pin_in & freq, hwlib::port_out & pins ):
        freqMeasuringtool( freq ),
        pins( pins )
    {}
    
    /// \brief
    /// getColor() function.
    /// \details
    /// This function returns the color as a char.
    char getColor();

    /// \brief
    /// getlightIntensity() function.
    /// \details
    /// This function returns the lightIntensity as an int.
    int getlightIntensity();

    /// \brief
    /// getRGB() function.
    /// \details
    /// This function returns the RGB values as an hwlib::color.
    hwlib::color getRGB();

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
    /// This function sets the color sensor to read clear values for light intensity and flushes the sensor.
    void setClear();

    /// \brief
    /// flush() function.
    /// \details
    /// This function flushes the chosen settings to the sensor.
    void flush();

    /// \brief
    /// calculatelightIntensity() function.
    /// \details
    /// This function fils the int lightIntensity with the light intensity.
    void calculatelightIntensity();

    /// \brief
    /// calculateColor() function.
    /// \details
    /// This function takes 25 samples of a single color and takes the average frequenty and returns this as an int.
    int calculateColor();

    /// \brief
    /// calculateRGB() function.
    /// \details
    /// This function sets the hwlib::color using the calculateColor function.
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
    /// The color is determined by putting shrinkValueRGB values into 8 different zones. the combination of three zondes correspond with a color.
    /// red = 'R
    /// green = 'G'
    /// blue = 'B'
    void nameColorMode1();

    /// \brief
    /// nameColorMode2() function.
    /// \details
    /// This function fils the color char with either the color red, green, blue, brown, yellow, orange or pink. 
    /// It is consistent but can be influenced by ambient light.
    /// If the color in front of the sensor cannot be defined as one of the colors the color will be filled with an 'X'.
    /// The color is determined by putting shrinkValueRGB values into 16 different zones. the combination of three zondes correspond with a color.
    /// red = 'R',
    /// green = 'G',
    /// blue = 'B',
    /// brown = 'b',
    /// yellow = 'Y',
    /// orange = 'O',
    /// pink = 'P'.
    void nameColorMode2();
};
#endif //COLORSENSOR_HPP