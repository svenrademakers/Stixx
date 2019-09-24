#pragma once
#include "MemoryView.hpp"

namespace sx
{
template<class T, std::size_t N>
  class Buffer
  {
  public:
    Buffer() = default;
    sx::MemoryView<T> operator()
    {
      return sx::MemoryView<T>(buffer, buffer+N);
    }
    
    T& operator[](std::size_t index)
    {
      return buffer[index];
    }
    
  private:
    T buffer[N];
  };
}
