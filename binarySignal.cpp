#include "binarySignal.h"

namespace Prog3A {
    BinarySignal::BinarySignal() noexcept: m_size(0), m_length(0), m_array{} {

    }

    BinarySignal::BinarySignal(bool lvl) noexcept: m_size(1), m_length(MAX), m_array{lvl, MAX} {

    }

    BinarySignal::BinarySignal(int size, const char *bs): m_size(0), m_length(size), m_array{} {
        initialization(size, bs);
    }


    BinarySignal& BinarySignal::initialization(int size, const char* bs) {// обработка строки и распределение по массиву состояний
        m_length = m_size + size;
        int count = 0;
        for (int i = 0; i < size - 1;) {
            if (bs[i] == '0') {
                m_array[m_size].m_level = false;
                while (bs[i] == '0' && i < size) {
                    count++;
                    i++;
                    if (count > MAX)
                        throw std::length_error("Invalid size for binary signal!"
                                                "(maximum duration is 255)");
                }
                m_array[m_size].m_duration = count;
            }
            else if (bs[i] == '1') {
                m_array[m_size].m_level = true;
                while (bs[i] == '1' && i < size) {
                    count++;
                    i++;
                    if (count > MAX)
                        throw std::length_error("Invalid size for binary signal!"
                                                "(maximum duration is 255)");
                }
                m_array[m_size].m_duration = count;
            }
            else
                throw std::invalid_argument("Invalid value in string!");

            count = 0;

            m_size++;
            if (m_size > SZ)
                throw std::length_error("Invalid size for binary signal!"
                                        "(all cells of the array are filled)");

        }
        return *this;
    }


    BinarySignal& BinarySignal::inverting() noexcept {    // инвертирование сигнала
        for (int i = 0; i < m_size; i++) {
            if (m_array[i].m_level)
                m_array[i].m_level = !m_array[i].m_level;
        }
        return *this;
    }


