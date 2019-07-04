#include "colorSensor.hpp"
#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________

char colorSensor::getColor(){
    return color;
}

int colorSensor::getlightIntensity(){
    return lightIntensity;
}

hwlib::color colorSensor::getRGB(){
    return RGB;
}

void colorSensor::setRed(){
    pins.write( 0b0010 );
    flush();
}

void colorSensor::setClear(){
    pins.write( 0b0110 );
    flush();
}

void colorSensor::setGreen(){
    pins.write( 0b1110 );
    flush();
}

void colorSensor::setBlue(){
    pins.write( 0b1010 );
    flush();
}

void colorSensor::flush(){
    pins.flush();
}

void colorSensor::calculatelightIntensity(){
    setClear();
    lightIntensity = read();
}

int colorSensor::calculateColor(){
    const int sampleSize = 25;
    int value = 0;
    for (unsigned int i = 0; i <= sampleSize; i++){
        sample();
        value += read();
    }
    return value/sampleSize;
}

void colorSensor::calculateRGB(){
    calculatelightIntensity();
    int value = getlightIntensity();
    if( value > 1000 ){
        //red
        setRed();
        red = calculateColor();
        //Green
        setGreen();
        green = calculateColor();
        //Blue
        setBlue();
        blue = calculateColor();
        shrinkValueRGB();
        RGB = hwlib::color(red, green, blue);
    }
}

void colorSensor::printRGB(){
    hwlib::cout << "Red: " << RGB.red << hwlib::endl;
    hwlib::cout << "Green: " << RGB.green << hwlib::endl;
    hwlib::cout << "Blue: " << RGB.blue << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "Color " << color << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "lightintensity " << lightIntensity << hwlib::endl;
}

void colorSensor::shrinkValueRGB(){
    int highest = std::max(std::max(red ,green), blue);
    int lowest = std::min(std::min(red ,green), blue);
    while( lowest > 0 && highest > 255){
        red = red/2;
        green = green/2;
        blue = blue/2;
        highest = std::max(std::max(red ,green), blue);
        lowest = std::min(std::min(red ,green), blue);
    }   
}

