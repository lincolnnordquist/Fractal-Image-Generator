#include "NumberGrid.h"

NumberGrid::NumberGrid()
    : mHeight(300), mWidth(400), mMaxValue(255){
        mGrid.resize(mHeight * mWidth);
        std::fill(mGrid.begin(),mGrid.end(),0);
}

NumberGrid::NumberGrid(const int& height, const int& width)
    : mHeight(height), mWidth(width), mMaxValue(255){
    mGrid.resize(mHeight * mWidth);
    std::fill(mGrid.begin(),mGrid.end(),0);
}

NumberGrid::~NumberGrid(){}

int NumberGrid::getHeight() const {
    return mHeight;
}

int NumberGrid::getWidth() const {
    return mWidth;
}

int NumberGrid::getMaxNumber() const {
    return mMaxValue;
}

void NumberGrid::setGridSize(const int& height, const int& width) {
    if(height >= 2 && width >= 2){
        mHeight = height;
        mWidth = width;
        //mMaxValue = 255;
        mGrid.resize(mHeight * mWidth);
    }
}

void NumberGrid::calculateAllNumbers() {
    for (int row = 0; row <= mHeight; row++){
        for (int col = 0; col <= mWidth; col++){
            setNumber(row, col, calculateNumber(row, col));
        }
    }
}

void NumberGrid::setMaxNumber(const int &number) {
    if (number >= 0){
        mMaxValue = number;
    }
}

const std::vector<int> &NumberGrid::getNumbers() const {
    return mGrid;
}

int NumberGrid::index(const int &row, const int &column) const {
    int index = (row * mWidth) + column;
    return index;
}

bool NumberGrid::indexValid(const int &row, const int &column) const {
    if (row >= 0 && row < mHeight && column < mWidth && column >= 0){
        return true;
    }
    return false;
    
}

bool NumberGrid::numberValid(const int &number) const {
    if (number >=0 && number <= mMaxValue){
        return true;
    }
    return false;
}

int NumberGrid::getNumber(const int &row, const int &column) const {
    if (indexValid(row, column)){
        int value = mGrid[index(row, column)];
        return value;
    }
    return -1;
}

void NumberGrid::setNumber(const int &row, const int &column, const int &number) {
    if (indexValid(row, column) && numberValid(number)){
        mGrid[index(row, column)] = number;
    }
}

void NumberGrid::setPPM(PPM &ppm) const {
    ppm.setHeight(mHeight);
    ppm.setWidth(mWidth);
    ppm.setMaxColorValue(63);
    for (int row = 0; row <= ppm.getHeight(); row++){
        for (int col = 0; col <= ppm.getWidth(); col++){
            if (getNumber(row, col) == 0){
                ppm.setPixel(row, col, 0, 0, 0);
            }
            else if (getNumber(row, col) == mMaxValue){
                ppm.setPixel(row, col, 63, 31, 31);
            }
            else if (getNumber(row, col) % 8 == 0){
                ppm.setPixel(row, col, 63, 63, 63);
            }
            else if (getNumber(row, col) % 8 == 1){
                ppm.setPixel(row, col, 63, 31, 31);
            }
            else if (getNumber(row, col) % 8 == 2){
                ppm.setPixel(row, col, 63, 63, 31);
            }
            else if (getNumber(row, col) % 8 == 3){
                ppm.setPixel(row, col, 31, 63, 31);
            }
            else if (getNumber(row, col) % 8 == 4){
                ppm.setPixel(row, col, 0, 0, 0);
            }
            else if (getNumber(row, col) % 8 == 5){
                ppm.setPixel(row, col, 31, 63, 63);
            }
            else if (getNumber(row, col) % 8 == 6){
                ppm.setPixel(row, col, 31, 31, 63);
            }
            else if (getNumber(row, col) % 8 == 7){
                ppm.setPixel(row, col, 63, 31, 63);
            }
        }
    }
}

void NumberGrid::setPPM(PPM &ppm, const ColorTable &colors) const {
    //ppm.setHeight(mHeight);
    //ppm.setWidth(mWidth);
    //ppm.setMaxColorValue(colors.getMaxChannelValue());
    if (colors.getNumberOfColors() >= 2){
        ppm.setHeight(mHeight);
        ppm.setWidth(mWidth);
        ppm.setMaxColorValue(colors.getMaxChannelValue());
        for (int row = 0; row < ppm.getHeight(); row++){
            for (int col = 0; col <= ppm.getWidth(); col++){
                if (getNumber(row, col) == getMaxNumber()){
                    Color end_color = colors[colors.getNumberOfColors() -1];
                    ppm.setPixel(row, col, end_color.getRed(), end_color.getGreen(), end_color.getBlue());
                }
                else{
                    Color new_color = colors[getNumber(row, col) % colors.getNumberOfColors()];
                    ppm.setPixel(row, col, new_color.getRed(), new_color.getGreen(), new_color.getBlue());
                }
            }
        }
    }
}
