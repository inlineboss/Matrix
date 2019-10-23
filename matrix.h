#ifndef MATRIX_H_
#define MATRIX_H_

#include <algorithm>
#include "types.h"
#include "cmp_tuple.h"

template<class Type, int Default, int n = 2>
class Matrix
{
public:
   Matrix() : pointer (std::make_shared<Elements<Type,n>>()) { }


   /// структура, которая "знает" с каким элементом матрицы надо работать
   template<int index = 1>
   struct ProxyElement
   {

	  std::weak_ptr<Elements<Type,n>> elements;

	  Coords <n> coord;

      ProxyElement<index> operator = (Type v) const
      {
         static_assert (index == n, "Неполная размерность");

         auto sameX = [&](const auto& element) {

            return cmp::tuple<n>(coord, element);
         };

         auto p = elements.lock();

         if (p) {

            if (v != Default) {

               auto it = std::find_if (
                  p->begin(),
                  p->end(),
                  sameX
               );

               if (it == p->end()) {

                  p->push_back(std::tuple_cat(coord,std::make_tuple(v)));

               } else {

                  std::get<n>(*it) = v;

               }
            } else {

               p->remove_if (sameX);

            }

         } else {

            throw std::bad_weak_ptr();

         }
         return *this;
      }

      /**
       *
       * @param y - Индекс по Y
       * @return Указатель на матрицу c второй координатой
       */
      ProxyElement<index+1> operator [] (int y) {

         static_assert (index < n, "выход за пределы размеров матрицы");

         std::get<index>(coord) = y;

         return *reinterpret_cast<ProxyElement<index+1>*>(this);
      }


      /**
       * Подстановка хранимого значения при разыминовании
       */
      operator Type() const
      {
         static_assert (index == n, "неполная размерность");

         Type res = Default;

         auto p = elements.lock();

         if (p) {

            for (const auto& element : *p) {

               if (cmp::tuple<n>(coord, element)) {

                  return std::get<n>(element);

               }

            }

         } else {

			 throw std::bad_weak_ptr();

		 }

         return res;
      }
   };


   /**
    * @param x - Индекс по X
    * @return Указатель на матрицу c первой координатой
    */
   ProxyElement<1> operator [] (int x) {

      auto element = ProxyElement<1>();

      element.elements = pointer;

      std::get<0>(element.coord) = x;

      return element;
   }

   auto size()  { return pointer->size();  }

   auto begin() { return pointer->begin(); }

   auto end()   { return pointer->end();   }

   template<class Compare> void sort (Compare comp) { pointer->sort(comp); }


private:

   std::shared_ptr<Elements<Type,n>> pointer;

};


#endif /* MATRIX_H_ */
