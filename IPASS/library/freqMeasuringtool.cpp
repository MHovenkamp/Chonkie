#include "freqMeasuringtool.hpp"

void freqMeasuringtool::sample(){
    std::array<uint_fast32_t, 30> testsamples;
    for(unsigned int i = 0; i < 30; i++){
        testsamples[i] = pin.read();
    }
    uint_fast32_t high = 0;
    for(unsigned int j = 0; j < 30; j++){
        if( testsamples[j] > high ){
            high = testsamples[j];
        }
    }
    while(pin.read() < high);
    while(pin.read() == high);
    t1 = hwlib::now_us();
    while(pin.read() < high);
    while(pin.read() == high);
    t2 = hwlib::now_us();
}
int freqMeasuringtool::calculate(){
    uint_fast64_t duration = t2-t1;
    frequenty = duration;
    return frequenty;
}