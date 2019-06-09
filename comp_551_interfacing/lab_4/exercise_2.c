/*
The processor frequency is 10MHz, so each tick will consume: 4/10MHz = 0.4us
In order to generate the highest frequency of a square wave, I have to obtain the lowest time period of that wave.
Because the time period is equal to double delay time, I will use the Timer0 to generate delay time as little as possible.
If the number of ticks is 0, the timer will not run. Therefore, the minimum number of ticks will be 1 tick.
I do not use the prescaler, so the actual ticks also will be 1 tick.
The possible lowest delay time will be: 1 x 0.4us = 0.4us
The lowest frequency generated will be: 1/(0.4us x 2) = 1.25MHz
*/
