#ifndef BUILDINGBLOCKS_HPP
#define BUILDINGBLOCKS_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

class rectangle {
private:
   hwlib::window & display;
   int start_x;
   int start_y; 
   int end_x;
   int end_y;
   
public:
   rectangle( hwlib::window & display, int start_x, int start_y, int end_x, int end_y );
   void printe();
   void printf();
};

class crosses{
private:
   hwlib::window & display;
   int start_x;
   int start_y; 
   int end_x;
   int end_y;
public:
   crosses( hwlib::window & display, int start_x, int start_y, int end_x, int end_y );
   void print();
};


#endif // BUIDLINGBLOCKS_HPP