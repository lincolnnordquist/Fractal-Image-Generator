#include "AppData.h"
#include "image_menu.h"
#include "ActionData.h"

AppData::AppData(int height, int width) 
    : mHeight(height), mWidth(width), mMaxNumber(200), mInteractionMode(IM_FRACTAL), 
      mFractalMode(M_JULIA), mNumColor(256), mColor1(Color(0, 0, 0)), mColor2(Color(255, 255, 255)), mColor3(0, 50, 35),
      mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mA(0.45), mB(-0.32), 
      mInputStream(), mOutputStream(), mActionData(mInputStream, mOutputStream), 
      mMenuData(), mDebug(0), mColorTableMode(CT_GRADIENT), mHSVColor(false) {
    configureMenu(mMenuData);
    mActionData.setGrid(new ComplexFractal);
    setColorTable();
    createFractal();
}

void AppData::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int AppData::getHeight() const {
  return mHeight;
}

int AppData::getWidth() const {
  return mWidth;
}

PPM& AppData::getOutputImage() {
  return mActionData.getOutputImage();
}

ColorTable& AppData::getColorTable() {
    return mActionData.getTable();
    // double check this
}

void AppData::createJulia1() {
//   selectJulia();
//   configureGrid(200);
//   juliaParameters(0.45, -0.32);
//   fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
//   fractalCalculate();
//   gridApplyColorTable();

    mColor1 = Color(102,252,3);
    mColor2 = Color(26,10,255);
    mNumColor = 30;
    selectJulia();
    configureGrid(200);
    juliaParameters(0.45, -0.32);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();
    setColorTable();
    gridApplyColorTable();
}

void AppData::createJulia2() {
//   selectJulia();
//   configureGrid(100);
//   juliaParameters( -0.8, 0.156);
//   fractalPlaneSize(-1.5, 1.5, -1.5, 1.5);
//   fractalCalculate();
//   gridApplyColorTable();

    mColor1 = Color(0,50,100);
    mColor2 = Color(205,0,0);
    selectJulia();
    configureGrid(200);
    juliaParameters( -0.8, 0.156);
    fractalPlaneSize(-1.5, 1.5, -1.5, 1.5);
    fractalCalculate();
    setColorTable();
    gridApplyColorTable();
}

void AppData::createMandelbrot1() {
    // selectMandelbrot();
    // configureGrid(200);
    // fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    // fractalCalculate();
    // gridApplyColorTable();

    mColor1 = Color(255, 123, 0);
    mColor2 = Color(255, 234, 0);
    selectMandelbrot();
    configureGrid(200);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();
    setColorTable();
    gridApplyColorTable();
}

void AppData::createMandelbrot2() {
    // selectMandelbrot();
    // configureGrid(100);
    // fractalPlaneSize(-2, -1.3, -0.1, 0.1);
    // fractalCalculate();
    // gridApplyColorTable();

    mColor1 = Color(220,9,158);
    mColor2 = Color(15,153,168);
    selectMandelbrot();
    configureGrid(200);
    fractalPlaneSize(-2, -1.3, -0.1, 0.1);
    fractalCalculate();
    setColorTable();
    gridApplyColorTable();
}

void AppData::createComplexFractal1() {
    selectComplexFractal();
    configureGrid(200);
    fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
    fractalCalculate();
    gridApplyColorTable();
}

void AppData::createComplexFractal2() {
    selectComplexFractal();
    configureGrid(450);
    fractalPlaneSize(-1.9, 1.2, -1.2, 1.9);
    fractalCalculate();
    gridApplyColorTable();
}

void AppData::clearStreams() {
    mOutputStream.clear();
    mOutputStream.str("");
    mInputStream.clear();
    mInputStream.str("");
}

void AppData::runCommand(const std::string& choice){
  std::cout << choice << " " << mInputStream.str() << std::endl;
  takeAction(choice,mMenuData,mActionData);
  std::cout << mOutputStream.str() << std::endl;

// if (mDebug != 0){
//         std::cout << choice << " " << mInputStream.str() << std:: endl;
//         takeAction(choice, mMenuData, mActionData);
//         std::cout << mOutputStream.str() << std::endl;
//     }
//     else{
//         takeAction(choice, mMenuData, mActionData);
//     }
//     clearStreams();
}

