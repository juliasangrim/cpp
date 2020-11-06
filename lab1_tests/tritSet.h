//
// Created by trubi on 10/27/2020.
//

#ifndef LAB1_TESTS_TRITSET_H
#define LAB1_TESTS_TRITSET_H
#include <iostream>
#include <cmath>

const size_t BIT = 8;
const size_t TRIT_SIZE = 2;
const size_t amountTrit = (sizeof(size_t) * BIT / TRIT_SIZE); // 16
enum Trit {F = 0, U = 1, T = 3};


class TritSet {
private:
    ///fields
    size_t* m_arrTrit;
    size_t m_size; //amount of trits
    size_t m_capacity; // allocLength
    TritSet& memory_alloc(size_t);
    TritSet& makeEqual(TritSet&); ///make an equal size
    size_t getUnknownTail();
    Trit getTrit(size_t);/// give us a Trit value
public:
    TritSet(size_t amount) {
        m_size = amount;
        m_capacity = ceil((double)amount * 2 / 8 / sizeof(size_t));
        m_arrTrit = new size_t[m_capacity];
        size_t unknown = 1;
        for (size_t i = 0; i < sizeof(size_t) * BIT / 2; i++) {
            unknown = unknown << 2;
            unknown |= 01;
        }
        for (size_t i = 0; i < m_capacity; i++) {
            m_arrTrit[i] = unknown;
        }
    }
    TritSet(TritSet& set){
        m_size = set.m_size;
        m_capacity = set.m_capacity;
        m_arrTrit = new size_t(m_capacity);
        memcpy(m_arrTrit, set.m_arrTrit, sizeof(size_t) * m_capacity);
    }

    TritSet (size_t amount, Trit t) {
        m_size = amount;
        m_capacity = ceil((double)amount * 2 / 8 / sizeof(size_t));
        m_arrTrit = new size_t[m_capacity];
        auto trit = static_cast<size_t>(t);
        size_t tmpSize = m_size;
        for (size_t i = 0; i < m_capacity; i++) {
        for (size_t i = 0; i < sizeof(size_t) * BIT / 2; i++) {
            if (tmpSize != 0) {
                trit = trit << 2;
                trit |= t;
                tmpSize--;
            } else {
                trit = trit << 2;
                trit |= U;
            }
        }
            m_arrTrit[i] = trit;
            trit = 0;
        }
    }

    ~TritSet() {
        delete [] m_arrTrit;
    }

    class Proxy {
    private:
        TritSet& m_set;
        size_t m_index; //set.arrtrit(индекс ячейки)
    public:
        Proxy(size_t idx, TritSet& set) : m_set(set), m_index(idx) { };
        Proxy& operator= (Trit);
        operator Trit() const;
    };
    Proxy operator[] (size_t); //DONE
    friend TritSet operator& (TritSet& , TritSet&);//DONE
    friend TritSet operator|(TritSet& , TritSet&);//DONE
    TritSet operator~();//DONE
    TritSet& operator=(TritSet const&);//DONE
    size_t getCapacity() const; //DONE
    size_t getSizeArray();
    void printTritSet();//DELETE
    size_t getSize();//DONE
    TritSet& shrink();//
};
#endif //LAB1_TESTS_TRITSET_H
