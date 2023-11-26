#ifndef LABWORK4_3DARRAY_H
#define LABWORK4_3DARRAY_H

#include <iostream>
#include <cstdint>

class Array3D;
class Helper17BitNumber {
private:
    Array3D *parentArray;
    uint32_t self_pos, number = 0;

    bool getBit(uint32_t pos) const;
    void setBit(uint32_t pos, uint32_t value);
    uint32_t get17BitNumber(uint32_t pos) const;
    void set17BitNumber(uint32_t pos, uint32_t number);

public:
    Helper17BitNumber(Array3D* array, uint32_t pos);
    uint32_t operator=(auto value) {
        set17BitNumber(self_pos, uint32_t(value));
        return value;
    }
    operator uint32_t();

    bool operator<(auto value) const {
        return number < value;
    }
    bool operator>(auto value) const {
        return number > value;
    }
    bool operator==(auto value) const {
        return number == value;
    }
    bool operator<=(auto value) const {
        return number <= value;
    }
    bool operator>=(auto value) const {
        return number >= value;
    }
    bool operator!=(auto value) const {
        return number != value;
    }

    std::ostream &operator<<(std::ostream &os) const;
    std::istream &operator>>(std::istream &is);

    auto operator+(auto value) const {
        return number + value;
    }
    auto operator-(auto value) const {
        return number - value;
    }
    auto operator*(auto value) const {
        return number * value;
    }
    auto operator/(auto value) const {
        return number / value;
    }
    auto operator%(auto value) const {
        return number % value;
    }
    auto operator&(auto value) const {
        return number & value;
    }
    auto operator|(auto value) const {
        return number | value;
    }
    auto operator^(auto value) const {
        return number ^ value;
    }
    auto operator<<(uint32_t value) const {
        return number << value;
    }
    auto operator>>(uint32_t value) const {
        return number >> value;
    }

    auto operator+=(auto value) {
        number += value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator-=(auto value) {
        number -= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator*=(auto value) {
        number *= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator/=(auto value) {
        number /= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator%=(auto value) {
        number %= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator&=(auto value) {
        number &= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator|=(auto value) {
        number |= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator^=(auto value) {
        number ^= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator<<=(auto value) {
        number <<= value;
        set17BitNumber(self_pos, number);
        return number;
    }
    auto operator>>=(auto value) {
        number >>= value;
        set17BitNumber(self_pos, number);
        return number;
    }
};

class Array3D {
public:
    char* array;
    uint32_t width, height, depth;
    uint32_t real_size;

    static uint32_t realSizeInBytes(uint32_t size);
    Array3D(uint32_t w, uint32_t h, uint32_t d);
    uint32_t get1DIndex(uint32_t x, uint32_t y, uint32_t z);

    Helper17BitNumber at(uint32_t x, uint32_t y, uint32_t z);
};

#endif //LABWORK4_3DARRAY_H
