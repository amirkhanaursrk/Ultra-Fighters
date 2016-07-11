#pragma once

#include <thread>

class LoopListener {
public:
    virtual void render(float interp) = 0;
    virtual void update(double step) = 0;
};

class Loop {
public:
    Loop(LoopListener* listener);
    void start();
    void stop();
    bool isRunning();
    void play();
    void pause();
    bool isPaused();
    LoopListener* getListener();
    void setLoopSpeed(int updatesPerSecond);
    void setMaxUpdates(int maxUpdates);
    
private:
    bool running;
    bool paused;
    std::thread* runThread;
    LoopListener* listener;
    double timeBetweenUpdates;
    double maxUpdates;
    
    void run();
};
