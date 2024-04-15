#ifndef TIMER_H
#define TIMER_H

class Timer 
{
    public : 

    Timer();
    void raz(int *strt);
    int elapsed(int* delta, int* strt);
};
#endif
