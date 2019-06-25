#include "chonkie.hpp"

//_________________________________Chonkie__________________________________________

void chonkie::print(){
    border.printe();
    body.draw( display );
    leftEye.draw( display );
    rightEye.draw( display );
    leftPupil.draw( display );
    rightPupil.draw( display );
    display.flush();
}

void chonkie::updateIdle(){
    if( left ){
        leftEye = hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white);
        rightEye = hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white);
        leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 2, hwlib::white);
        rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white);
        left = false;
        right = true;
    }
    else if( right ){
        leftEye = hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white);
        rightEye = hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white);
        leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 8, coordinaat.y), 2, hwlib::white);
        rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 12, coordinaat.y), 2, hwlib::white);
        left = true;
        right = false;
    }
}

void chonkie::animationCheck(){
    activity = manageHealth();
    hwlib::cout << "activity " << activity << hwlib::endl;
    if( activity == 'D'){
        drink();
        display.flush();
        activity = 'X';
    }
    if( activity == 'E'){
        eat();
        display.flush();
        activity = 'X';
    }
    if( activity == 'S'){
        sleep();
        display.flush();
        activity = 'X';
    }
    display.flush();
}
bool chonkie::deathCkeck(){
    if( happinessLevel <= 0 ){
        death();
        return true;
    }
    if( hungerLevel <= 0 ){
        death();
        return true;
    }
    if( thirstLevel <= 0 ){
        death();
        return true;
    }
    if( sleepLevel <= 0 ){
        death();
        return true;
    }
    return false;
}
void chonkie::drink(){
    int a;
    int b;
    int c;
    if( drinkBool ){
        a = 45;
        b = 50;
        drinkBool = false;
        c = (a + b)/2;
    }
    else{
        a = 50;
        b = 45;
        drinkBool = true;
        c = (a + b)/2;
    }

    for( int i = 5; i < 15; i++){
        display.write( hwlib::xy(i, a));
    }
    for( int i = 15; i < 25; i++){
        display.write( hwlib::xy(i, c));
    }
    for( int i = 25; i <35 ; i++){
        display.write( hwlib::xy(i, b));
    }
    for( int i = 35; i < 45; i++){
        display.write( hwlib::xy(i, c));
    }
    for( int i = 45; i < 55; i++){
        display.write( hwlib::xy(i, a));
    }
    for( int i = 55; i < 65; i++){
        display.write( hwlib::xy(i, c));
    }
    for( int i = 65; i < 80; i++){
        display.write( hwlib::xy(i, b));
    }
}

void chonkie::sleep(){
    leftEye = hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 0, hwlib::white);
    rightEye = hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 0, hwlib::white);
    leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 0, hwlib::white);
    rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 0, hwlib::white);
    display.flush();
    for(int i = coordinaat.x - 15; i < coordinaat.x -5; i ++){
        display.write( hwlib::xy ( i, coordinaat.y));
    }
    for(int j = coordinaat.x + 5; j < coordinaat.x + 15; j ++){
        display.write( hwlib::xy ( j, coordinaat.y));
    }
}

void chonkie::death(){
    leftEye = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 0, hwlib::white);
    rightEye = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 0, hwlib::white);
    leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 0, hwlib::white);
    rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 0, hwlib::white);
    leftEyeDeath.print();
    rightEyeDeath.print();
}

void chonkie::eat(){
    leftEye = hwlib::circle( hwlib::xy( coordinaat.x - 10, coordinaat.y), 5, hwlib::white);
    rightEye = hwlib::circle( hwlib::xy( coordinaat.x + 10, coordinaat.y), 5, hwlib::white);
    leftPupil = hwlib::circle( hwlib::xy( coordinaat.x - 12, coordinaat.y), 2, hwlib::white);
    rightPupil = hwlib::circle( hwlib::xy( coordinaat.x + 8, coordinaat.y), 2, hwlib::white);
    if( mouthBool ){
        mouth = hwlib::circle( hwlib::xy( coordinaat.x, coordinaat.y + 4), 5, hwlib::white);
        mouth.draw( display );
        mouthBool = false;
    }
    else if( mouthBool == false ){
        mouth = hwlib::circle( hwlib::xy( coordinaat.x, coordinaat.y + 4), 2, hwlib::white);
        mouth.draw( display );
        mouthBool = true;
    }

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

char lives::manageHealth(){
    sensor.calculateRGB();
    sensor.nameColorMode1();
    char action = sensor.getColor();
    hwlib::cout << action << hwlib::endl;
    int hungerUp = 2;
    int thirstUp = 3;
    int sleepUp = 1;
    char activity = 'X';
    if( action == 'R'){
        activity = 'E';
        hungerLevel = hungerLevel + 40;
        thirstLevel = thirstLevel - thirstUp;
        sleepLevel = sleepLevel - sleepUp;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else if( action == 'B'){
        activity = 'D';
        thirstLevel = thirstLevel + 40;
        hungerLevel = hungerLevel - hungerUp;
        sleepLevel = sleepLevel - sleepUp;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else if( action == 'G'){
        activity = 'S';
        sleepLevel = sleepLevel + 40;
        hungerLevel = hungerLevel - hungerUp;
        thirstLevel = thirstLevel - thirstUp;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    else{
        hungerLevel = hungerLevel - hungerUp;
        thirstLevel = thirstLevel - thirstUp;
        sleepLevel = sleepLevel - sleepUp;
        happinessLevel = (hungerLevel + thirstLevel + sleepLevel) / 3;
    }
    if(sleepLevel > 100){
        sleepLevel = 100;
    }
    if(sleepLevel < 0){
        sleepLevel = 0;
    }
    if(thirstLevel > 100){
        thirstLevel = 100;
    }
    if(thirstLevel < 0){
        thirstLevel = 0;
    }
    if(hungerLevel > 100){
        hungerLevel = 100;
    }
    if(hungerLevel < 0){
        hungerLevel = 0;
    }
    return activity;
}
