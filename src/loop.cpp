#include <algorithm>
#include <ctime>

#include "logger.h"
#include "loop.hpp"

Loop::Loop(LoopListener* listener) {
    this->listener = listener;
    running = false;
    timeBetweenUpdates = CLOCKS_PER_SEC / 30.0;
    maxUpdates = 10;
}

void Loop::start() {
    running = true;
    runThread = new std::thread(&Loop::run, this);
}

void Loop::stop() {
    running = false;
    runThread->join();
}

bool Loop::isRunning() {
    return running;
}

LoopListener* Loop::getListener() {
    return listener;
}

void Loop::setLoopSpeed(int updatesPerSecond) {
    timeBetweenUpdates = CLOCKS_PER_SEC / updatesPerSecond;
}

void Loop::setMaxUpdates(int maxUpdates) {
    this->maxUpdates = maxUpdates;
}

void Loop::run() {
    std::clock_t oldTime = std::clock();

    listener->setup();

    while (running) {
        std::clock_t newTime = std::clock();

        int updates = 0;
        while (newTime - oldTime >= timeBetweenUpdates && updates < maxUpdates) {
            listener->update((double) timeBetweenUpdates / CLOCKS_PER_SEC);

            oldTime += timeBetweenUpdates;
            updates++;
        }

        if (updates == maxUpdates) log_msg(LOG_WARNING, "Loop is overloaded!!!\n");

        float interp = std::min(1.0f, (float) (newTime - oldTime) / (float) timeBetweenUpdates);
        listener->render(interp);
    }
}
