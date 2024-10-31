#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_
#include "AppData.h"

class GlutApp {
public:
  GlutApp(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;
  void display();
  void displayOutputImage();
  void displayColorTable();
  bool keyboard(unsigned char c);
  bool special(unsigned char c);
  bool mouse(int mouse_button, int state, int x, int y);

protected:
  AppData mData;
};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */