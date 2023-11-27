#include <stdexcept>
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
    if (num > INT17_MAX)
        throw std::out_of_range("Number is too big for 17 bits");

    uint32_t start = pos * 17;
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

std::ostream &operator<<(std::ostream &os, const Helper17BitNumber &number) {
    os << number.number;
    return os;
}

std::istream &operator>>(std::istream &is, Helper17BitNumber number) {
    is >> number.number;
    number.set17BitNumber(number.self_pos, number.number);
    return is;
}

uint32_t Array3D::realSizeInBytes(uint32_t size) {
    return size * 17 / 8 + 1;
}

Array3D::Array3D(int32_t w, int32_t h, int32_t d) {
    if (w <= 0 || h <= 0 || d <= 0)
        throw std::invalid_argument("Array size must be positive");
    if (uint64_t(w) * h * d / 8 * 17 > MEM_LIMIT)
        throw std::out_of_range("Array size is too big");

    width = w;
    height = h;
    depth = d;
    real_size = realSizeInBytes(w * h * d);
    array = new char[real_size];
    /* fill array with zeros */
    for (uint32_t i = 0; i < real_size; i++)
        array[i] = 0;
}

Array3D Array3D::newArray3D(int32_t w, int32_t h, int32_t d) {
    return {w, h, d};
}

uint32_t Array3D::get1DIndex(uint32_t x, uint32_t y, uint32_t z) const {
    return x + y * width + z * width * height;
}

Helper17BitNumber Array3D::at(int32_t x, int32_t y, int32_t z) {
    if (x >= width || x < 0 || y >= height || y < 0 || z >= depth || z < 0)
        throw std::out_of_range("Index is out of range");
    return {this, get1DIndex(x, y, z)};
}

std::ostream &operator<<(std::ostream &os, Array3D &array) {
    os << "Array3D(" << array.width << ", " << array.height << ", " << array.depth << ")\n";
    for (uint32_t z = 0; z < array.depth; z++) {
        os << "z = " << z << '\n';
        for (uint32_t y = 0; y < array.height; y++)
            for (uint32_t x = 0; x < array.width; x++)
                os << array.at(x, y, z) << (x == array.width - 1 ? "\n" : ", ");
    }
    return os;
}

std::istream &operator>>(std::istream &is, Array3D &array) {
    for (uint32_t z = 0; z < array.depth; z++) {
        for (uint32_t y = 0; y < array.height; y++)
            for (uint32_t x = 0; x < array.width; x++) {
                is >> array.at(x, y, z);
            }
    }
    return is;
}

Array3D Array3D::operator+(Array3D &other) {
    if (width != other.width || height != other.height || depth != other.depth)
        throw std::invalid_argument("Arrays have different sizes");

    Array3D result(width, height, depth);
    for (uint32_t z = 0; z < depth; z++)
        for (uint32_t y = 0; y < height; y++)
            for (uint32_t x = 0; x < width; x++) {
                auto r = at(x, y, z) + other.at(x, y, z);
                if (r > INT17_MAX)
                    throw std::out_of_range("Number is too big for 17 bits");
                result.at(x, y, z) = r;
            }
    return result;
}

Array3D Array3D::operator-(Array3D &other) {
    if (width != other.width || height != other.height || depth != other.depth)
        throw std::invalid_argument("Arrays have different sizes");

    Array3D result(width, height, depth);
    for (uint32_t z = 0; z < depth; z++)
        for (uint32_t y = 0; y < height; y++)
            for (uint32_t x = 0; x < width; x++) {
                auto r = at(x, y, z) - other.at(x, y, z);
                if (r > INT17_MAX)
                    throw std::out_of_range("Number is too big for 17 bits");
                if (r < 0)
                    throw std::out_of_range("We can store only unsigned numbers");
                result.at(x, y, z) = r;
            }
    return result;
}

Array3D Array3D::operator*(double value) {
    Array3D result(width, height, depth);
    for (uint32_t z = 0; z < depth; z++)
        for (uint32_t y = 0; y < height; y++)
            for (uint32_t x = 0; x < width; x++) {
                if (value < 0)
                    throw std::invalid_argument("We can store only unsigned numbers");
                auto r = at(x, y, z) * value;
                if (r > INT17_MAX)
                    throw std::out_of_range("Number is too big for 17 bits");
                result.at(x, y, z) = uint32_t(r);
            }
    return result;
}

Array3D::~Array3D() {
    delete[] array;
}
