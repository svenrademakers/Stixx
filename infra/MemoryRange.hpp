#ifndef MEMORY_RANGE_HPP
#define MEMORY_RANGE_HPP

#include <cassert>
#include <vector>
#include <iterator>

namespace sx
{
    template<class T>
    class FixedMemoryRange
    {
    public:
        typedef typename T* iterator;
        typedef typename const T* const_iterator;

        template<typename T2, std::size_t N>
        constexpr FixedMemoryRange(const std::array<T2, N>& arr)
            : beginElement(arr.data())
            , endElement(arr.data() + arr.size())
        {}

        constexpr FixedMemoryRange(iterator begin, iterator end)
            : beginElement(begin)
            , endElement(end)
        {}

        constexpr T& operator[](const std::size_t index) const
        {
            return *const_cast<T*>(beginElement + index);
        }

        constexpr iterator begin() const
        {
            return beginElement;
        }

        constexpr const_iterator cbegin() const
        {
            return beginElement;
        }

        constexpr iterator end() const
        {
            return endElement;
        }

        constexpr const_iterator cend() const
        {
            return endElement;
        }

        constexpr std::size_t size() const
        {
            return std::distance(beginElement, endElement);
        }

    protected:
        const const_iterator beginElement;
        const const_iterator endElement;
    };

    template<class T>
    class MemoryRange
    {
    public:
        typedef typename T* iterator;

        MemoryRange() = default;

        explicit MemoryRange(std::vector<T>& vector)
            : beginElement(vector.data())
            , endElement(vector.data() + vector.size())
        {}

        constexpr MemoryRange(iterator begin, iterator end)
            : beginElement(begin)
            , endElement(end)
        {}

        constexpr iterator begin()
        {
            return beginElement;
        }

        constexpr iterator end()
        {
            return endElement;
        }

        constexpr std::size_t size()
        {
            return std::distance(beginElement, endElement);
        }

        void shrink(std::size_t newSize)
        {
            if (newSize < size())
                endElement = beginElement + newSize;
        }

    protected:
        iterator beginElement;
        iterator endElement;
    };

    template<class T>
    class MemoryRange2D
        : public MemoryRange<T>
    {
    public:
        explicit MemoryRange2D(MemoryRange<T> memRange, const uint32_t width)
            : MemoryRange<T>(memRange)
            , rowSize(width)
        {}

        template<class T2>
        explicit MemoryRange2D(std::vector<T2>& vector, const uint32_t width)
            : MemoryRange<T>(vector)
            , rowSize(width)
        {}

        constexpr uint32_t width()
        {
            return rowSize;
        }

    private:
        const uint32_t rowSize;
    };
}
#endif
