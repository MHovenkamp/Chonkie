#include "buildingBlocks.hpp"

//_________________________rectangle______________________________

void rectangle::printe(){
   //empty rectangle
   for(int a = start.y;  a<= end.y; a++){
      display.write(hwlib::xy(start.x,a));
      display.write(hwlib::xy(end.x,a));
   }
   for(int b = start.x; b <= end.x; b++){
      display.write(hwlib::xy(b,start.y));
      display.write(hwlib::xy(b,end.y));
   }
}

void rectangle::printf(){
   //filled rectangle
   for(int i = start.y; i < end.y; i++){
      for(int j = start.x; j < end.x; j++){
         display.write(hwlib::xy(i,j));
      }
   }
}

//_____________________crosses_____________________________________

void crosses::print(){
   int countUpOne = start.y;
   int countUpTwo = end.y;
   for(int i = start.x; i <= end.x; i++){
      display.write(hwlib::xy(i,countUpOne));
      countUpOne++;
   }
   for(int j = start.x; j <= end.x; j++){
      display.write(hwlib::xy(j,countUpTwo));
      countUpTwo--;
   }
}
