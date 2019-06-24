#include "buildingBlocks.hpp"

//_________________________rectangle______________________________--

rectangle::rectangle( hwlib::window & display, int sx, int sy, int ex, int ey ):
   display( display ),
   start_x(sx),
   start_y(sy), 
   end_x(ex),
   end_y(ey)
{}


void rectangle::print(){
   //empty rectangle
   for(int a = start_y;  a<= end_y; a++){
      display.write(hwlib::xy(start_x,a));
      display.write(hwlib::xy(end_x,a));
   }
   for(int b = start_x; b <= end_x; b++){
      display.write(hwlib::xy(b,start_y));
      display.write(hwlib::xy(b,end_y));
   }
}