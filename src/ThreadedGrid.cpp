#include "ThreadedGrid.h"
#include "NumberGrid.h"
#include <vector>
#include <thread>

Coordinate::Coordinate()
    : mRow(), mCol(){
}

ThreadedGrid::ThreadedGrid() 
    : NumberGrid(), mTasks(), mLock(){
}

ThreadedGrid::ThreadedGrid(const int& height, const int& width) 
    : NumberGrid(height, width) {
}

ThreadedGrid::~ThreadedGrid() {
}

void ThreadedGrid::calculateAllNumbers() {
    Coordinate cord;
    for(int row = 0; row < getHeight(); row++){
        for (int col = 0; col < getWidth(); col++){
            cord.mRow = row;
            cord.mCol = col;
            mTasks.push_back(cord);
        }
    }

    unsigned int max_cores = std::thread::hardware_concurrency();
    unsigned int i;
    std::vector<std::thread> threads;
    for(i = 0; i < max_cores; i++) {
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
    }

    for(i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
}

void ThreadedGrid::worker() {
    bool done = false;
    Coordinate coord;
    while(!done) {
        mLock.lock();
        if(mTasks.size() > 0) {
            coord = mTasks.back();
            mTasks.pop_back();
        } else {
            done = true;
        }
        mLock.unlock();

        if(!done){
            // mLock.lock();
            int number = calculateNumber(coord.mRow, coord.mCol);
            setNumber(coord.mRow, coord.mCol, number);
            // mLock.unlock();
        }
    }
}