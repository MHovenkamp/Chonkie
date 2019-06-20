#include "colorSensor.hpp"
#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

void colorSensor::setRed(){
    s2.write(0);
    s3.write(0);
    flush();
}

void colorSensor::setGreen(){
    s2.write(1);
    s3.write(1);
    flush();
}

void colorSensor::setBlue(){
    s2.write(0);
    s3.write(1);
    flush();
}

void colorSensor::flush(){
    s0.flush();
    s1.flush();
    s2.flush();
    s3.flush();
}

int colorSensor::calculateColor(){
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

void colorSensor::calculateRGB(){
    //red
    setRed();
    red = calculateColor();
    //Green
    setGreen();
    green = calculateColor();
    //Blue
    setBlue();
    blue = calculateColor();
    //turn them into useable RGB value with max 255
    shrinkValueRGB();
}

void colorSensor::shrinkValueRGB(){
    int highest = red;
    int lowest = blue;
    int last = 0;
    if( red > green && red > blue ){highest = red;}
    if( green > red && green > blue ){highest = green;}
    if( blue > green && blue > red ){highest = blue;}
    if( red < green && red < blue ){lowest = red;}
    if( green < red && green < blue ){lowest = green;}
    if( blue < green && blue < red ){lowest = blue;}
    while( lowest > 0 ){
        red = red/2;
        green = green/2;
        blue = blue/2;
        if( red > green && red > blue ){highest = red;}
        if( green > red && green > blue ){highest = green;}
        if( blue > green && blue > red ){highest = blue;}
        if( red < green && red < blue ){lowest = red;}
        if( green < red && green < blue ){lowest = green;}
        if( blue < green && blue < red ){lowest = blue;}
        if (lowest == last || highest < 255){break;}
        last = lowest;
    }   
}

void colorSensor::printRGB(){
    hwlib::cout << "Red: " << red << hwlib::endl;
    hwlib::cout << "Green: " << green << hwlib::endl;
    hwlib::cout << "Blue: " << blue << hwlib::endl;
    hwlib::cout << "Color " << color << hwlib::endl;
}

void colorSensor::nameColor(){
    std::array<std::array<int,2>,8> zones = {zone1, zone2, zone3, zone4, zone5, zone6, zone7, zone8};
    int redZone = 0;
    int greenZone = 0;
    int blueZone = 0;
    for( unsigned int i = 0; i < 8; i++ ){
        if( red >= zones[i][0] && red <= zones[i][1]){redZone = i+1;}
        if( green >= zones[i][0] && green <= zones[i][1]){greenZone = i+1;}
        if( blue >= zones[i][0] && blue <= zones[i][1]){blueZone = i+1;}
    }
    std::array<int, 3> value = {redZone, greenZone, blueZone};
    std::array<std::array<int, 2>,3> redValues = {{{2,3},{5,6},{2,3}}};
    std::array<std::array<int, 2>,3> greenValues = {{{6,7},{5,6},{4,5}}};
    std::array<std::array<int, 2>,3> blueValues = {{{5,6},{4,5},{2,3}}};
    std::array<std::array<int, 2>,3> yellowValues = {{{5,6},{6,7},{7,8}}};
    std::array<std::array<int, 2>,3> orangeValues = {{{2,3},{5,6},{3,4}}};
    const int AmountOfColors = 5;
    std::array<int, AmountOfColors> colorCounts = {0, 0, 0, 0, 0};
    for( unsigned int i = 0; i < 3; i++ ){
        if(value[i] == redValues[i][0] || value[i] == redValues[i][1]){ colorCounts[0]++; }
        if(value[i] == greenValues[i][0] || value[i] == greenValues[i][1]){ colorCounts[1]++; }
        if(value[i] == blueValues[i][0] || value[i] == blueValues[i][1]){ colorCounts[2]++; }
        if(value[i] == yellowValues[i][0] || value[i] == yellowValues[i][1]){ colorCounts[3]++; }
        if(value[i] == yellowValues[i][0] || value[i] == orangeValues[i][1]){ colorCounts[4]++; }
    }
    std::array<char, AmountOfColors> colorChars = {'R','G','B','Y','O'};
    for( unsigned int i = 0; i < AmountOfColors; i++ ){
        if( colorCounts[i] == 3 ){
            color = colorChars[i];
        }
    }
};