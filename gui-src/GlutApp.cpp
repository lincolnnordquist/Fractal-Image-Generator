#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mData(height, width) {
}

void GlutApp::setSize(int height, int width) {
    mData.setSize(height, width);
    mData.createFractal();
}

int GlutApp::getHeight() const {
  return mData.getHeight();
}
int GlutApp::getWidth() const {
  return mData.getWidth();
}

void GlutApp::display() {
    if (mData.getInteractionMode() == AppData::IM_FRACTAL) {
        displayOutputImage();
    } else if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
        displayColorTable();
    } else if (mData.getInteractionMode() == AppData::IM_COLOR1 || mData.getInteractionMode() == AppData::IM_COLOR2 || mData.getInteractionMode() == AppData::IM_COLOR3){
        displayColorTable();
    }
}

void GlutApp::displayOutputImage() {
    PPM& p = mData.getOutputImage();
    double max = static_cast <double> (p.getMaxColorValue());
    double r,g,b;
    int row, column;
    glBegin(GL_POINTS);
    for (row = 0; row < p.getHeight(); row++) {
        for (column = 0; column < p.getWidth(); column++) {
            r = p.getChannel(row, column, 0) / max;
            g = p.getChannel(row, column, 1) / max;
            b = p.getChannel(row, column, 2) / max;
            glColor3d(r, g, b);
            glVertex2i(column, p.getHeight() - row-1);
        }
    }
    glEnd();
}

void GlutApp::displayColorTable() {
    PPM& p = mData.getOutputImage();
    ColorTable& c = mData.getColorTable();
    int row, column;
    glBegin(GL_POINTS);
        for (row=0; row < p.getHeight(); row++) {
            for (column = 0; column < p.getWidth(); column++) {
                int i = column * c.getNumberOfColors() / p.getWidth();
                double r = c[i].getRed() / 255.0;
                double g = c[i].getGreen() / 255.0;
                double b = c[i].getBlue() / 255.0;
                glColor3d(r, g, b);
                glVertex2i(column, p.getHeight() - row - 1);
            }
        }
        glEnd();
}

bool GlutApp::keyboard(unsigned char c) {
    bool shouldUpdate = false;

    switch(c) {
        case 'J':
            mData.createJulia1();
            shouldUpdate = true;
            break;
        case 'j':
            mData.createJulia2();
            shouldUpdate = true;
            break;
        case 'M':
            mData.createMandelbrot1();
            shouldUpdate = true;
            break;
        case 'm':
            mData.createMandelbrot2();
            shouldUpdate = true;
            break;
        case 'C':
            mData.createComplexFractal1();
            shouldUpdate = true;
            break;
        case 'c':
            mData.createComplexFractal2();
            shouldUpdate = true;
            break;
        case 'T':
            mData.setInteractionMode(AppData::IM_COLORTABLE);
            shouldUpdate = true;
            break;
        case 't':
            mData.setInteractionMode(AppData::IM_FRACTAL);
            shouldUpdate = true;
            break;
        case 'b':
            mData.setFractalMode(AppData::M_MANDELBROT);
            mData.createFractal();
            shouldUpdate = true;
            break;
        case 'n':
            mData.setFractalMode(AppData::M_JULIA);
            mData.createFractal();
            shouldUpdate = true;
            break;
        case 'F':
            mData.setFractalMode(AppData::M_COMPLEX);
            mData.createFractal();
            shouldUpdate = true;
            break;
        case '>':
        case '.':
            mData.increaseColorTableSize();
            shouldUpdate = true;
            break;
        case '<':
        case ',':
            mData.decreaseColorTableSize();
            shouldUpdate = true;
            break;
        case 'r':
            if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
                mData.randomColor1();
                shouldUpdate = true;
            }
            break;
        case 'R':
            if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
                mData.randomColor2();
                shouldUpdate = true;
            }
            break;
        case 'z':
            mData.zoomIn();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case 'Z':
            mData.zoomOut();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case '+':
        case '=':
            mData.increaseMaxNumber();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case '-':
        case '_':
            mData.decreaseMaxNumber();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case '0':
            mData.nextColorTableMode();
            shouldUpdate = true;
            break;
        case '1':
            mData.setInteractionMode(AppData::IM_COLOR1);
            shouldUpdate = true;
            break;
        case '2':
            mData.setInteractionMode(AppData::IM_COLOR2);
            shouldUpdate = true;
            break;
        case '3':
            mData.setInteractionMode(AppData::IM_COLOR3);
            shouldUpdate = true;
            break;
        case 'Y':
            mData.increaseRed();
            shouldUpdate = true;
            break;
        case 'y':
            mData.decreaseRed();
            shouldUpdate = true;
            break;
        case 'U':
            mData.increaseGreen();
            shouldUpdate = true;
            break;
        case 'u':
            mData.decreaseGreen();
            shouldUpdate = true;
            break;
        case 'I':
            mData.increaseBlue();
            shouldUpdate = true;
            break;
        case 'i':
            mData.decreaseBlue();
            shouldUpdate = true;
            break;
        case 'e':
            if (mData.getInteractionMode() == AppData::IM_COLORTABLE){
            mData.randomColor3();
            shouldUpdate = true;
            }
            break;
        case 'h':
          mData.toggleHSVColor();
          shouldUpdate = true;
          break;
        default:
            break;
    }

    return shouldUpdate;
}

bool GlutApp::special(unsigned char c) {
    bool shouldUpdate = false;

    switch(c) {
        case GLUT_KEY_LEFT:
            mData.moveLeft();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case GLUT_KEY_RIGHT:
            mData.moveRight();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case GLUT_KEY_DOWN:
            mData.moveDown();
            mData.createFractal();
            shouldUpdate = true;
            break;
        case GLUT_KEY_UP:
            mData.moveUp();
            mData.createFractal();
            shouldUpdate = true;
            break;
        default:
            break;
    }

    return shouldUpdate;
}

bool GlutApp::mouse(int mouse_button, int state, int x, int y) {
    int xd = x;
  int yd = mData.getHeight() - y;
  bool shouldUpdate = false;
  if (mData.getInteractionMode() == AppData::IM_FRACTAL && mData.getFractalMode() == AppData::M_MANDELBROT) {
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      mData.setAB(xd, yd);
      mData.setFractalMode(AppData::M_JULIA);
      mData.createFractal();
      shouldUpdate = true;
    }
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    shouldUpdate = false;
  }
  return shouldUpdate;
}