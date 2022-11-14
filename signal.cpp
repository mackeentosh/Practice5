#include "signal.h"
#include <math.h>
#define M_PI 3.14159265358979323846

Signal::Signal()
{
    signal_size = 100;
    values = new double[100];
}

Signal::Signal(size_t size)
{
    signal_size = size;
    values = new double[size];
}

void Signal::resize(size_t new_size)
{
    auto temp = new double[new_size];

    for(int i = 0; i < signal_size; i++)
        temp[i] = values[i];

    values = temp;
    delete[] temp;
}

double Signal::operator[](size_t ind)
{
    return values[ind];
}

Signal Signal::operator+(const Signal& s)
{
    int max = signal_size >= s.signal_size? signal_size : s.signal_size;
    int min = signal_size <= s.signal_size? signal_size : s.signal_size;
    auto max_arr = signal_size >= s.signal_size? values : s.values;
    auto res = new Signal(max);

    for(int i = 0; i < min; i++)
        res[i] = values[i] + s.values[i];

    for(int i = 0; i < max - min; i++)
        res[i + min] = max_arr[i + min];

    delete max_arr;
    return *res;
}

Signal Signal::operator-(const Signal& s)
{
    int max = signal_size >= s.signal_size? signal_size : s.signal_size;
    int min = signal_size <= s.signal_size? signal_size : s.signal_size;
    auto res = new Signal(max);

    for(int i = 0; i < min; i++)
        res[i] = values[i] - s.values[i];

    if(signal_size >= s.signal_size)
        for(int i = 0; i < max - min; i++)
            res[min + i] = values[min + i];
    else
        for(int i = 0; i < max - min; i++)
            res[i + min] = 0 - s.values[i + min];

    return *res;
}

Signal& Signal::operator+=(const Signal& s)
{
    int max = signal_size >= s.signal_size? signal_size : s.signal_size;
    int min = signal_size <= s.signal_size? signal_size : s.signal_size;
    auto max_arr = signal_size > s.signal_size? values : s.values;
    Signal* res = new Signal(max);

    for(int i = 0; i < min; i++)
        res[i] = values[i] + s.values[i];

    for(int i = 0; i < max - min; i++)
        res[i + min] = max_arr[i + min];

    values = res->values;
    signal_size = res->signal_size;

    delete max_arr;

    return *res;
}

Signal& Signal::operator-=(const Signal& s)
{
    int max = signal_size >= s.signal_size? signal_size : s.signal_size;
    int min = signal_size <= s.signal_size? signal_size : s.signal_size;
    auto res = new Signal(max);

    for(int i = 0; i < min; i++)
        res[i] = this->values[i] - s.values[i];

    if(signal_size >= s.signal_size)
        for(int i = 0; i < max - min; i++)
            res[min + i] = values[min + i];
    else
        for(int i = 0; i < max - min; i++)
            res[i + min] = 0 - s.values[i + min];

    values = res->values;
    signal_size = res->signal_size;
    return *res;
}


void Signal::generate_sine (double freq, double sig_ampl)
{
    for(int i = 0; i< signal_size; i++)
        values[i] = sig_ampl * std::sin((2 * M_PI * freq * i) / discr_freq);
}

Signal::~Signal()
{
    delete[] values;
}
