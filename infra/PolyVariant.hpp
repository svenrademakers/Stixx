#ifndef POLYVARIANT_HPP
#define POLYVARIANT_HPP

#include <algorithm>
#include "TemplateHelper.h"

// Polyvariant is a variant that holds derivatives of a specific interface or Base class
// experiment: if users adhere to the liskov principle a Get that returns Base should be sufficient
// without the need for casting to a dervative...
namespace sx
{
	template<class Base, typename... T>
	class PolyVariant
	{
	public:
		static constexpr std::size_t Size = MaxSize<sizeof(T)...>::value;
		static_assert(RecursiveBaseOf<Base, T...>::value, "some types in variadic type list do not decent from base type");

		PolyVariant(const PolyVariant&) = delete;
		PolyVariant& operator=(const PolyVariant&) = delete;
		PolyVariant()
		{
			new (std::addressof(storage)) Front<T...>::value_type();
		}

		template<typename T, typename...Args>
		PolyVariant(T, Args&&... args)
		{
			Construct<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename...Args>
		T& emplace(Args&&... args)
		{
			return Construct<T>(std::forward<Args>(args)...);
		}

		Base* const Get()
		{
			return reinterpret_cast<Base*>(&storage);
		}

		template<class U>
		operator const U&()
		{
			static_assert(TypeInList<U, T...>::value, "cannot cast to type thats not declared in variant");
			return *reinterpret_cast<U*>(Get());
		}

	private:
		template<typename T, typename...Args>
		T& Construct(Args&&... args)
		{
			return *(new (std::addressof(storage)) T(std::forward<Args>(args)...));
		}

		typename std::aligned_union<Size, T...>::type storage;
	};
}

#endif