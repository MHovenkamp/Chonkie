#ifndef FREQMEASURINGTOOL_HPP
#define FREQMEASURINGTOOL_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

//____________________________________________________________________________________
//          Copyright Maaike Hovenkamp 2019. 
// Distributed under the Boost Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt or copy at 
//          https://www.boost.org/LICENSE_1_0.txt)
//____________________________________________________________________________________

/// @file

/// \brief
/// freqMeasuringtool ADT
/// \details
/// This is an ADT that gives the user a frequenty from an analog to digital converter pin.
/// The frequenty in microseconds is stored as an integer inside the function 
/// the ADT is dependant on the hwlib library for an input pin_in and its now_us() function.
/// https://github.com/wovo/hwlib

class freqMeasuringtool{
protected: 
    int frequenty;
    uint_fast64_t t1;
    uint_fast64_t t2;
    hwlib::target::pin_in & pin;
public:

    /// \brief
    /// freqMeasuringtool constructor with pin.
    /// \details
    /// This is a constructor that constructs an ADT with the input of an hwlib::target::pin_in.
    freqMeasuringtool( hwlib::target::pin_in & pin ):
        pin( pin )
    {}
    /// \brief
    /// sample() function.
    /// \details
    /// Sample function that takes 30 samples of frequenty and puts the average in the int frequenty.
    void sample();

    /// \brief
    /// calculate() function.
    /// \details
    /// The sample function has te be run once in order to use this function. The previously filled int frequenty is in microseconds. 
    /// In this function the frequency is transferred into hertz.
    void calculate();

    /// \brief
    /// read() function.
    /// \details
    /// The read function gives you the frequenty in Hertz of the pin back as an int.
    int read();

};

#endif //FREQMEASURINGTOOL_HPP