#include <chrono>

class SimpleClock{
    public:
        SimpleClock();
        void Restart();
        double GetElapsedTimeInSeconds() const;
    
    private:
        std::chrono::steady_clock::time_point StartingTime;
};