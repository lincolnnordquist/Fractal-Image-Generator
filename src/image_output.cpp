#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include <fstream>
//#include "user_io.cpp"


void copyImage(ActionData& action_data){
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ){
    std::string f_name = getString(action_data, "Input filename? ");
    std::ifstream myFile;
    myFile.open(f_name, std::ifstream::binary);
    action_data.getInputImage1().readStream(myFile);
    if(!myFile.good()){ //or .is_open() or .fail()
        std::cout << "'"<< f_name << "'"<< " could not be opened." << std::endl;;
    }
}

void readUserImage2(ActionData &action_data) {
    std::string f_name = getString(action_data, "Input filename? ");
    std::ifstream myFile;
    myFile.open(f_name, std::ifstream::binary);
    action_data.getInputImage2().readStream(myFile);
    if(!myFile.good()){ //or .is_open() or .fail()
        std::cout << "'"<< f_name << "'"<< " could not be opened." << std::endl;;
    }
}

void drawAsciiImage( ActionData& action_data ) {
    (void) action_data.getIS();
    int row = action_data.getOutputImage().getHeight();
    int column = action_data.getOutputImage().getWidth();
    for (int i = 0; i < row; i++){
        for (int i2 = 0; i2 < column; i2++){
            int red_val = action_data.getOutputImage().getChannel(i, i2, 0);
            int green_val = action_data.getOutputImage().getChannel(i, i2, 1);
            int blue_val = action_data.getOutputImage().getChannel(i, i2, 2);
            int pix_sum = red_val + green_val + blue_val;
            double pix_strength = double(pix_sum) / 765.0;
            if (pix_strength >= 1.0){
                action_data.getOS() << "@";
            }
            else if (pix_strength >= 0.9){
                action_data.getOS() << "#";
            }
            else if (pix_strength >= 0.8){
                action_data.getOS() << "%";
            }
            else if (pix_strength >= 0.7){
                action_data.getOS() << "*";
            }
            else if (pix_strength >= 0.6){
                action_data.getOS() << "|";
            }
            else if (pix_strength >= 0.5){
                action_data.getOS() << "+";
            }
            else if (pix_strength >= 0.4){
                action_data.getOS() << ";";
            }
            else if (pix_strength >= 0.3){
                action_data.getOS() << "~";
            }
            else if (pix_strength >= 0.2){
                action_data.getOS() << "-";
            }
            else if (pix_strength >= 0.1){
                action_data.getOS() << ".";
            }
            else if (pix_strength >= 0.0){
                action_data.getOS() << " ";
            }
            }
        action_data.getOS() << std::endl;
    }

}

void writeUserImage( ActionData& action_data ){
    std::string f_name = getString(action_data, "Output filename? ");
    std::ofstream myFile (f_name, std::ofstream::binary);
    action_data.getOutputImage().writeStream(myFile);
    myFile.close();
}

