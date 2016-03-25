#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <cmath>

using std::pair;

template <typename T, typename U> pair<T, U> operator+ (const pair<T, U>& l, const pair<T, U>& r) { return{ l.first + r.first, l.second + r.second }; }
template <typename T, typename U> pair<T, U> operator+= (pair<T, U>& l, const pair<T, U>& r) { l.first += r.first; l.second += r.second; return l; }
template <typename T, typename U> pair<T, U> operator- (const pair<T, U>& l, const pair<T, U>& r) { return{ l.first - r.first, l.second - r.second }; }
template <typename T, typename U> pair<T, U> operator-= (pair<T, U>& l, const pair<T, U>& r) { l.first -= r.first; l.second -= r.second; return l; }
template <typename T, typename U> pair<T, U> operator* (pair<T, U>& l, const float r) { return{ l.first * r, l.second * r }; }
template <typename T, typename U> pair<T, U> operator*= (pair<T, U>& l, const float r) { l.first *= r; l.second *= r; return l; }
template <typename T, typename U> pair<T, U> operator* (const float l, const pair<T, U>& r) { return{ r.first * l, r.second * l }; }
template <typename T, typename U> pair<T, U> operator/ (pair<T, U>& l, const float r) { return{ l.first / r, l.second / r }; }
template <typename T, typename U> pair<T, U> operator/= (pair<T, U>& l, const float r) { l.first /= r; l.second /= r; return l; }
template <typename T, typename U> pair<T, U> operator/ (const float l, const pair<T, U>& r) { return{ r.first / l, r.second / l }; }

template <typename T, typename U> float length(const pair<T, U>& a) {
    return std::sqrt(a.first*a.first + a.second*a.second);
}

#endif