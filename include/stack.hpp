#ifndef STACK_1_0_STACK_H
#define STACK_1_0_STACK_H
#include <iostream>

class stack_error: public std::logic_error
{
public:
    explicit stack_error (const std::string& arg): std::logic_error (arg) {};
    explicit stack_error (const char* arg): std::logic_error (arg) {};
};

template <typename T>
class Stack
{
public:
    Stack();
    auto count() const noexcept ->size_t;
    auto push(T const&) noexcept -> void;
    auto pop() throw (std::logic_error) -> T;
    auto top () throw (std::logic_error) ->  void;
    auto print () noexcept -> void;
    auto empty() noexcept -> bool;
    ~Stack();
private:
    static const size_t default_size = 100;
    T * array_;
    size_t array_size_;
    size_t count_;
};

template <typename T>
Stack<T>::Stack()
{
    array_ = new T[default_size];
    array_size_ = default_size;
    count_ = 0;
}

template <typename T>
auto Stack<T>::count() const noexcept ->size_t
{
    return count_;
}

template <typename T>
auto Stack<T>::push(T const& value_) noexcept -> void
{
    if (count_ == array_size_)
    {
        size_t size = 2 * array_size_;
        T *a = new T[size];
        std::copy(array_, array_ + array_size_, a);
        delete[] array_;
        array_ = a;
        array_size_ = size;
    }
    array_[count_] = value_;
    ++count_;
}

template <typename T>
auto Stack<T>::pop()  throw (std::logic_error) -> T
{
    if (!empty())
    {
        --count_;
        return array_[count_];
    }
    else
        throw stack_error ("Error of pop()");
}

template <typename T>
auto Stack<T>::top () throw (std::logic_error) -> void
{
//    if (!empty())
//        return array_[0];
//    else
//        throw stack_error("Error of top()");
}

template <typename T>
auto Stack<T>::print () noexcept -> void
{
    if (empty())
        std:: cout << "Stack is empty!" << std:: endl;
        else
    {
        for (int i = 0; i < count_; i++)
            std::cout << array_[i] << " ";
        std::cout << std::endl;
    }
        }
        
template <typename T>
auto Stack<T>::empty() noexcept -> bool
    {
        return count_ > 0 ? false: true;
    }

template <typename T>
 Stack<T>::~Stack()
    {
        delete [] array_;
    }
        
#endif //STACK_1_0_STACK_H
