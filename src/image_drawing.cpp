#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include <cmath>
#include "ThreadedGrid.h"

void setSize( ActionData& action_data ){
    int height = getInteger(action_data, "Height? ");
    int width = getInteger(action_data, "Width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ){
    int val = getInteger(action_data, "Max color value? ");
    action_data.getInputImage1().setMaxColorValue(val);
}

void setChannel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int chan = getInteger(action_data, "Channel? ");
    int val = getInteger(action_data, "Value? ");
    action_data.getInputImage1().setChannel(row, col, chan, val);
}

void setPixel( ActionData& action_data ){
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getInputImage1().setPixel(row, col, red, green, blue);
}

void clearAll( ActionData& action_data ){
    int height = action_data.getInputImage1().getHeight();
    int width = action_data.getInputImage1().getWidth();

    for (int i = 0; i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setPixel(i, i2, 0, 0, 0);
        } 
    }
}

void diagonalQuadPattern( ActionData& action_data) {
    (void) action_data.getIS();
    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);

    int i = height/2;
    int i2 = 0;
    //red channel 0
    for (;i < height; i++){
        for (int i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 0, 255);
        } 
    }
    //green channel 1
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
           action_data.getInputImage1().setChannel(i, i2, 1, ( 2*i + 2*i2 ) % 256 ); 
        }
    }
    //blue channel 2 
    for(i = 0; i < height; i++){
        i2 = width/2;
        for (;i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 2, 255);
        }
    }
}

