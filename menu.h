#ifndef PROG3A_MENU_H
#define PROG3A_MENU_H


#include <limits>
//#include "..\Library\BS\include\BinarySignal.h"
#include "binarySignal.h"


template <class T>
int getNum(T &a)
{
    while (true) {
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR! Invalid data! Try again please: ->";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 1;
        }
    }
}

int getPositiveNum(int &a);

void print_menu();
void emptyConstructor(Prog3A::BinarySignal& ptr);
void firstConstructor(Prog3A::BinarySignal& ptr);
void secondConstructor(Prog3A::BinarySignal &ptr);
void inputSequence(Prog3A::BinarySignal& ptr);
void outputSequence(Prog3A::BinarySignal &ptr);
void copyBinarySignal(Prog3A::BinarySignal& ptr);
void inversionBinarySignal(Prog3A::BinarySignal& ptr);
void insertBinarySignal(Prog3A::BinarySignal& ptr);
void removeBinarySignal(Prog3A::BinarySignal& ptr);
void addBinarySignal(Prog3A::BinarySignal& ptr);
void elemArray(Prog3A::BinarySignal& ptr);

#endif //PROG3A_MENU_H
