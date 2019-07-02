#ifndef BUILDINGBLOCKS_HPP
#define BUILDINGBLOCKS_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

/// @file

/// \brief
/// retangle ADT
/// \details
/// This is an ADT that makes and prints filled and empty rectangle. It is dependend on the library hwlib
/// https://github.com/wovo/hwlib
class rectangle {
private:
   hwlib::window & display;
   hwlib::xy start;
   hwlib::xy end;
   
public:

   /// \brief
   /// retangle constructor
   /// \details
   /// This constructor creates a rectangle out of 2 hwlib::xy coordinates;
   rectangle( hwlib::window & display, hwlib::xy start, hwlib::xy end ):
      display( display ),
      start( start ),
      end( end )
   {}
   /// \brief
   /// printe() function
   /// \details
   /// This function prints an empty rectangle.
   void printe();

   /// \brief
   /// printf() function
   /// \details
   /// This function prints a filled rectangle.
   void printf();
};


/// @file

/// \brief
/// crosses ADT
/// \details
/// This is an ADT that makes and prints crosses. It is dependend on the library hwlib
/// https://github.com/wovo/hwlib
class crosses{
private:
   hwlib::window & display;
   hwlib::xy start;
   hwlib::xy end;
public:

   /// \brief
   /// crosses constructor
   /// \details
   /// This is a constructor that constructs a cross out of 2 hlib::xy coordinates
   crosses( hwlib::window & display, hwlib::xy start, hwlib::xy end):
   display( display ),
   start( start ),
   end( end )
{}

   /// \brief
   /// print() function
   /// \details
   /// This function prints a cross.
   void print();
};


#endif // BUIDLINGBLOCKS_HPP