void AppData::selectJulia() {
    std::string choice = "julia";
    clearStreams();
    setFractalMode(M_JULIA);
    runCommand(choice);
}

void AppData::selectMandelbrot() {
    std::string choice = "mandelbrot";
    clearStreams();
    setFractalMode(M_MANDELBROT);
    runCommand(choice);
}

void AppData::selectComplexFractal() {
    std::string choice = "complex-fractal";
    clearStreams();
    setFractalMode(M_COMPLEX);
    runCommand(choice);
}

void AppData::configureGrid(int max){
    std::string choice;
    clearStreams();
    {
        std::stringstream tmp;
        tmp << mHeight << " " << mWidth << " " << max;
        mInputStream.str(tmp.str());
    }
    choice = "grid";
    runCommand(choice);
}

void AppData::juliaParameters(double a, double b) {
  std::string choice;
  clearStreams();
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
    choice = "julia-parameters";
    runCommand(choice);
}

void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
  std::string choice;
  clearStreams();
  {
    std::stringstream tmp;
    tmp << x_min << " " << x_max << " "<< y_min << " " << y_max;
    mInputStream.str(tmp.str());
  }
    choice = "fractal-plane-size";
    runCommand(choice);
}

void AppData::fractalCalculate() {
  std::string choice = "fractal-calculate";
  clearStreams();
  runCommand(choice);
}

void AppData::gridApplyColorTable() {
  std::string choice = "grid-apply-color-table";
  clearStreams();
  runCommand(choice);
}

void AppData::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

AppData::InteractionMode AppData::getInteractionMode() const {
    return mInteractionMode;
}

void AppData::setColorTable() {
  std::string choice;
  clearStreams();
  {
    std::stringstream tmp;
    tmp << mNumColor;
    mInputStream.str(tmp.str());
  }
  choice = "set-color-table-size";
  runCommand(choice);

  if (mHSVColor) {
    clearStreams();
    {
      std::stringstream tmp;
      int half = mNumColor / 2;
      double h1, s1, v1;
      mColor1.getHSV(h1, s1, v1);
      double h2, s2, v2;
      mColor2.getHSV(h2, s2, v2);
      tmp << 0 << " " << h1 << " " << s1 << " " << v1 << " " 
      << half << " " << h2 << " " << s2 << " " << v2;
      mInputStream.str(tmp.str());
    }

    runCommand("set-hsv-gradient");

    clearStreams();
    {
      std::stringstream tmp;
      int half = mNumColor / 2;
      double h2, s2, v2;
      mColor2.getHSV(h2, s2, v2);
      double h3, s3, v3;
      mColor3.getHSV(h3, s3, v3);
      tmp << half << " " << h2 << " " << s2 << " " << v2 << " " 
      << mNumColor - 1 << " " << h3 << " " << s3 << " " << v3;
      mInputStream.str(tmp.str());
    }

    runCommand("set-hsv-gradient");
  }

 clearStreams();
choice = "set-color-gradient";

    {
    std::stringstream tmp;
    tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " 
    << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
    mInputStream.str(tmp.str());
  }
  runCommand(choice);
  clearStreams();
  choice = "set-color-gradient";
  {
    std::stringstream tmp;
    tmp << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue() << " " 
    << mNumColor-1 << " " << mColor3.getRed() << " " << mColor3.getGreen() << " " << mColor3.getBlue();
    mInputStream.str(tmp.str());
  }
    runCommand(choice);


  if (mColorTableMode == CT_RANDOM3) {
    set3RandomColors();
  } else if (mColorTableMode == CT_RANDOM) {
    setAllRandomColors();
  } else if (mColorTableMode == CT_REVERSE) {
    setReverseGradient();
  }
}

