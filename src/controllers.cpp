#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include <string>
#include "MandelbrotSet.h"
#include "ThreadedGrid.h"

void showMenu( MenuData& menu_data, ActionData& action_data ){
    int len = menu_data.getNames().size();
    int i = 0;
    for (i = 0; i < len; i++){
        std::string name = menu_data.getNames()[i];
        action_data.getOS() << name << ") " << menu_data.getDescription(name) << std::endl;
    }
}

void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data){
    if (menu_data.getFunction(choice) == 0 && choice != "menu"){
        action_data.getOS() << "Unknown action " << "'"<< choice << "'." << std::endl;
    }
    else if (menu_data.getFunction(choice) == 0 && choice == "menu"){
        showMenu(menu_data, action_data);
    }
    else{
        menu_data.getFunction(choice)(action_data);

    }
}

void configureMenu( MenuData& menu_data ){
    menu_data.addAction("draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
    menu_data.addAction("write", writeUserImage, "Write output image to file.");
    menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
    menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
    menu_data.addAction("#", commentLine, "Comment to end of line.");
    menu_data.addAction("size", setSize, "Set the size of input image 1.");
    menu_data.addAction("max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
    menu_data.addAction("channel", setChannel, "Set a channel value in input image 1.");
    menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1.");
    menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
    menu_data.addAction("quit", quit, "Quit.");
    menu_data.addAction("read2", readUserImage2, "Read file into input image 2.");
    menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2.");
    menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2.");
    menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2.");
    menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2.");
    menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number.");
    menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number.");
    menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number.");
    menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number.");
    menu_data.addAction("red-gray", grayFromRed, "Set output image by grayscale from red on input image 1.");
    menu_data.addAction("green-gray", grayFromGreen, "Set output image by grayscale from green on input image 1.");
    menu_data.addAction("blue-gray", grayFromBlue, "Set output image by grayscale from blue on input image 1.");
    menu_data.addAction("linear-gray", grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
    menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1.");
    menu_data.addAction("box", drawBox, "Draw a box shape in input image 1.");
    menu_data.addAction("square", drawSquare, "Draw a square shape in input image 1.");
    menu_data.addAction("orange", orangeFilter, "Set output image from orange filter on input image 1.");
    menu_data.addAction("grid", configureGrid, "Configure the grid.");
    menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
    menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
    menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
    menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
    menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
    menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
    menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
    menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
    menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal.");
    menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
    menu_data.addAction("complex-fractal", setComplexFractal, "Choose to make a complex plane.");
    menu_data.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
    menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
    menu_data.addAction("set-inverted-color-gradient", setInvertedColorGradient, "Smoothly set the values for a range of slots in the color table, using a color and its inverse.");
    menu_data.addAction("fractal-zoom", zoomPlane, "Zoom in or out of the complex plane.");
    menu_data.addAction("set-easy-random-color-gradient", setEasyRandomColorGradient, "Smoothly set the values for a range of slots in the color table, using two random colors.");
    menu_data.addAction("fractal-right", panPlaneRight, "Pan complex plane right.");
    menu_data.addAction("fractal-left", panPlaneLeft, "Pan complex plane left.");
    menu_data.addAction("fractal-up", panPlaneUp, "Pan complex plane up.");
    menu_data.addAction("fractal-down", panPlaneDown, "Pan complex plane down.");
    menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
    menu_data.addAction("set-hsv-gradient", setHueSaturationValueGradient, "Smoothly set colors for a range of slots in the color table, based on change of hue, saturation, and value.");
}

int imageMenu(std::istream& is, std::ostream& os){
    ActionData action_data(is, os);
    action_data.setGrid(new ComplexFractal);
    MenuData menu_data;
    configureMenu(menu_data);
    //showMenu(menu_data, action_data);
    std::string choice;
    while(action_data.getDone() != true && action_data.getIS().good()){
        choice = getChoice(action_data);
        takeAction(choice, menu_data, action_data);
    }
    return 0;
}


int assignment1(std::istream& is, std::ostream& os) {
    ActionData action_data(is, os);
    return askQuestions3(action_data);
}

int assignment2( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
    diagonalQuadPattern(action_data);
    copyImage(action_data);
    drawAsciiImage(action_data);
    return 0;
}

int assignment3( std::istream& is, std::ostream& os ) {
    ActionData action_data(is, os);
    stripedDiagonalPattern(action_data);
    copyImage(action_data);
    writeUserImage(action_data);
    return 0;
}

int flag_romania(std::istream& is, std::ostream& os) {
    ActionData action_data(is,os);
    flagRomaniaPattern(action_data);
    copyImage(action_data);
    writeUserImage(action_data);
    return 0;
}

void setComplexFractal(ActionData& action_data) {
    ComplexFractal* cf = new ComplexFractal();
    action_data.setGrid(cf);
}

void setJuliaFractal(ActionData& action_data) {
    JuliaSet* js = new JuliaSet();
    action_data.setGrid(js);
}

void setMandelbrotFractal(ActionData &action_data) {
    MandelbrotSet* mbs = new MandelbrotSet();
    action_data.setGrid(mbs);
}