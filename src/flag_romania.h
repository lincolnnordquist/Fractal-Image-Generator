#ifndef FLAG_ROMANIA_H
#define FLAG_ROMANIA_H
#include "PPM.h"
#include <iostream>


class flag_romania: public PPM{
public:
    flag_romania();
    flag_romania(const int& height, const int& width, const int& max_color_value);

};
#endif