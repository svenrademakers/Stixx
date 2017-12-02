#ifndef OBJECT_WRAPPER_HPP
#define OBJECT_WRAPPER_HPP

namespace sx
{
    template<typename T>
    class ObjectWrapper
    {
    public:
		using value_type = T;

		constexpr ObjectWrapper() = default;
		explicit ObjectWrapper(const T&&);
        operator const T &() const;
    protected:
        T handle;
    };

	template<typename T>
	ObjectWrapper<T>::ObjectWrapper(const T&& object)
		: handle(std::move(object))
	{}

    template<typename T>
    ObjectWrapper<T>::operator const T &() const
    {
        return handle;
    }
}

#endif