void stripedDiagonalPattern( ActionData& action_data ){
    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");
    action_data.getInputImage1().setHeight(height);
    action_data.getInputImage1().setWidth(width);
    int val = (height + width) / 3;
    if (val >= 255){
        action_data.getInputImage1().setMaxColorValue(255);
    }
    else {
    action_data.getInputImage1().setMaxColorValue((height + width) / 3);
    }
//red 
    int i = height/2;
    int i2;
    for (;i < height; i++){
        if (i % 3 != 0) {
            for (i2 = 0; i2 < width; i2++){
                action_data.getInputImage1().setChannel(i, i2, 0, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }
//green
    for(i = 0; i < height; i++){
        for(i2 = 0; i2 < width; i2++){
            action_data.getInputImage1().setChannel(i, i2, 1, (i + width - i2 -1) % (action_data.getInputImage1().getMaxColorValue() + 1));
        }
    }
//blue
    for (i = 0; i < height; i++){
        for (i2 = 0; i2 < width; i2++){
            if (i2 >= i){
                action_data.getInputImage1().setChannel(i, i2, 2, action_data.getInputImage1().getMaxColorValue());
            }
        }
    }
}

void flagRomaniaPattern( ActionData& action_data ){
    int height = getInteger(action_data, "Image height? ");
    action_data.getInputImage1().setHeight(height);
    int width = (height * 3) / 2;
    action_data.getInputImage1().setWidth(width);
    action_data.getInputImage1().setMaxColorValue(255);
    //int col_1 = p.getWidth() / 3
    //int col_2 = p.getWidth() / 3 + col_1
    //int col_3 = p.getWidth() / 3 + col_1 + col_2

    //blue section 
    int i;
    int i2 = 0;
    for (i = 0; i < height; i++){
        for (i2 = 0; i2 < width / 3; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 0);
                action_data.getInputImage1().setChannel(i, i2, 1, 43);
                action_data.getInputImage1().setChannel(i, i2, 2, 127);
        }
    }
    //yellow section
    for (i = 0; i < height; i++){
        for (i2 = width / 3; i2 < (width / 3) * 2 ; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 252);
                action_data.getInputImage1().setChannel(i, i2, 1, 209);
                action_data.getInputImage1().setChannel(i, i2, 2, 22);
        }
    }
    //red section
    for (i = 0; i < height; i++){
        for (i2 = (width / 3) * 2; i2 < width ; i2++ ){
                action_data.getInputImage1().setChannel(i, i2, 0, 206);
                action_data.getInputImage1().setChannel(i, i2, 1, 17);
                action_data.getInputImage1().setChannel(i, i2, 2, 38);
        }
    }
}
void drawCircle(ActionData &action_data) {
    int c_row = getInteger(action_data, "Center Row? ");
    int c_col = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for (int row = c_row - radius; row <= c_row + radius; row++){
        for (int col = c_col - radius; col <= c_col + radius; col++){
            double dist = sqrt(((row - c_row)*(row - c_row)) + ((col - c_col)*(col - c_col)));
            if (dist <= radius){
                action_data.getInputImage1().setPixel(row, col, red, green, blue);
            }
        }
    }
}

void drawBox(ActionData &action_data) {
    int t_row = getInteger(action_data, "Top Row? ");
    int l_col = getInteger(action_data, "Left Column? ");
    int b_row = getInteger(action_data, "Bottom Row? ");
    int r_col = getInteger(action_data, "Right Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for (int row = t_row; row <= b_row; row++ ){
        for (int col = l_col; col <= r_col; col++){
            action_data.getInputImage1().setPixel(row, col, red, green, blue);
        }
    }
}

void drawSquare(ActionData &action_data) {
    int s_row = getInteger(action_data, "Row? ");
    int s_col = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    double start_row = s_row - (size/2);
    double end_row = s_row + (size/2);
    double start_col = s_col - (size/2);
    double end_col = s_col + (size/2);
    for (int row = start_row ; row <= end_row; row++ ){
        for (int col = start_col; col <= end_col; col++){
            if (row >= start_row && row <= end_row && col >= start_col && col <= end_col){
                action_data.getInputImage1().setPixel(row, col, red, green, blue);
        }
    }
}
}

void configureGrid(ActionData &action_data) {
    int height = getInteger(action_data, "Grid Height? ");
    int width = getInteger(action_data, "Grid Width? ");
    int max_value = getInteger(action_data, "Grid Max Value? ");
    //NumberGrid& a_grid = action_data.getGrid();
    action_data.getGrid().setGridSize(height, width);
    action_data.getGrid().setMaxNumber(max_value);
}

void setGrid(ActionData &action_data) {
    int row = getInteger(action_data, "Grid Row? ");
    int col = getInteger(action_data, "Grid Column? ");
    int value = getInteger(action_data, "Grid Value? ");
    //NumberGrid& a_grid = action_data.getGrid();
    action_data.getGrid().setNumber(row, col, value);
}

void applyGrid(ActionData &action_data){
   action_data.getGrid().setPPM(action_data.getOutputImage());
}

void setColorTableSize(ActionData &action_data) {
    int size = getInteger(action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData &action_data) {
    int position = getInteger(action_data, "Position? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getTable()[position] = Color(red, green, blue);
}

void setRandomColor(ActionData &action_data) {
    int position = getInteger(action_data, "Position? ");
    action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData &action_data) {
    int position_1 = getInteger(action_data, "First position? ");
    int red_1 = getInteger(action_data, "First red? ");
    int green_1 = getInteger(action_data, "First green? ");
    int blue_1 = getInteger(action_data, "First blue? ");
    int position_2 = getInteger(action_data, "Second position? ");
    int red_2 = getInteger(action_data, "Second red? ");
    int green_2 = getInteger(action_data, "Second green? ");
    int blue_2 = getInteger(action_data, "Second blue? ");
    action_data.getTable().insertGradient(Color(red_1, green_1, blue_1), Color(red_2, green_2, blue_2), position_1, position_2);
}

void applyGridColorTable(ActionData &action_data) {
    action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setFractalPlaneSize(ActionData &action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != 0){
        double min_x = getDouble(action_data, "Min X? ");
        double max_x = getDouble(action_data, "Max X? ");
        double min_y = getDouble(action_data, "Min Y? ");
        double max_y = getDouble(action_data, "Max Y? ");
        //action_data.setGrid(cfptr->setPlaneSize(min_x, max_x, min_y, max_y));
        cfptr->setPlaneSize(min_x, max_x, min_y, max_y);
    }
    else{
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size."<< std::endl; 
    }
}

void calculateFractal(ActionData &action_data) {
    //ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(cfptr);
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData &action_data) {
    JuliaSet *jsptr = dynamic_cast<JuliaSet*>(&action_data.getGrid());
    if (jsptr != 0){
        double a = getDouble(action_data, "Parameter a? ");
        double b = getDouble(action_data, "Parameter b? ");
        jsptr->setParameters(a, b);
    }
    else{
        action_data.getOS() << "Not a JuliaSet object. Can't set parameters."<< std::endl; 
    }
}

void setInvertedColorGradient(ActionData& action_data) {
    int position_1 = getInteger(action_data, "First position? ");
    int red_1 = getInteger(action_data, "First red? ");
    int green_1 = getInteger(action_data, "First green? ");
    int blue_1 = getInteger(action_data, "First blue? ");
    int position_2 = getInteger(action_data, "Second position? ");
    action_data.getTable().insertInvertedGradient(Color(red_1, green_1, blue_1), position_1, position_2);
}

void zoomPlane(ActionData& action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != 0){
        double zoom_factor = getDouble(action_data, "Zoom Factor? ");
        cfptr->zoomPlane(zoom_factor);
    }
    else{
        action_data.getOS() << "Not a ComplexFractal object. Can't zoom plane."<< std::endl; 
    }

}

void setEasyRandomColorGradient(ActionData& action_data) {
    // will set a random gradient in the color table, using the insertEasyRandomGradient() method. Prompts the user for “First position? ” and “Second position? “.
    int position_1 = getInteger(action_data, "First position? ");
    int position_2 = getInteger(action_data, "Second position? ");
    action_data.getTable().insertEasyRandomGradient(position_1, position_2);
}

void panPlaneRight(ActionData& action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != nullptr) {
        cfptr->panPlaneRight(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." << std::endl;
    }
}

void panPlaneLeft(ActionData& action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != nullptr) {
        cfptr->panPlaneLeft(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." << std::endl;
    }
}

void panPlaneUp(ActionData& action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != nullptr) {
        cfptr->panPlaneUp(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." << std::endl;
    }
}

void panPlaneDown(ActionData& action_data) {
    ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
    if (cfptr != nullptr) {
        cfptr->panPlaneDown(0.1);
    } else {
        action_data.getOS() << "Not a ComplexFractal object. Can't pan plane." << std::endl;
    }
}

void calculateFractalSingleThread(ActionData &action_data) {
    action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void setHueSaturationValueGradient(ActionData& action_data) {
    int firstPosition = getInteger(action_data, "First position? ");
    double firstHue = getDouble(action_data, "First hue? ");
    double firstSaturation = getDouble(action_data, "First saturation? ");
    double firstValue = getDouble(action_data, "First value? ");

    int secondPosition = getInteger(action_data, "Second position? ");
    double secondHue = getDouble(action_data, "Second hue? ");
    double secondSaturation = getDouble(action_data, "Second saturation? ");
    double secondValue = getDouble(action_data, "Second value? ");

    Color color1;
    Color color2;

    color1.setFromHSV(firstHue, firstSaturation, firstValue);
    color2.setFromHSV(secondHue, secondSaturation, secondValue);

    action_data.getTable().insertHueSaturationValueGradient(color1, color2, firstPosition, secondPosition);
}