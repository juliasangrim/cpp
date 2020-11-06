#include "tritSet.h"

TritSet::Proxy TritSet::operator[](size_t index) {
    return Proxy (index, *this);
}

size_t TritSet::getSize() {
    return m_size;
}

TritSet& TritSet::memory_alloc(size_t index) {
    m_size = index + 1;
    m_capacity =  ceil((double)m_size * 2 / 8 / sizeof(size_t));
    size_t* arrCopy = new size_t[m_capacity];
    memcpy(arrCopy, m_arrTrit, m_capacity * sizeof(size_t));
    delete[] m_arrTrit;
    m_arrTrit = arrCopy;
    return *this;
}

TritSet::Proxy& TritSet::Proxy::operator=(Trit t) { // set[2] = T; set.operator[](2).operator=(T)
    if (m_set.m_size <= m_index) {
        if ((t == T) || (t == F)) {
            m_set.memory_alloc(m_index);//выделение памяти и копирование
        } else {
            return *this;
        }
    }
    size_t bitMask = 3;//place for trit
    size_t idxArray = m_index / amountTrit;
    size_t idxTrit = m_index % amountTrit + 1;
    m_set.m_arrTrit[idxArray] &= ~(bitMask << (sizeof(size_t) * BIT - idxTrit * 2));
    bitMask = t;
    m_set.m_arrTrit[idxArray] |= (bitMask << (sizeof(size_t) * BIT - idxTrit * 2));
    return *this;
    //here i should find place for trit
}

TritSet::Proxy::operator Trit() const { // trit t = set[10];
    return m_set.getTrit(m_index);
}

Trit TritSet::getTrit(size_t index) {
    size_t bitMask = 3;//place for trit
    size_t idxArray = index / amountTrit;
    size_t idxTrit = index % amountTrit + 1;
    size_t trit = (m_arrTrit[idxArray] & bitMask << (sizeof(size_t) * BIT - idxTrit * 2)) >> (sizeof(size_t) * BIT - idxTrit * 2);
    switch (trit) {
        case 0:return F;
        case 1:return U;
        case 3:return T;
        default: return U;
    }
}

void TritSet::printTritSet() {
    for (size_t i = 0; i < m_size ; i++) {
        switch (getTrit(i)) {
            case 0:
                std::cout << "F ";
                break;
            case 1:
                std::cout << "U ";
                break;
            case 3:
                std::cout << "T ";
                break;
            default:
                std::cout << "NO TRITS";
        }
    }
    std::cout << std::endl;
}

size_t TritSet::getCapacity() const {
    return m_capacity;
}

size_t TritSet::getSizeArray() {
    return sizeof(*m_arrTrit) / sizeof (size_t);
}

TritSet& TritSet::makeEqual(TritSet& biggerSet) {
    TritSet tmp(biggerSet.m_size);
    memcpy(tmp.m_arrTrit, m_arrTrit, m_capacity * sizeof(size_t));
    *this = tmp;
    return *this;
}

TritSet operator&(TritSet &setA, TritSet &setB) {
    size_t size;
    if (setA.m_capacity > setB.m_capacity) {
        setB.makeEqual(setA);
    } else {
        setA.makeEqual(setB);
    }
    TritSet setC(setA.m_size);
    size = setA.m_capacity;
    for (size_t i = 0; i < size; i++) {
        setC.m_arrTrit[i] = setA.m_arrTrit[i] & setB.m_arrTrit[i];
    }
    return setC;
}

TritSet operator|(TritSet &setA, TritSet &setB) {
    if (setA.m_capacity > setB.m_capacity) {
        setB.makeEqual(setA);
    } else {
        setA.makeEqual(setB);
    }
    TritSet setC(setA.m_size);
    const size_t size = setA.m_capacity;
    for (size_t i = 0; i < size; i++) {
        setC.m_arrTrit[i] = setA.m_arrTrit[i] | setB.m_arrTrit[i];
    }
    return setC;
}

TritSet& TritSet::operator=(TritSet const & set) {
    if (&set == this) return *this;
    m_size = set.m_size;
    m_capacity = set.m_capacity;
    delete[] m_arrTrit;
    m_arrTrit = new size_t[m_capacity];
    memcpy(m_arrTrit, set.m_arrTrit, sizeof(size_t) * m_capacity);
    return *this;
}

TritSet TritSet::operator~(){  //переделать так, чтобы не изменял содержимое сета
    TritSet tmp(m_size);
    memcpy(tmp.m_arrTrit, m_arrTrit, m_capacity * sizeof(size_t));
    for (size_t i = 0; i < m_size ; i++) {
        if (static_cast<Trit>(tmp[i]) != U) {
            Trit trit = tmp[i];
            trit = static_cast<Trit>(~trit);
            trit = static_cast<Trit>(trit & 3);
            tmp[i] = trit;
        }
    }
    return tmp;
}

size_t TritSet::getUnknownTail() {
    size_t amountUnknown = 0;
    for (size_t i = 0; i < m_size; i++) {
        Trit tmp = (*this)[i];
        if (tmp == U) {
            amountUnknown++;
        }
    }
    return amountUnknown;
}

TritSet& TritSet::shrink () {
    int amountUnknown = this->getUnknownTail();
    int newSize = m_size - amountUnknown;
    m_size = newSize;
    m_capacity = ceil((double)newSize * 2 / 8 / sizeof(size_t));
    if (m_capacity == 0) {
        delete [] m_arrTrit;
        return *this;
    }
    size_t* arrTmp = new size_t[m_capacity];
    memcpy(arrTmp, m_arrTrit, m_capacity * sizeof(size_t));
    delete[] m_arrTrit;
    m_arrTrit = arrTmp;
    return *this;
}