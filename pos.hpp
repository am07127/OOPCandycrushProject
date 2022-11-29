#include<iostream>
#pragma once

class pos{
    public:
       int x;
       int y;
    pos(){
       x=0;
       y=0;
    };
    void set_pos(int X,int Y);

    int get_x();

    int get_y();

};
