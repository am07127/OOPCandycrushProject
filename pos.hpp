#include<iostream>
#pragma once

class pos{

    public:
      int x;   // x,y co-ordinates of mouse
      int y;
      
      pos(){     // constructor
         x=0;
         y=0;
      };

      void set_pos(int X,int Y);

      int get_x();

      int get_y();

};
