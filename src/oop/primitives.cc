#include <primitives.hh>

template <typename T>
PrimitiveClass<T>::PrimitiveClass(T val) : value(val) {}

template <typename T>
PrimitiveClass<T>::PrimitiveClass(const PrimitiveClass& other) : value(other.value) {}

template <typename T>
const char* PrimitiveClass<T>::getType() const {
    return "#name";
}

template <typename T>
Object* PrimitiveClass<T>::clone() const {
    return new PrimitiveClass(*this);
}

template <typename T>
PrimitiveClass<T>& PrimitiveClass<T>::operator=(const PrimitiveClass& other) {
    if (this != &other) {
        this->value = other.value;
    }
    return *this;
}

template <typename T>
PrimitiveClass<T> PrimitiveClass<T>::operator+(const PrimitiveClass& other) const { return this->value + other.value; }
template <typename T>
PrimitiveClass<T> PrimitiveClass<T>::operator-(const PrimitiveClass& other) const { return this->value - other.value; }
template <typename T>
PrimitiveClass<T> PrimitiveClass<T>::operator*(const PrimitiveClass& other) const { return this->value * other.value; }
template <typename T>
PrimitiveClass<T> PrimitiveClass<T>::operator/(const PrimitiveClass& other) const { return this->value / other.value; }

template <typename T>
PrimitiveClass<T>& PrimitiveClass<T>::operator+=(const PrimitiveClass& other) { this->value += other.value; return *this; }
template <typename T>
PrimitiveClass<T>& PrimitiveClass<T>::operator-=(const PrimitiveClass& other) { this->value -= other.value; return *this; }
template <typename T>
PrimitiveClass<T>& PrimitiveClass<T>::operator*=(const PrimitiveClass& other) { this->value *= other.value; return *this; }
template <typename T>
PrimitiveClass<T>& PrimitiveClass<T>::operator/=(const PrimitiveClass& other) { this->value /= other.value; return *this; }

template <typename T>
bool PrimitiveClass<T>::operator==(const PrimitiveClass& other) const { return this->value == other.value; }
template <typename T>
bool PrimitiveClass<T>::operator!=(const PrimitiveClass& other) const { return this->value != other.value; }
template <typename T>
bool PrimitiveClass<T>::operator<(const PrimitiveClass& other) const { return this->value < other.value; }
template <typename T>
bool PrimitiveClass<T>::operator<=(const PrimitiveClass& other) const { return this->value <= other.value; }
template <typename T>
bool PrimitiveClass<T>::operator>(const PrimitiveClass& other) const { return this->value > other.value; }
template <typename T>
bool PrimitiveClass<T>::operator>=(const PrimitiveClass& other) const { return this->value >= other.value; }

template <typename T>
T PrimitiveClass<T>::getValue() const { return this->value; }
template <typename T>
void PrimitiveClass<T>::setValue(T val) { this->value = val; }
template <typename T>
T PrimitiveClass<T>::raw() const { return this->value; }

template class PrimitiveClass<int>;
template class PrimitiveClass<double>;
template class PrimitiveClass<float>;
template class PrimitiveClass<bool>;
template class PrimitiveClass<char>;
template class PrimitiveClass<u8>;
template class PrimitiveClass<u16>;
template class PrimitiveClass<u32>;
template class PrimitiveClass<u64>;
template class PrimitiveClass<i8>;
template class PrimitiveClass<i16>;
template class PrimitiveClass<i32>;
template class PrimitiveClass<i64>;
template class PrimitiveClass<usize>;
template class PrimitiveClass<usize>;
