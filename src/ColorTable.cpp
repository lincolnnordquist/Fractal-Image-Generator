#include "ColorTable.h"
#include <iostream>

Color::Color()
    : mRed(0), mGreen(0), mBlue(0){
}

Color::Color(const int &red, const int &green, const int &blue) :
    mRed(red), mGreen(green), mBlue(blue){
}

int Color::getRed() const {
    return mRed;
}

int Color::getGreen() const {
    return mGreen;
}

int Color::getBlue() const {
    return mBlue;
}

int Color::getChannel(const int &channel) const {
    if (channel == 0){
        return mRed;
    }
    else if (channel == 1){
        return mGreen;
    }
    else if (channel == 2){
        return mBlue;
    }
    return -1;
}

void Color::setRed(const int &value) {
    if (value >=0){
        mRed = value;
    }
}

void Color::setGreen(const int &value) {
    if (value >=0){
        mGreen = value;
    }
}

void Color::setBlue(const int &value) {
    if (value >=0){
        mBlue = value;
    }
}

void Color::setChannel(const int &channel, const int &value) {
    if (channel >= 0 && channel <= 3){
        if (value >= 0){
            if (channel == 0){
                setRed(value);
            }
            else if (channel == 1){
                setGreen(value);
            }
            else if (channel == 2){
                setBlue(value);
            }
        }
    }
}

void Color::invert(const int &max_color_value) {
    if (mRed <= max_color_value && mGreen <= max_color_value && mBlue <= max_color_value){
        mRed = max_color_value - mRed;
        mGreen = max_color_value - mGreen;
        mBlue = max_color_value - mBlue;
    }
    //if (mGreen <= max_color_value){
    //    mGreen = max_color_value - mGreen; }
    //if (mBlue <= max_color_value){
    //    mBlue = max_color_value - mBlue; }
}

bool Color::operator==(const Color &rhs) const {
    if (mRed == rhs.mRed && mGreen == rhs.mGreen && mBlue == rhs.mBlue){
        return true;
    }
    return false;
}

std::ostream& operator<<( std::ostream& os, const Color& color ){
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
}

ColorTable::ColorTable(const int &num_color) {
    mColors.resize(num_color);
}

int ColorTable::getNumberOfColors() const {
    return mColors.size();
}

void ColorTable::setNumberOfColors(const int &num_color) {
    mColors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const {
    if (i > (getNumberOfColors() -1)  || i < 0){
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;
    }
    return mColors[i];
}

Color& ColorTable::operator[](const int& i) {
    if (i > (getNumberOfColors() -1) || i < 0){
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;
    }
    return mColors[i];
}

void ColorTable::setRandomColor(const int &max_color_value, const int &position) {
    if (position >= 0 && position <= getNumberOfColors() && max_color_value >= 0){
        if (rand() % (max_color_value + 1) >= 0 && rand() % (max_color_value + 1) <= max_color_value){
        mColors[position].setRed(rand() % (max_color_value + 1));
        mColors[position].setGreen(rand() % (max_color_value + 1));
        mColors[position].setBlue(rand() % (max_color_value + 1));
        }
    }
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
    double rise = y2 - y1;
    double run = x2 - x1;
    return (rise/run);
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    int x_diff = x - x1;
    double fy = slope * x_diff;
    double y = fy + y1;
    return y;
}

void ColorTable::insertGradient(const Color &color1, const Color &color2, const int &position1, const int &position2) {
    //double red_step = (color2.getRed() - color1.getRed()) / (position2 - 1);
    //double green_step = (color2.getGreen() - color1.getGreen()) / (position2 - 1);
    //double blue_step = (color2.getBlue() - color1.getBlue()) / (position2 - 1);
    double red_slope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
    double green_slope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
    double blue_slope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);
    if (position1 < position2 && position1 >= 0 && position1 <= int(mColors.size()-1) && position2 >= 0 && position2 <= int(mColors.size() -1)){
        for (int position = position1; position <= position2 ; position++){
            //double red_g = (color1.getRed() + position) * red_step;
            //double green_g = (color1.getGreen() + position) * green_step;
            //double blue_g = (color1.getBlue() + position) * blue_step;
            double red_g = gradientValue(color1.getRed(), position1, red_slope, position);
            double green_g = gradientValue(color1.getGreen(), position1, green_slope, position);
            double blue_g = gradientValue(color1.getBlue(), position1, blue_slope, position);
            mColors[position].setRed(red_g);
            mColors[position].setGreen(green_g);
            mColors[position].setBlue(blue_g);
        }
    }
}

int ColorTable::getMaxChannelValue() const {
    int max_channel_value = 0;
    for(int i = 0; i < getNumberOfColors(); i++){
        if (mColors[i].getRed() > max_channel_value){
            max_channel_value = mColors[i].getRed();
        }
        if (mColors[i].getGreen() > max_channel_value){
            max_channel_value = mColors[i].getGreen();
        }
        if (mColors[i].getBlue() > max_channel_value){
            max_channel_value = mColors[i].getBlue();
        }
    }
    return max_channel_value;
}

