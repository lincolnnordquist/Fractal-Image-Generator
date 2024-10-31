#include "ActionData.h"

ActionData::ActionData(std::istream& is, std::ostream& os) 
    : mIs(is), mOs(os), mQuit(false), mGrid(0), mColors_table(16){
        mColors_table.insertGradient(Color(0,255,0), Color(255,0,255), 0, 15);
}

std::istream& ActionData::getIS() {
    return mIs;
}

std::ostream& ActionData::getOS() {
    return mOs;
}

PPM& ActionData::getInputImage1() {
    return mII1;
}

PPM& ActionData::getInputImage2() {
    return mII2;
}

PPM& ActionData::getOutputImage() {
    return mOutI;
}

bool ActionData::getDone() const {
    return mQuit;
}

void ActionData::setDone() {
    mQuit = true;
}

ActionData::~ActionData(){
    if(mGrid != 0) {
    delete mGrid;
  }
}

NumberGrid& ActionData::getGrid() {
  return *mGrid;
}

void ActionData::setGrid(NumberGrid *grid) {
    if(mGrid != 0) {
    delete mGrid;
  }
  mGrid = grid;
}

ColorTable &ActionData::getTable() {
  return mColors_table;
}
