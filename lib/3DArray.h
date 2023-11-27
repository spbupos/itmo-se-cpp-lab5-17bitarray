#ifndef LABWORK4_3DARRAY_H
#define LABWORK4_3DARRAY_H

#include <iostream>
#include <cstdint>

#define INT17_MAX 0x1FFFF
#define MEM_LIMIT 0x40000000

class Array3D;

class Helper17BitNumber {
public:
    Array3D *parentArray;
    uint32_t self_pos, number = 0;

    bool getBit(uint32_t pos) const;
    void setBit(uint32_t pos, uint32_t value);
    uint32_t get17BitNumber(uint32_t pos) const;
    void set17BitNumber(uint32_t pos, uint32_t number);

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

std::ostream &operator<<(std::ostream &os, const Helper17BitNumber &number);
std::istream &operator>>(std::istream &is, Helper17BitNumber number);

class Array3D {
private:
    uint32_t real_size;
    static uint32_t realSizeInBytes(uint32_t size);
    uint32_t get1DIndex(uint32_t x, uint32_t y, uint32_t z) const;

public:
    char* array;
    uint32_t width, height, depth;

    Array3D(int32_t w, int32_t h, int32_t d);
    static Array3D newArray3D(int32_t w, int32_t h, int32_t d);

    Helper17BitNumber at(int32_t x, int32_t y, int32_t z);

    Array3D operator+(Array3D &other);
    Array3D operator-(Array3D &other);
    Array3D operator*(double value);

    ~Array3D();
};

std::ostream &operator<<(std::ostream &os, Array3D &array);
std::istream &operator>>(std::istream &is, Array3D &array);

#endif //LABWORK4_3DARRAY_H
