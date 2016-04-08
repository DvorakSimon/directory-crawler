#ifndef LOOPTIME_H
#define LOOPTIME_H

#include <sys/timeb.h>

class LoopTime
{
    public:
        long getCurrentTime();

        LoopTime();
        virtual ~LoopTime();
    protected:
    private:
};

#endif // LOOPTIME_H
