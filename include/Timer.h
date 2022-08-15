#ifndef TIMER_H
#define TIMER_H

// clase Temporizador
class Timer {
    private:
        int counter; // contador

    public:
        // constructor
        Timer(int = 0);

        // establecer
        void set(int = 0);

        // obtener
        int get() const;

        // incrementar
        void increment();

        // decrementar
        void decrement();
};

#endif // TIMER_H
