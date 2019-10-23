#ifndef TYPES_H_
#define TYPES_H_

#include <tuple>
#include <list>
#include <memory>

/**
 * Добавление к tuple (T) тип U
 */
template<typename T, typename U>
using AppendToTuple = decltype(std::tuple_cat(T{}, std::make_tuple(U{})));

/**
 * Генерирация tuple`а, состоящего из n - int`ов
 */
template<int n>
struct GenTupleOfInt {
   using type = AppendToTuple<typename GenTupleOfInt<n-1>::type, int>;
};
template<>
struct GenTupleOfInt<1> {
   using type = std::tuple<int>;
};

/// тип для хранения координат элемента матрицы
template<int n>
using Coords = typename GenTupleOfInt<n>::type;

/// тип для хранения одного элемента матрицы с координатами
template<class T, int n>
using Element = AppendToTuple<Coords<n>,T>;

/**
 * Тип списка всех элементов матрицы
 */
template<class T, int n>
using Elements = std::list<Element<T,n>>;

#endif /* TYPES_H_ */
