#include "SimpleClock.h"

SimpleClock::SimpleClock(){
    Restart();
}

void SimpleClock::Restart(){
    this->StartingTime = std::chrono::steady_clock::now();
}

double SimpleClock::GetElapsedTimeInSeconds() const{
    auto CurrentTime = std::chrono::steady_clock::now();
    auto ElapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(CurrentTime-StartingTime);
    return ElapsedTime.count();
}
