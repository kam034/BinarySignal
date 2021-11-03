#ifndef PROG3A_BINARYSIGNAL_H
#define PROG3A_BINARYSIGNAL_H

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits>

//  !!! потоки - « , »
//  !!! бинарный - +
//  !!! декремент - --(), ()--
//  !!! инверсия - ~
//  !!! индексация - [] const и не const
//  !!! модифицированное присваивание - *=
//  !!! приведение типа space ship - ()


namespace Prog3A
{
    struct Status
    {
        bool m_level;
        unsigned char m_duration;
    };

    class BinarySignal
    {
    private:
        static const int SZ = 100;
        static const int MAX = 255;
        int m_length;                //размер сигнала (110101 - размер 6)
        int m_size;                     //фактический размер массива
        Status m_array[SZ];

    public:
        //конструкторы
        BinarySignal() noexcept;
        explicit BinarySignal(bool lvl) noexcept;
        BinarySignal(int size, const char* bs);

        //дичь какая-то
        BinarySignal& initialization(int size, const char* bs);
        BinarySignal& inverting() noexcept;
        BinarySignal& add(const BinarySignal &bs);
        BinarySignal& insert(int prd, const BinarySignal &ptr);
        BinarySignal& copy(int n);
        BinarySignal& remove(int start, int prd);

        //куча никому не нужных перегрузок
        friend std::istream &operator>>(std::istream &in, BinarySignal &bs);
        friend std::ostream& operator<<(std::ostream &out, const BinarySignal &ptr) noexcept;
        friend BinarySignal operator+(BinarySignal &a, const BinarySignal &b);
        BinarySignal& operator*=(int n);
        BinarySignal& operator()(const char* bs, int n);
        Status& operator[](int n);
        const Status& operator[](int n) const;
        BinarySignal& operator~();
        BinarySignal& operator--();
        const BinarySignal operator--(int);

        //геттеры и еще
        void printDebug() const;
        static int getSZ();
        [[nodiscard]] int getM_CNT() const;
        [[nodiscard]] int getM_LGHT() const;
        [[nodiscard]] const Status* getM_ARRAY() const;
    };

    template<class T>
    void getNum(std::istream &in, T &num) {
        while (true) {
            in >> num;
            if (!in.good()) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
    }
}


#endif //PROG3A_BINARYSIGNAL_H
