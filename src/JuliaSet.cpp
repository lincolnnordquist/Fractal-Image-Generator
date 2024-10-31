#include "JuliaSet.h"
#include <cmath>

JuliaSet::JuliaSet() 
    : ComplexFractal(), mA(-0.650492), mB(-0.478235) { 
    setMaxNumber(255);
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b) 
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(-0.650492), mB(-0.478235) {
    mA = a;
    mB = b;
}

JuliaSet::~JuliaSet(){

}

double JuliaSet::getA() const {
    return mA;
}

double JuliaSet::getB() const {
    return mB;
}

void JuliaSet::setParameters(const double& a, const double& b) {
    if (a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0){
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const {
    x1 = (x0 * x0) - (y0 * y0) + mA;
    y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const{
    int count =0;
    double x1=x0, y1=y0;
    double x2=0, y2=0;
    while(count < getMaxNumber() && sqrt(x1*x1 + y1*y1) <=2){
        calculateNextPoint(x1,y1,x2,y2);
        count++;
        x1=x2;
        y1=y2;
    }
    return count;
}

int JuliaSet::calculateNumber(const int &row, const int &column) const {
    //double x = calculatePlaneXFromPixelColumn(column);
    //double y = calculatePlaneYFromPixelRow(row);
    //calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
    if (row < 0 || row >= mHeight || column < 0 || column >= mWidth ){
        return -1;
    }
    else{
        double x = calculatePlaneXFromPixelColumn(column);
        double y = calculatePlaneYFromPixelRow(row);
        int val = calculatePlaneEscapeCount(x, y);
        return val;
    }
}