void ColorTable::insertInvertedGradient(const Color& color1, const int& position1, const int& position2) {
    Color invertedColor = color1; 
    invertedColor.invert(255); 
    insertGradient(color1, invertedColor, position1, position2);
}

void ColorTable::insertEasyRandomGradient(const int& position1, const int& position2) {
    if (position1 < position2 && position1 >= 0 && position1 < getNumberOfColors() && position2 >= 0 && position2 < getNumberOfColors()) {
        setRandomColor(255, position1);
        setRandomColor(255, position2);
        insertGradient(mColors[position1], mColors[position2], position1, position2);
    }
}

void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue) {
  /* Convert Hue, Saturation, Value to Red, Green, Blue
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
   *
   * Inputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   *
   * Outputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   */
  if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
    red = green = blue = 0.0;
    std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
              << " hue: " << hue  << std::endl
              << " saturation: " << saturation << std::endl
              << " value: " << value << std::endl;
    return;
  }

  // chroma selects the strength of the "primary" color of the current area of the wheel
  double chroma = value * saturation;
  // hue2 selects which 60-degree wedge of the color wheel we are in
  double hue2 = hue / 60.0;
  // x selects the strength of the "secondary" color of the current area of the wheel
  double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
  if( hue2 >= 0 && hue2 < 1 ) {
    red = chroma;
    green = x;
    blue = 0.0;
  } else if( hue2 >= 1 && hue2 < 2 ) {
    red = x;
    green = chroma;
    blue = 0.0;
  } else if( hue2 >= 2 && hue2 < 3 ) {
    red = 0.0;
    green = chroma;
    blue = x;
  } else if( hue2 >= 3 && hue2 < 4 ) {
    red = 0.0;
    green = x;
    blue = chroma;
  } else if( hue2 >= 4 && hue2 < 5 ) {
    red = x;
    green = 0.0;
    blue = chroma;
  } else if( hue2 >= 5 && hue2 <= 6 ) {
    red = chroma;
    green = 0.0;
    blue = x;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  // m scales all color channels to obtain the overall brightness.
  double m = value - chroma;
  red = 255.0*( red + m );
  green = 255.0*( green + m );
  blue = 255.0*( blue + m );
}

void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value) {
  /* Red, Green, Blue to Convert Hue, Saturation, Value
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
   *
   * Inputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   *
   * Outputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   */
  if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
    hue = saturation = value = 0.0;
    std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
              << " red: " << red0  << std::endl
              << " green: " << green0 << std::endl
              << " blue: " << blue0 << std::endl;
    return;
  }

  double red   = red0 / 255.0;
  double green = green0 / 255.0;
  double blue  = blue0 / 255.0;

  // x_max helps identify the primary hue
  double x_max = red;
  if(green > x_max) { x_max = green; }
  if(blue > x_max) { x_max = blue; }
  value = x_max;

  double x_min = red;
  if(green < x_min) { x_min = green; }
  if(blue < x_min) { x_min = blue; }

  double chroma = x_max - x_min;

  if(chroma == 0) {
    hue = 0;
  } else if(value == red) {
    hue = 60.0 * (0 + (green - blue)/chroma);
  } else if(value == green) {
    hue = 60.0 * (2 + (blue - red)/chroma);
  } else if(value == blue) {
    hue = 60.0 * (4 + (red - green)/chroma);
  } else {
    hue = -720.0;
  }
  if(hue < 0.0) {
    hue += 360.0;
  }

  if(value == 0.0) {
    saturation = 0.0;
  } else {
    saturation = chroma/value;
  }

}

void Color::setFromHSV(const double& hue, const double& saturation, const double& value) {
    double red = getRed();
    double green = getGreen();
    double blue = getBlue();

    HSV_to_RGB(hue, saturation, value, red, green, blue);

    setRed(red);
    setGreen(green);
    setBlue(blue);
}

void Color::getHSV(double& hue, double& saturation, double& value) const {
    RGB_to_HSV(mRed, mGreen, mBlue, hue, saturation, value);
}

void ColorTable::insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {
    if (position1 >= 0 && position2 >= 0 && position1 < getNumberOfColors() && position2 < getNumberOfColors() && position1 < position2) {
        double color1Hue, color1Saturation, color1Value;
        double color2Hue, color2Saturation, color2Value;
        color1.getHSV(color1Hue, color1Saturation, color1Value);
        color2.getHSV(color2Hue, color2Saturation, color2Value);

        double hueSlope = gradientSlope(color1Hue, color2Hue, position1, position2);
        double saturationSlope = gradientSlope(color1Saturation, color2Saturation, position1, position2);
        double valueSlope = gradientSlope(color1Value, color2Value, position1, position2);
        
        for (int i = position1; i <= position2; i++) {
            double hue = gradientValue(color1Hue, position1, hueSlope, i);
            double saturation = gradientValue(color1Saturation, position1, saturationSlope, i);
            double value = gradientValue(color1Value, position1, valueSlope, i);

            Color color;
            color.setFromHSV(hue, saturation, value);
            mColors[i].setRed(color.getRed());
            mColors[i].setGreen(color.getGreen());
            mColors[i].setBlue(color.getBlue());
        }
    }
}