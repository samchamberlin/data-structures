#ifndef QS_h
#define QS_h

#include "QSInterface.h"
#include <iostream>
#include <string>
using namespace std;

class QS : public QSInterface{
public:
    QS();
    ~QS();
    void sort(int left, int right);
    void sortAll();
    void swap(int value1, int value2);
    int medianOfThree(int left, int right);
    int partition(int left, int right, int pivotIndex);
    string getArray() const;
    int getSize() const;
    bool addToArray(int value);
    bool createArray(int capacity);
    void clear();
private:
    int* myArray;
    int currentSize = 0;
    int maxSize = 0;
};

#endif /* QS_H_ */
