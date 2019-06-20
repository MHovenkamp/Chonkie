#ifndef FREQMEASURE_HPP
#define FREQMEASURE_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

class freqMeasure{
protected: 
    int frequenty;
    uint_fast64_t t1;
    uint_fast64_t t2;
public:
    hwlib::target::pin_adc pin;
    freqMeasure( hwlib::target::pin_adc & pin ):
        pin( pin )
    {}
    freqMeasure( freqMeasure & rhs ):
        pin( rhs.pin )
    {}
    void sample();
    int calculate();
};

#endif //FREQMEASURE_HPP