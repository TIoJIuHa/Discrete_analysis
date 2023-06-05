#include <iostream>
#include <stdio.h>
#include <string.h>

template <typename T>
class VectorClass
{
    T* data;
    int capacity;
    int current;

public:
    VectorClass()
    {
        data = new T[1];
        capacity = 1;
        current = 0;
    }
    ~VectorClass()
    {
        delete[] data;
    }

    void push(T value)
    {
        if (current == capacity)
        {
            T* temp = new T[2 * capacity];

            for (int i = 0; i < capacity; i++)
            {
                temp[i] = data[i];
            }

            delete[] data;
            capacity *= 2;
            data = temp;
        }

        data[current] = value;
        ++current;
    }

    void push(T value, int index)
    {
        if (index == capacity)
        {
            push(value);
        }
        else
        {
            data[index] = value;
        }
    }

    T get(int index)
    {
        return data[index];
    }

    int size()
    { 
        return current;
    }
};

void ZFunction(VectorClass<char> &s, int* Z)
{
    int n = s.size();
    int left = 0;
    int right = 0;

    for (int i = 1; i < n; ++i)
    {
        if (i < right)
        {
            if (right - i < Z[i - left])
            {
                Z[i] = right - i;
            }
            else
            {
                Z[i] = Z[i - left];
            }
        }

        while (s.get(Z[i]) == s.get(i + Z[i]))
        {
            Z[i] += 1;
        }

        if (i + Z[i] > right)
        {
            left = i;
            right = i + Z[i];
        }
    }
}

int main()
{
    VectorClass<char> P;
    VectorClass<char> T;
    char symbol = ' ';

    while ('\n' != (symbol = getchar()))
    {
        T.push(symbol);
    }

    while ('\n' != (symbol = getchar()))
    {
        P.push(symbol);
    }

    int n = P.size();
    int m = T.size();
    P.push('$');

    for (int i = 0; i < T.size(); ++i)
    {
        P.push(T.get(i));
    }

    int Z[n + m + 1];
    memset(Z, 0, (n + m + 1) * sizeof(int));
    ZFunction(P, Z);

    for (int i = 0; i < n + m + 1; ++i)
    {
        if (Z[i] == n)
        {
            std::cout << i - n - 1 << "\n";
        }
    }

    return 0;
}