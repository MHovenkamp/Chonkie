#include "chonkie.hpp"

//_________________________________Chonkie__________________________________________

void chonkie::print(){
    border.print();
    body.draw( display );
    leftEye.draw( display );
    rightEye.draw( display );
    leftPupil.draw( display );
    rightPupil.draw( display );
    display.flush();

    
}

void chonkie::updateIdle(){
    if( left ){
        leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 2, hwlib::white);
        rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white);
        left = false;
        right = true;
    }
    else if( right ){
        leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 8, coordinaat.y), 2, hwlib::white);
        rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 12, coordinaat.y), 2, hwlib::white);
        left = true;
        right = false;
    }
    // if( activity == 'D'){
    //     giveWater();
    // }
    // if( activity == 'E'){
    //     giveFood();
    // }
    // if( activity == 'S'){
    //     sleep();
    // }
}

bool chonkie::deathCkeck(){
    if( happinessLevel <= 0 ){
        return true;
    }
    if( hungerLevel <= 0 ){
        return true;
    }
    if( thirstLevel <= 0 ){
        return true;
    }
    if( sleepLevel <= 0 ){
        return true;
    }
    return false;
}


//_________________________________Healthbar________________________________________
void healthbar::draw( hwlib::glcd_oled & display ){
    //top lines
    for(uint16_t i = 0; i <= length; i++){
        display.write( hwlib::xy( start.x + i, start.y ) );
        display.write( hwlib::xy( start.x + i, start.y + height ) );
    }
    //side lines
    for(uint16_t j = 0; j <= height; j++){
        display.write( hwlib::xy( start.x , start.y+ j ) );
        display.write( hwlib::xy( start.x + length , start.y + j ) );
    }
    //filled parts
    for(uint16_t y = start.y; y < start.y + height; y++){
        for(uint16_t x = start.x; x < start.x + filled; x++){
            display.write( hwlib::xy( x , y ) );
        }
    }
}

void healthbar::setfilled( int value ){
    filled = (length * value)/100;
    if( filled > 30 ){
        filled = 30;
    }
    //hwlib::cout << filled << hwlib::endl;
}

//_________________________________lives______________________________________________
void lives::draw( hwlib::glcd_oled & display ){
    happiness.draw( display );
    hunger.draw( display );
    thirst.draw( display );
    sleep.draw( display );
}
void lives::set(){
    happiness.setfilled( happinessLevel );
    hunger.setfilled( hungerLevel );
    thirst.setfilled( thirstLevel );
    sleep.setfilled( sleepLevel );
}

void lives::manageHealth(){
    sensor.calculateRGB();
    sensor.nameColorMode1();
    char action = sensor.getColor();
    hwlib::cout << action << hwlib::endl;
    int hungerUp = 2;
    int thirstUp = 3;
    int sleepUp = 1;
    if( action == 'R'){
        //activity = 'E';
        hungerLevel = hungerLevel + 40;
        thirstLevel = thirstLevel - thirstUp;
        sleepLevel = sleepLevel - sleepUp;
        if(hungerLevel > 100){
            hungerLevel = 100;
        }
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else if( action == 'B'){
        //activity = 'D';
        thirstLevel = thirstLevel + 40;
        hungerLevel = hungerLevel - hungerUp;
        sleepLevel = sleepLevel - sleepUp;
        if(thirstLevel > 100){
            thirstLevel = 100;
        }
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else if( action == 'G'){
        //activity = 'S';
        sleepLevel = sleepLevel + 40;
        hungerLevel = hungerLevel - hungerUp;
        thirstLevel = thirstLevel - thirstUp;
        if(sleepLevel > 100){
            sleepLevel = 100;
        }
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else{
        hungerLevel = hungerLevel - hungerUp;
        thirstLevel = thirstLevel - thirstUp;
        sleepLevel = sleepLevel - sleepUp;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    action = 'X';
}