void AppData::decreaseColorTableSize() {
  ColorTable& ct = mActionData.getTable();
  if (ct.getNumberOfColors() > 10){
    double new_num_colors = ct.getNumberOfColors() / 1.1;
    mNumColor = new_num_colors;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::increaseColorTableSize() {
  ColorTable& ct = mActionData.getTable();
  if (ct.getNumberOfColors() < 1024){
    double new_num_colors = ct.getNumberOfColors() * 1.1;
    mNumColor = new_num_colors;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::randomColor1() {
  //ColorTable& ct = mActionData.getTable();
  PPM& p = mActionData.getOutputImage();
  int max_color_value = p.getMaxColorValue();
  mColor1.setRed(rand() % (max_color_value + 1));
  mColor1.setGreen(rand() % (max_color_value + 1));
  mColor1.setBlue(rand() % (max_color_value + 1));
  setColorTable();
  gridApplyColorTable();
}

void AppData::randomColor2() {
  //ColorTable& ct = mActionData.getTable();
  PPM& p = mActionData.getOutputImage();
  int max_color_value = p.getMaxColorValue();
  mColor2.setRed(rand() % (max_color_value + 1));
  mColor2.setGreen(rand() % (max_color_value + 1));
  mColor2.setBlue(rand() % (max_color_value + 1));
  setColorTable();
  gridApplyColorTable();
}

void AppData::randomColor3(){
  PPM& p = mActionData.getOutputImage();
  int max_color_value = p.getMaxColorValue();
  mColor2.setRed(rand() % (max_color_value + 1));
  mColor2.setGreen(rand() % (max_color_value + 1));
  mColor2.setBlue(rand() % (max_color_value + 1));
  setColorTable();
  gridApplyColorTable();
}

void AppData::zoomIn() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  mMinX += dx;
  mMaxX -= dx;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinY += dy;
  mMaxY -= dy;
}

void AppData::zoomOut() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double min_x = mMinX - dx;
  double max_x = mMaxX + dx;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  double min_y = mMinY - dy;
  double max_y = mMaxY + dy;
  if (min_x >= -2.0 && min_y >= -2.0 && max_x <= 2.0 && max_y <= 2.0){
    mMinX -= dx;
    mMaxX += dx;
    mMinY -= dy;
    mMaxY += dy;
  }
}

void AppData::moveLeft() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  double min_x = mMinX - dx;
  if (min_x >= -2.0){
    mMinX -= dx;
    mMaxX -= dx;
  }
}

void AppData::moveRight() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  double max_x = mMaxX + dx;
  if (max_x <= 2.0){
    mMinX += dx;
    mMaxX += dx;
  }
}

void AppData::moveDown() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  double min_y = mMinY - dy;
  if (min_y >= -2.0){
    mMinY -= dy;
    mMaxY -= dy;
  }
}

void AppData::moveUp() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  double max_y = mMaxY + dy;
  if (max_y <= 2.0){
    mMinY += dy;
    mMaxY += dy;
  }
}

void AppData::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}

AppData::FractalMode AppData::getFractalMode() const {
    return mFractalMode;
}

void AppData::increaseMaxNumber() {
  if (mMaxNumber < 2048){
    mMaxNumber *= 1.1;
  }
}

void AppData::decreaseMaxNumber() {
  if (mMaxNumber > 11){
    mMaxNumber /= 1.1;
  }
}

void AppData::setAB(int x, int y) {
  ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&mActionData.getGrid());
  if (getFractalMode() == M_MANDELBROT && cfptr != 0){
    mA = mMinX + x * cfptr->getDeltaX();
    mB = mMinY + y * cfptr->getDeltaY();
  }
}

void AppData::resetPlane() {
  mMinX = -2.0;
  mMinY = -2.0;
  mMaxX = 2.0;
  mMaxY = 2.0;
}

void AppData::createFractal(){
  if (mFractalMode == M_MANDELBROT) {
    selectMandelbrot();
  } else if (mFractalMode == M_JULIA) {
    selectJulia();
    juliaParameters(mA, mB);
  } else if (mFractalMode == M_COMPLEX) {
    selectComplexFractal();
  }
  configureGrid(mMaxNumber);
  fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
  setColorTable();
  fractalCalculate();
  gridApplyColorTable();
}