    BinarySignal& BinarySignal::add(const BinarySignal &bs) {    // добавление в конец и склеивание
        if (!bs.m_size);
        else if (!m_size)
            *this = bs;
        else {
            if (m_array[m_size - 1].m_level == bs.m_array[0].m_level) {
                if (m_size + bs.m_size - 1 > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                if (m_array[m_size - 1].m_duration + bs.m_array[0].m_duration > MAX)
                    throw std::length_error("Illegal size for binary signal, because m_duration > MAX!");
                m_array[m_size - 1].m_duration += bs.m_array[0].m_duration;
                for (int i = 0; i < bs.m_size - 1; i++)
                    m_array[i + m_size] = bs.m_array[i + 1];
                m_size += bs.m_size - 1;
            } else {
                if (m_size + bs.m_size > SZ)
                    throw std::length_error("Illegal size for binary signal, because m_size > SZ!");
                for (int i = 0; i < bs.m_size; i++)
                    m_array[i + m_size] = bs.m_array[i];
                m_size += bs.m_size;
            }
            m_length += bs.m_length;
        }
        return *this;
    }



    BinarySignal& BinarySignal::insert(int prd, const BinarySignal &ptr) {
        if (prd > m_length)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        BinarySignal begin, end, tmp = *this;
        if (prd == 0) {
            begin = ptr;
            begin.add(*this);
            *this = begin;
            return *this;
        }
        if (prd == m_length) {
            add(ptr);
            return *this;
        }
        int k = 0, i;
        for (i = 0; i < m_size; i++) {
            k += m_array[i].m_duration;
            if (k > prd - 1)
                break;
        }
        tmp.m_size = i + 1;
        tmp.m_length = prd;
        tmp.m_array[i].m_duration -= k - prd;
        begin = tmp;
        begin.add(ptr);
        if (k == prd) {
            end.m_size = m_size - tmp.m_size;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + tmp.m_size];
        } else {
            end.m_size = m_size - tmp.m_size + 1;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + tmp.m_size - 1];
            end.m_array[0].m_duration = k - prd;
        }
        end.m_length = m_length - prd;
        begin.add(end);
        *this = begin;
        return *this;
    }

    BinarySignal& BinarySignal::copy(int n) {
        BinarySignal tmp = *this;
        for (int i = 0; i < n - 1; i++)
            this->add(tmp);
        return *this;
    }

    BinarySignal& BinarySignal::remove(int start, int prd) {
        if (start + prd > m_length)
            throw std::length_error("Illegal size for binary signal, because prd > m_lght!");
        int k = 0, q = 0, i;
        BinarySignal begin, end, tmp = *this;
        for (i = 0; i < m_size; i++) {
            k += m_array[i].m_duration;
            if (k > start - 1)
                break;
        }
        tmp.m_size = i + 1;
        tmp.m_length = start;
        tmp.m_array[i].m_duration -= k - start;
        begin = tmp;
        for (i = 0; i < m_size; i++) {
            q += m_array[i].m_duration;
            if (q > start + prd - 1)
                break;
        }
        int s = i;
        if (q == start + prd) {
            end.m_size = m_size - s - 1;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + s + 1];
        } else {
            end.m_size = m_size - s;
            for (i = 0; i < end.m_size; i++)
                end.m_array[i] = m_array[i + s];
            end.m_array[0].m_duration = q - start - prd;
        }
        end.m_length = m_length - begin.m_length - prd;
        begin.add(end);
        *this = begin;
        return *this;
}


                // ПЕРЕГРУЗКИ


    std::istream &operator>>(std::istream &in, BinarySignal &bs) {
        int sz;
        std::cout << "Enter the size of string -> " << std::endl;
        getNum(in, sz);
        char array[sz + 1];
        std::cout << "Enter the string (separated by a space) ->" << std::endl;
        for (int i = 0; i < sz; i++)
            getNum(in, array[i]);
        //bs (array, sz + 1); // использование перегрузки ()
        bs.initialization(sz + 1, array);
        return in;
    }


    std::ostream &operator<<(std::ostream &out, const BinarySignal &bs) noexcept {
        if (!bs.m_length)
            out << "Binary Signal is empty!";
        else {
            std::cout << "Binary signal -> ";
            for (int i = 0; i < bs.m_length; i++)
                for (int j = 0; j < bs.m_array[i].m_duration; j++)
                    out << bs.m_array[i].m_level;
        }
        std::cout << std::endl;
        return out;
    }


    BinarySignal operator+(BinarySignal &a, const BinarySignal &b) {
        BinarySignal c;
        c = a.add(b);
        return c;
    }


    BinarySignal& BinarySignal::operator*=(int n) {
        copy(n);
        return *this;
    }

    BinarySignal& BinarySignal::operator()(const char* bs, int n) {
        initialization(n, bs);
        return *this;
    }


    BinarySignal& BinarySignal::operator~() {
        inverting();
        return *this;
    }

    Status& BinarySignal::operator[](int n) {
        if (n < 0 || n > m_size)
            throw std::invalid_argument("Invalid index of array!");
        return m_array[n];
    }

    const Status& BinarySignal::operator[](int n) const {
        if (n < 0 || n > m_size)
            throw std::invalid_argument("Invalid index of array!");
        return m_array[n];
    }

    BinarySignal& BinarySignal::operator--() {   //префикс
        remove(0, m_array[0].m_duration);
        return *this;
    }

            // (int) - фиктивный целочислинный параметр, чтобы отличить постфикс от префикса
     const BinarySignal BinarySignal::operator--(int) {  //постфикс
        BinarySignal t(*this);
        remove(0, m_array[0].m_duration);
        return t;
    }


                        //getтеры и вспом функции

    void BinarySignal::printDebug() const {
        for (int i = 0; i < m_size; i++)
            std::cout << "#" << i << ": " << m_array[i].m_level << " -> " << static_cast<int>(m_array[i].m_duration) << std::endl;
        std::cout << std::endl;
    }

    int BinarySignal::getSZ() {
        return SZ;
    }

    int BinarySignal::getM_CNT() const {
        return m_size;
    }

    int BinarySignal::getM_LGHT() const {
        return m_length;
    }

    const Status* BinarySignal::getM_ARRAY() const {
        return m_array;
    }
}