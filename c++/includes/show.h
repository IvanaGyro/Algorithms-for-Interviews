#ifndef SHOW_H
#define SHOW_H

#include <iterator>
#include <utility>

template <class Stream, class Vector,
          class Begin = decltype(std::begin(std::declval<Vector>()))>
inline Stream& operator<<(Stream& stream, const Vector& vect) {
    stream << "[";
    const char* dlm = "";
    for (const auto& i : vect) {
        stream << dlm << i;
        dlm = ", ";
    }
    stream << "]";
    return stream;
}

#endif  // SHOW_H