void AppData::nextColorTableMode() {
    if (mColorTableMode == CT_GRADIENT) {
        mColorTableMode = CT_RANDOM3;
    } else if (mColorTableMode == CT_RANDOM3) {
        mColorTableMode = CT_RANDOM;
    } 
    else if (mColorTableMode == CT_RANDOM){
        mColorTableMode = CT_REVERSE;
    } else {
        mColorTableMode = CT_GRADIENT;}

    setColorTable();
    gridApplyColorTable();
}

AppData::ColorTableMode AppData::getColorTableMode() const {
    return mColorTableMode;
}

void AppData::set3RandomColors() {
    // clearStreams();
    // std::string choice;
    // int num_colors = mActionData.getTable().getNumberOfColors();
    // int first = 0;
    // int middle = num_colors / 2;
    // int last = num_colors - 1;

    // // first position
    // mInputStream.str(std::to_string(first));
    // choice = "set-random-color";
    // runCommand(choice);

    // // middle position
    // mInputStream.str(std::to_string(middle));
    // choice = "set-random-color";
    // runCommand(choice);

    // // last position
    // mInputStream.str(std::to_string(last));
    // choice = "set-random-color";
    // runCommand(choice);

    clearStreams();
    std::string choice = "set-random-color";
    {
        std::stringstream tmp;
        tmp << 0;
        mInputStream.str(tmp.str());
    }
    runCommand(choice);
    clearStreams();
    {
        std::stringstream tmp;
        tmp << mActionData.getTable().getNumberOfColors() - 1;
        mInputStream.str(tmp.str());
    }
    runCommand(choice);
    clearStreams();
    {
        std::stringstream tmp;
        tmp << mActionData.getTable().getNumberOfColors() - 2;
        mInputStream.str(tmp.str());
    }
    runCommand(choice);
}

void AppData::setAllRandomColors() {
    std::string choice;
    int num_colors = mActionData.getTable().getNumberOfColors();

    for (int i = 0; i < num_colors; ++i) {
        mInputStream.str(std::to_string(i));
        choice = "set-random-color";
        runCommand(choice);
    }
}

void AppData::setReverseGradient() {
    std::string choice;
    int num_colors = mActionData.getTable().getNumberOfColors();
    int half = num_colors / 2;

    // first half
    mInputStream.str("0 " + std::to_string(half) + " color1 color2");
    choice = "set-color-gradient";
    runCommand(choice);

    // second half 
    mInputStream.str(std::to_string(half) + " " + std::to_string(num_colors - 1) + " color2 color1");
    choice = "set-color-gradient";
    runCommand(choice);
}

void AppData::increaseChannel(Color& color, int channel) {

  int change = color.getChannel(channel);
  change += 10; 
  if ( change >= 255 ) {
    change = 255;
  }
  
  color.setChannel(channel,change);
  setColorTable();
  gridApplyColorTable();
}

void AppData::decreaseChannel(Color& color, int channel) {

  int change = color.getChannel(channel);
  change -= 10; 
  if ( change <= 0 ) {
    change = 0;
  }
  
  color.setChannel(channel,change);
  setColorTable();
  gridApplyColorTable();
}

Color& AppData::fetchColor() {
  if ( mInteractionMode == IM_COLOR1 ) {
    
    return mColor1;

  } else if ( mInteractionMode == IM_COLOR2 ) {
     
    return mColor2;
 
  } else if ( mInteractionMode == IM_COLOR3 ) {
    return mColor3;
  } else {
    Color color;
    static Color staticColor;
    staticColor = static_cast<Color>(color);
    return staticColor;
  }
}

void AppData::increaseRed() {
  increaseChannel(fetchColor(), 0);
}

void AppData::decreaseRed() {
  decreaseChannel(fetchColor(), 0);
}

void AppData::increaseGreen() {
  increaseChannel(fetchColor(), 1);
}

void AppData::decreaseGreen() {
  decreaseChannel(fetchColor(), 1);
}

void AppData::increaseBlue() {
  increaseChannel(fetchColor(), 2);
}

void AppData::decreaseBlue() {
  decreaseChannel(fetchColor(), 2);
}

void AppData::toggleHSVColor() {
  if (mHSVColor == false) {
    mHSVColor = true;
  } else {
    mHSVColor = false;
  }

  setColorTable();
  gridApplyColorTable();
}