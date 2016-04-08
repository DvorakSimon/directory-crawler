#include "LoopTime.h"

LoopTime::LoopTime()
{
    //ctor
}

LoopTime::~LoopTime()
{
    //dtor
}

long LoopTime::getCurrentTime() {
    timeb timebstr;
    ftime( &timebstr );
    return (long)(timebstr.time)*1000 + timebstr.millitm;
}
