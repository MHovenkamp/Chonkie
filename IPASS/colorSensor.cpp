#include "colorSensor.hpp"
#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

char colorSensor::getColor(){
    return color;
}

std::array<int, 3> colorSensor::getRGB(){
    std::array<int, 3> RGB = {red, green, blue};
    return RGB;
}


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
    if(color == 'O' || color == 'b' || color == 'P'){
        hwlib::cout << "Color (30% chance) " << color << hwlib::endl;
    }
    else{
        hwlib::cout << "Color " << color << hwlib::endl;
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
        if( red >= zones[i][0] && red <= zones[i][1]){redZone = i+1;}
        if( green >= zones[i][0] && green <= zones[i][1]){greenZone = i+1;}
        if( blue >= zones[i][0] && blue <= zones[i][1]){blueZone = i+1;}
    }
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "red " << redZone << hwlib::endl;
    hwlib::cout << "green " << greenZone << hwlib::endl;
    hwlib::cout << "blue " << blueZone << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;

    std::array<int, 3> value = {redZone, greenZone, blueZone};
    //std::array<std::array<int, 2>,3> yellowValues = {{{4,5},{5,6},{5,6}}};
    std::array<std::array<int, 2>,3> redValues = {{{3,4},{6,7},{5,6}}};
    std::array<std::array<int, 2>,3> greenValues = {{{5,6},{5,6},{5,6}}};
    std::array<std::array<int, 2>,3> blueValues = {{{5,6},{4,5},{3,4}}};
    const int AmountOfColors = 4;
    std::array<int, AmountOfColors> colorCounts = {0, 0, 0, 0};
    for( unsigned int i = 0; i < 3; i++ ){
        //if(value[i] == yellowValues[i][0] || value[i] == yellowValues[i][1]){ colorCounts[0]++; }
        if(value[i] == redValues[i][0] || value[i] == redValues[i][1]){ colorCounts[1]++; }
        if(value[i] == greenValues[i][0] || value[i] == greenValues[i][1]){ colorCounts[2]++; }
        if(value[i] == blueValues[i][0] || value[i] == blueValues[i][1]){ colorCounts[3]++; }
    }
    std::array<char, AmountOfColors> colorChars = {'Y','R','G','B'};
    color = 'X';
    for( unsigned int i = 0; i < AmountOfColors; i++ ){
        if( colorCounts[i] == 3 ){
            color = colorChars[i];
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
    for( unsigned int i = 0; i < 8; i++ ){
        if( red >= zones[i][0] && red <= zones[i][1]){redZone = i+1;}
        if( green >= zones[i][0] && green <= zones[i][1]){greenZone = i+1;}
        if( blue >= zones[i][0] && blue <= zones[i][1]){blueZone = i+1;}
    }
    hwlib::cout << "___________________________________" << hwlib::endl;
    hwlib::cout << "red " << redZone << hwlib::endl;
    hwlib::cout << "green " << greenZone << hwlib::endl;
    hwlib::cout << "blue " << blueZone << hwlib::endl;
    hwlib::cout << "___________________________________" << hwlib::endl;

    std::array<int, 3> value = {redZone, greenZone, blueZone};
    std::array<std::array<int, 2>,3> pinkValues = {{{5,5},{6,6},{5,4}}};
    std::array<std::array<int, 2>,3> brownValues = {{{4,5},{5,5},{5,5}}};
    std::array<std::array<int, 2>,3> orangeValues = {{{5,6},{7,8},{6,7}}};
    std::array<std::array<int, 2>,3> yellowValues = {{{5,4},{5,5},{5,5}}};
    std::array<std::array<int, 2>,3> redValues = {{{4,3},{5,5},{4,4}}};
    std::array<std::array<int, 2>,3> greenValues = {{{8,8},{8,7},{8,7}}};
    std::array<std::array<int, 2>,3> blueValues = {{{7,8},{5,6},{4,5}}};
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
    std::array<char, AmountOfColors> colorChars = {'P','b','O','Y','R','G','B'};
    for( unsigned int i = 0; i < AmountOfColors; i++ ){
        if( colorCounts[i] == 3 ){
            color = colorChars[i];
        }
    }
}
