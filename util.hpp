#include <iostream>
#include <string>
namespace AGA::Util
{
  std::string removeCharStart(const std::string &str, char c);
  std::string removeCharEnd(const std::string &str, char c);
  template <typename Data>
  class List
  {
  private:
    Data *elements;
    size_t capacity;
    size_t size;

  public:
    List() : elements(nullptr), capacity(0), size(0) {}
    ~List() { delete[] elements; }
    void addEnd(const Data &item)
    {
      if (size == capacity)
      {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Data *newElements = new Data[newCapacity];

        for (size_t i = 0; i < size; ++i)
        {
          newElements[i] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
      }
      elements[size++] = item;
    }
    void addStart(const Data &item)
    {
      if (size == capacity)
      {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Data *newElements = new Data[newCapacity];

        for (size_t i = 0; i < size; ++i)
        {
          newElements[i + 1] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
      }
      else
      {
        for (size_t i = size; i > 0; --i)
        {
          elements[i] = elements[i - 1];
        }
      }
      elements[0] = item;
      size++;
    }
    Data get(size_t index) const
    {
      if (index >= size)
      {
        throw std::out_of_range("Index out of range");
      }
      return elements[index];
    }
    Data set(size_t index, const Data &item)
    {
      if (index >= size)
      {
        throw std::out_of_range("Index out of range");
      }
      Data old = elements[index];
      elements[index] = item;
      return old;
    }
    length() const
    {
      return size;
    }
  };
} // namespace AGA::Util

std::string
AGA::Util::removeCharStart(const std::string &str, char c)
{
  size_t firstPositionNoChar = str.find_first_not_of(c);
  return firstPositionNoChar == std::string::npos ? "" : str.substr(firstPositionNoChar);
}

std::string AGA::Util::removeCharEnd(const std::string &str, char c)
{
  size_t lastPositionNoChar = str.find_last_not_of(c);
  return lastPositionNoChar == std::string::npos ? "" : str.substr(0, lastPositionNoChar + 1);
}