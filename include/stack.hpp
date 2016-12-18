#ifndef STACK_1_0_STACK_H
#define STACK_1_0_STACK_H
#include <iostream>
#include <allocator.hpp>

class stack_error: public std::logic_error
{
public:
    explicit stack_error (const std::string& arg): std::logic_error (arg) {};
    explicit stack_error (const char* arg): std::logic_error (arg) {};
};

template <typename T>
class Stack: private allocator <T>
{
public:
    Stack(size_t size = 0);
    auto count() const noexcept ->size_t;
    auto push(T const&) /*strong*/ -> void;
    auto pop() throw (std::logic_error) /*strong*/ -> void;
    auto top () throw (std::logic_error) /*strong*/ ->  T;
    auto print () noexcept -> void;
    auto empty() noexcept -> bool;
};

// наследуем конструктор
template <typename T>
Stack<T>::Stack(size_t size) : allocator<T>(size) {};

// количество элементов стека
template <typename T>
auto Stack<T>::count() const noexcept ->size_t
{
    return allocator <T>::count_;
}

template <typename T>
auto Stack<T>::push(T const& value_) /*strong*/ -> void
{
    T* b;
    try
    {
        b = new T[allocator <T>::size_];
        std::copy(allocator<T>::p, allocator<T>::p + allocator<T>::count_, b);
    }
    catch (...)
    {
        delete [] b;
        throw ;
    }
    try
    {
        allocator<T>:: allocate();
    }
    catch(...)
    {
        delete [] allocator<T>::p;
        allocator<T>::size_ /=2;
        std::copy(b, b + allocator <T>::count_, allocator<T>::p);
        allocator <T>::p = b;
        throw ;
    }
    try
    {
        allocator<T>::p[allocator<T>::count_] = value_;
        allocator<T>::count_++;
    }
    catch (...)
    {
        throw ;
    }
}

template <typename T>
auto Stack<T>::pop()  throw (std::logic_error) /*strong*/ -> void
{
    if (!empty())
    {
        allocator<T>::count_--;
    }
    else
        throw stack_error("Error of pop()");
}

template <typename T>
auto Stack<T>::top () throw (std::logic_error) /*strong*/ -> T
{
    if (!empty())
    {
        return allocator<T>::p[allocator<T>::count_-1];
    }
    else
        throw stack_error ("Error of top()");
}

template <typename T>
auto Stack<T>::print () noexcept -> void
{
    if (empty())
        std:: cout << "Stack is empty!" << std:: endl;
    else
    {
        for (int i = 0; i < allocator<T>::count_; i++)
            std::cout << allocator<T>::p[i] << " ";
        std::cout << std::endl;
    }
}

template <typename T>
auto Stack<T>::empty() noexcept -> bool
{
    return (!allocator<T>::count_);
}

#endif //STACK_1_0_STACK_H
