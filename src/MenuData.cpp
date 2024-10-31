#include "MenuData.h"

MenuData::MenuData(){}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
    mNames.push_back(name);
    mActions[name] = func;
    mDescriptions[name] = description;
}

const std::vector<std::string> &MenuData::getNames() const {
    return mNames;
}

ActionFunctionType MenuData::getFunction(const std::string &name) {
    if(mActions.find(name) != mActions.end()) {
        return mActions[name];
    }
    else{
        return 0;
    }
}
const std::string &MenuData::getDescription(const std::string &name) {
    if(mDescriptions.find(name) != mDescriptions.end()) {
        return mDescriptions[name];
    }
    else{
        static std::string empty = "";
        mDescriptions[name] = empty;
        return mDescriptions[name];
    }
}
