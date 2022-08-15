#include "Timer.h"

// constructor
Timer::Timer(int time) {
    set(time);
}

// establecer
void Timer::set(int time) {
    if (time >= 0) {
        counter = time;
    }
}

// obtener
int Timer::get() const {
    return counter;
}

// incrementar
void Timer::increment() {
    counter++;
}

// decrementar
void Timer::decrement() {
    if (counter > 0) counter--;
}
