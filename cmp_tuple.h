#ifndef CMP_TUPLE_H_
#define CMP_TUPLE_H_

///Сравнение
namespace cmp {

	/**
	 * Cравнение первых n элементов у двух tuple
	 */
	template<int n, class T, class U,  int index = n-1>
	struct tuple_impl {
	   bool operator() (const T& t1, const U& t2)
	   {
		  return std::get<index>(t1) == std::get<index>(t2)
			and tuple_impl<n,T,U,index-1>()(t1,t2);
	   }
	};

	template<int n, class T, class U>
	struct tuple_impl<n,T,U,-1> {
	   bool operator() (const T& t1, const U& t2)
	   {
		  return true;
	   }
	};
	template<int n, class T, class U>
	bool tuple (const T& t1, const U& t2)
	{
	   return tuple_impl<n,T,U,n-1>()(t1,t2);
	}
}





#endif /* CMP_TUPLE_H_ */
