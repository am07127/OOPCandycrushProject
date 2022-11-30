#include "pos.hpp"


void pos :: set_pos(int X,int Y) {
        x = X / 100;
        y = Y / 60;
}

int pos :: get_x() {
        return x;
}
int pos :: get_y() {
        return y;
}