#ifndef THREADEDGRID_H
#define THREADEDGRID_H
#include "NumberGrid.h"
#include <vector>
#include <thread>
#include <mutex>

class Coordinate{
public:
    Coordinate();
    Coordinate(const int row, const int column);
    int mRow;
    int mCol;
};

class ThreadedGrid: public NumberGrid{
public:
    ThreadedGrid();
    ThreadedGrid(const int& height, const int& width);
    virtual ~ThreadedGrid();
    virtual void calculateAllNumbers();
    virtual void worker();

protected:
    std::vector <Coordinate> mTasks;
    std::mutex mLock;


};


#endif