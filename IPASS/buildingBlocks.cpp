#include "buildingBlocks.hpp"

//_________________________rectangle______________________________--

rectangle::rectangle( hwlib::window & display, int sx, int sy, int ex, int ey ):
   display( display ),
   start_x(sx),
   start_y(sy), 
   end_x(ex),
   end_y(ey)
{}


void rectangle::printe(){
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

void rectangle::printf(){
   //filled rectangle
   for(int i = start_y; i < end_y; i++){
      for(int j = start_x; j < end_x; j++){
         display.write(hwlib::xy(i,j));
      }
   }
}

//_____________________crosses_____________________________________

crosses::crosses( hwlib::window & display, int start_x, int start_y, int end_x, int end_y):
   display( display ),
   start_x( start_x ),
   start_y( start_y ),
   end_x( end_x ),
   end_y( end_y )
{}

void crosses::print(){
   int countUpOne = start_y;
   int countUpTwo = end_y;
   for(int i = start_x; i <= end_x; i++){
      display.write(hwlib::xy(i,countUpOne));
      countUpOne++;
   }
   for(int j = start_x; j <= end_x; j++){
      display.write(hwlib::xy(j,countUpTwo));
      countUpTwo--;
   }
}
