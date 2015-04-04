#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

#include <string>
#include <iostream>


// defines the tickInterface - It's only one method so it's not that big a deal
class tickInterface {
public:
    virtual void doTick(int foo){};
};





class TickControl : public tickInterface {
private:
    std::vector<tickInterface*> toTick;
    bool running = false, started = false;

    float interval = 0.2;

    void sleep(unsigned int milliseconds);
    void Timer();


public:
    void doTick(int foo);
    void addTicker(tickInterface* ticker);
    void setRunning(bool run);
    void start();
};





#endif