void colorSensor::nameColorMode1(){
    std::array<int,2> zone1 = {0,32};
    std::array<int,2> zone2 = {32,64};
    std::array<int,2> zone3 = {64,96};
    std::array<int,2> zone4 = {96,128};
    std::array<int,2> zone5 = {128,160};
    std::array<int,2> zone6 = {160,192};
    std::array<int,2> zone7 = {192,224};
    std::array<int,2> zone8 = {224,255};
    std::array<std::array<int,2>,15> zones = {zone1, zone2, zone3, zone4, zone5, zone6, zone7, zone8};
    int redZone = 0;
    int greenZone = 0;
    int blueZone = 0;
    for( unsigned int i = 0; i < 8; i++ ){
        if( RGB.red >= zones[i][0] && RGB.red <= zones[i][1]){redZone = i+1;}
        if( RGB.green >= zones[i][0] && RGB.green <= zones[i][1]){greenZone = i+1;}
        if( RGB.blue >= zones[i][0] && RGB.blue <= zones[i][1]){blueZone = i+1;}
    }
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "redZone " << redZone << hwlib::endl;
    hwlib::cout << "greenZone " << greenZone << hwlib::endl;
    hwlib::cout << "blueZone " << blueZone << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;

    std::array<int, 3> value = {redZone, greenZone, blueZone};
    std::array<std::array<int, 2>,3> redValues = {{{5,6},{2,3},{3,4}}};
    std::array<std::array<int, 2>,3> greenValues = {{{3,4},{4,5},{3,4}}};
    std::array<std::array<int, 2>,3> blueValues = {{{1,2},{2,3},{4,5}}};
    const int AmountOfColors = 4;
    std::array<int, AmountOfColors> colorCounts = {0, 0, 0};
    for( unsigned int i = 0; i < 3; i++ ){
        if(value[i] == redValues[i][0] || value[i] == redValues[i][1]){ colorCounts[0]++; }
        if(value[i] == greenValues[i][0] || value[i] == greenValues[i][1]){ colorCounts[1]++; }
        if(value[i] == blueValues[i][0] || value[i] == blueValues[i][1]){ colorCounts[2]++; }
    }
    std::array<colors, AmountOfColors> colorChars = {colors::red, colors::green, colors::blue};
    color = static_cast<char>(colors::empty);
    for( unsigned int i = 0; i < AmountOfColors; i++ ){
        if( colorCounts[i] == 3 ){
            color = static_cast<char>(colorChars[i]);
        }
    }
}
void colorSensor::nameColorMode2(){
    std::array<int,2> zone1 = {0,16};
    std::array<int,2> zone2 = {16,32};
    std::array<int,2> zone3 = {32,64};
    std::array<int,2> zone4 = {64,80};
    std::array<int,2> zone5 = {80,96};
    std::array<int,2> zone6 = {96,112};
    std::array<int,2> zone7 = {112,128};
    std::array<int,2> zone8 = {128,144};
    std::array<int,2> zone9 = {144,160};
    std::array<int,2> zone10 = {160,176};
    std::array<int,2> zone11 = {176,192};
    std::array<int,2> zone12 = {192,208};
    std::array<int,2> zone13 = {208,224};
    std::array<int,2> zone14 = {224,240};
    std::array<int,2> zone15 = {240,255};
    std::array<std::array<int,2>,15> zones = {zone1, zone2, zone3, zone4, zone5, zone6, zone7, zone8, zone9, zone10, zone11, zone12, zone13, zone14, zone15};
    int redZone = 0;
    int greenZone = 0;
    int blueZone = 0;
    for( unsigned int i = 0; i < 14; i++ ){
        if( RGB.red >= zones[i][0] && RGB.red <= zones[i][1]){redZone = i+1;}
        if( RGB.green >= zones[i][0] && RGB.green <= zones[i][1]){greenZone = i+1;}
        if( RGB.blue >= zones[i][0] && RGB.blue <= zones[i][1]){blueZone = i+1;}
    }
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "redZone " << redZone << hwlib::endl;
    hwlib::cout << "greenZone " << greenZone << hwlib::endl;
    hwlib::cout << "blueZone " << blueZone << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;

    std::array<int, 3> value = {redZone, greenZone, blueZone};
    std::array<std::array<int, 2>,3> pinkValues = {{{8,9},{4,5},{7,8}}};
    std::array<std::array<int, 2>,3> brownValues = {{{11,12},{7,8},{9,10}}};
    std::array<std::array<int, 2>,3> orangeValues = {{{7,8},{2,3},{2,3}}};
    std::array<std::array<int, 2>,3> yellowValues = {{{8,9},{6,7},{4,5}}};
    std::array<std::array<int, 2>,3> redValues = {{{9,10},{3,4},{5,6}}};
    std::array<std::array<int, 2>,3> greenValues = {{{4,5},{7,8},{6,7}}};
    std::array<std::array<int, 2>,3> blueValues = {{{2,3},{4,5},{7,8}}};
    const int AmountOfColors = 7;
    std::array<int, AmountOfColors> colorCounts = {0, 0, 0, 0, 0, 0, 0};
    for( unsigned int i = 0; i < 3; i++ ){
        if(value[i] == pinkValues[i][0] || value[i] == pinkValues[i][1]){ colorCounts[0]++; }
        if(value[i] == brownValues[i][0] || value[i] == brownValues[i][1]){ colorCounts[1]++; }
        if(value[i] == orangeValues[i][0] || value[i] == orangeValues[i][1]){ colorCounts[2]++; }
        if(value[i] == yellowValues[i][0] || value[i] == yellowValues[i][1]){ colorCounts[3]++; }
        if(value[i] == redValues[i][0] || value[i] == redValues[i][1]){ colorCounts[4]++; }
        if(value[i] == greenValues[i][0] || value[i] == greenValues[i][1]){ colorCounts[5]++; }
        if(value[i] == blueValues[i][0] || value[i] == blueValues[i][1]){ colorCounts[6]++; }
    }
    std::array<colors, AmountOfColors> colorChars = {colors::pink, colors::brown, colors::orange, colors::yellow, colors::red, colors::green, colors::blue};
    for( unsigned int i = 0; i < AmountOfColors; i++ ){
        if( colorCounts[i] == 3 ){
            color = static_cast<char>(colorChars[i]);
        }
    }
}