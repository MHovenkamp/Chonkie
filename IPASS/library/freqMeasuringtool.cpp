#include "freqMeasuringtool.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________

void freqMeasuringtool::sample(){
    while(pin.read() == 1);
    while(pin.read() == 0);
    t1 = hwlib::now_us();
    while(pin.read() == 1);
    while(pin.read() == 0);
    t2 = hwlib::now_us();
}
void freqMeasuringtool::calculate(){
    uint_fast64_t duration = (t2-t1);
    frequenty = 1000000 / duration;
}

int freqMeasuringtool::read(){
    sample();
    calculate();
    return frequenty;
}