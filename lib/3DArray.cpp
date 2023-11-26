#include "3DArray.h"

bool Helper17BitNumber::getBit(uint32_t pos) const {
    return (parentArray->array[pos / 8] & (1 << (pos % 8))) != 0;
}

void Helper17BitNumber::setBit(uint32_t pos, uint32_t value) {
    if (value)
        parentArray->array[pos / 8] |= 1 << (pos % 8);
    else
        parentArray->array[pos / 8] &= ~(1 << (pos % 8));
}

uint32_t Helper17BitNumber::get17BitNumber(uint32_t pos) const {
    uint32_t start = pos * 17;
    uint32_t result = 0;
    for (uint32_t i = 0; i < 17; i++)
        result |= getBit(start + i) << i;
    return result;
}

void Helper17BitNumber::set17BitNumber(uint32_t pos, uint32_t num) {
    /* get starting bit */
    uint32_t start = pos * 17;
    /* set 17 bits */
    for (uint32_t i = 0; i < 17; i++)
        setBit(start + i, num & (1 << i));
}

Helper17BitNumber::Helper17BitNumber(Array3D* array, uint32_t pos) {
    parentArray = array;
    self_pos = pos;
    number = get17BitNumber(pos);
}

Helper17BitNumber::operator uint32_t() {
    number = get17BitNumber(self_pos);
    return number;
}

std::ostream &Helper17BitNumber::operator<<(std::ostream &os) const {
    os << number;
    return os;
}

std::istream &Helper17BitNumber::operator>>(std::istream &is) {
    is >> number;
    set17BitNumber(self_pos, number);
    return is;
}

uint32_t Array3D::realSizeInBytes(uint32_t size) {
    return size * 17 / 8 + 1;
}

Array3D::Array3D(uint32_t w, uint32_t h, uint32_t d) {
    width = w;
    height = h;
    depth = d;
    real_size = realSizeInBytes(w * h * d);
    array = new char[real_size];
}

uint32_t Array3D::get1DIndex(uint32_t x, uint32_t y, uint32_t z) {
    return x + y * width + z * width * height;
}

Helper17BitNumber Array3D::at(uint32_t x, uint32_t y, uint32_t z) {
    return {this, get1DIndex(x, y, z)};
}
