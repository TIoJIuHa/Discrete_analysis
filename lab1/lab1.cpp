#include <iostream>
#include <iomanip>
#include <cstring>


template <typename T>
class vectorClass
{
    T* data;
    int capacity_;
    int current_;

public:
    vectorClass()
    {
        data = new T[1];
        capacity_ = 1;
        current_ = 0;
    }
    ~vectorClass()
    {
        delete[] data;
    }

    void push(unsigned int code, char* input_string)
    {
        if (current_ == capacity_)
        {
            T* temp = new T[2 * capacity_];

            for (int i = 0; i < capacity_; ++i)
            {
                temp[i] = data[i];
            }

            delete[] data;
            capacity_ *= 2;
            data = temp;
        }

        data[current_].postcode = code;
        strcpy(data[current_].value, input_string);
        current_ += 1;
    }

    T get(int index)
    {
        return data[index];
    }

    int size()
    { 
        return current_;
    }
};


struct InputData
{
    unsigned int postcode;
    char value[65];
};


InputData* CountSort(vectorClass<InputData> &inputArray)
{
    unsigned int countArray[1000000] = {0};
    InputData pair;

    for (int i = 0; i < inputArray.size(); ++i)
    {
        pair = inputArray.get(i);
        countArray[pair.postcode] += 1;
    }

    for (int i = 1; i < 1000000; ++i)
    {
        countArray[i] += countArray[i - 1];
    }

    InputData* sortedArray = new InputData[inputArray.size()];

    for (int i = inputArray.size() - 1; i > -1; --i)
    {
        pair = inputArray.get(i);
        sortedArray[countArray[pair.postcode] - 1] = pair;
        countArray[pair.postcode] -= 1;
    }

    return sortedArray;
}


int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    vectorClass<InputData> inputArray;
    unsigned int postcode;
    char value[65];

    while (std::cin >> postcode >> value)
    {
        inputArray.push(postcode, value);
    }

    InputData* sortedData = new InputData[inputArray.size()];
    sortedData = CountSort(inputArray);

    for (int i = 0; i < inputArray.size(); ++i)
    {
        std::cout << std::setw(6) << std::setfill('0') << sortedData[i].postcode << "\t" << sortedData[i].value << "\n";
    }

    delete[] sortedData;
    return 0;
}
