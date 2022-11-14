#ifndef SIGNAL_H
#define SIGNAL_H
#include <cstddef>


class Signal
{
public:
    Signal();
    Signal(size_t size);
    void resize(size_t new_size);
    double operator[](size_t);
    Signal operator+(const Signal&);
    Signal operator-(const Signal&);
    Signal& operator+=(const Signal&);
    Signal& operator-=(const Signal&);
    void generate_sine(double freq, double sig_ampl);

    size_t signal_size = 0;
    double* values = nullptr;

    static constexpr double discr_freq = 44100;
    inline ~Signal();
};

#endif // SIGNAL_H

