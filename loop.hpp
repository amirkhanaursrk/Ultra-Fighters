#ifndef LOOP_H
#define LOOP_H

#include <thread>

class LoopListener {
public:
    virtual void setup() = 0;
    virtual void render(float interp) = 0;
    virtual void update(double step) = 0;
};

class Loop {
public:
    Loop(LoopListener* listener);
    void start();
    void stop();
    bool isRunning();
    LoopListener* getListener();
    void setLoopSpeed(int updatesPerSecond);
    void setMaxUpdates(int maxUpdates);
    
private:
    bool running;
    std::thread* runThread;
    LoopListener* listener;
    double timeBetweenUpdates;
    double maxUpdates;
    
    void run();
};

#endif
