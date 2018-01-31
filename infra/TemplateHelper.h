#ifndef TEMPLATE_HELPER_HPP
#define TEMPLATE_HELPER_HPP

#include <type_traits>

namespace sx
{
	template<typename T, typename ...other>
	struct Front
	{
		using value_type = T;
	};

	template <std::size_t... others>
	struct MaxSize;

	template <std::size_t T>
	struct MaxSize<T>
	{
		static constexpr size_t value = T;
	};

	template <size_t T1, size_t T2, size_t ... others>
	struct MaxSize<T1, T2, others...>
	{
		static constexpr size_t value = T1 >= T2 ? MaxSize<T1, others...>::value :
			MaxSize<T2, others...>::value;
	};

	template <typename... T>
	struct RecursiveBaseOf;

	template<typename T>
	struct RecursiveBaseOf<T>
	{
		static constexpr bool value = true;
	};

	template<typename T, typename T2>
	struct RecursiveBaseOf<T, T2>
	{
		static constexpr bool value = std::is_base_of<T, T2>();
	};

	template<typename T, typename T2, typename... other>
	struct RecursiveBaseOf<T, T2, other...>
	{
		static constexpr bool value = RecursiveBaseOf<T, T2>::value && RecursiveBaseOf<other...>::value;
	};

	template <typename... T>
	struct TypeInList;

	template<typename T, typename T2>
	struct TypeInList<T, T2>
	{
		static constexpr bool value = std::is_same<T, T2>();
	};

	template<typename T, typename T2, typename... other>
	struct TypeInList<T, T2, other...>
	{
		static constexpr bool value = TypeInList<T, T2>::value ? true : TypeInList<T, other...>::value;
	};
}


#endif