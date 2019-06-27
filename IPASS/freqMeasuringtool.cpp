#include "freqMeasuringtool.hpp"

void freqMeasuringtool::sample(){
    while(pin.read() == 0);
    while(pin.read() == 1);
    t1 = hwlib::now_us();
    while(pin.read() == 0);
    while(pin.read() == 1);
    t2 = hwlib::now_us();
}
void freqMeasuringtool::calculate(){
    uint_fast64_t duration = t2-t1;
    frequenty = duration;
}

int freqMeasuringtool::read(){
    sample();
    calculate();
    return frequenty;
}