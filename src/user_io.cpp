#include <string>
#include "image_menu.h"
#include <iostream>
#include "ActionData.h"


std::string getString( ActionData& action_data, const std::string& prompt ) {
    std::string b;
    action_data.getOS() << prompt;
    action_data.getIS() >> b;
    return b;
}
int getInteger(ActionData& action_data, const std::string& prompt) {
    int a;
    action_data.getOS() << prompt;
    action_data.getIS() >> a;
    return a;
}
double getDouble( ActionData& action_data, const std::string& prompt ) {
    double c;
    action_data.getOS() << prompt;
    action_data.getIS() >> c;
    return c;
}
int askQuestions3(ActionData& action_data) {
    std::string color = getString(action_data, "What is your favorite color? ");
    int n = getInteger(action_data, "What is your favorite integer? ");
    double f = getDouble(action_data, "What is your favorite number? ");
    if(n > 0) {
        for(int i = 0; i < n; i++) {
        action_data.getOS() << i+1 << " " << color << " " << f << std::endl;
        }
    }
    else {
        return n;
    }
    return n;
}
std::string getChoice( ActionData& action_data ){
    std::string choice = getString(action_data, "Choice? ");
    return choice;
}

void commentLine( ActionData& action_data ){
    unsigned char c;
    while(action_data.getIS().good() && c != '\n'){
        action_data.getIS().read((char *) &c, 1);
    }
}

void quit(ActionData& action_data){
    action_data.setDone();
}