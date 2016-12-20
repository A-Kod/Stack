#ifndef Stack_1_0_Stack_H
#define Stack_1_0_Stack_H
#include <iostream>
#include "allocator.hpp"

class Stack_error: public std::logic_error
{
public:
    explicit Stack_error (const std::string& arg): std::logic_error (arg) {};
    explicit Stack_error (const char* arg): std::logic_error (arg) {};
};

template <typename T>
class Stack
{
public:

    explicit
    Stack(size_t size = 0);

    auto count() const noexcept -> size_t ;
    auto push(T const& value) -> void;
    auto top() const throw (std::logic_error) -> T;
    auto pop() throw (std::logic_error) -> void;
    auto empty() const noexcept -> bool;

private:
    Allocator<T> alloc;
};

template <typename T>
Stack<T>::Stack(size_t size): alloc(size)
{
}


template <typename T>
auto Stack<T>::count() const noexcept -> size_t
{
    return alloc.count();
}


template <typename T>
auto Stack<T>::empty() const noexcept -> bool
{
    return (alloc.empty());
}

template <typename T>
auto Stack<T>::push(T const& value) -> void
{

    if ((alloc.empty()) || (alloc.full()))
    {
        try
        {
            alloc.resize();
        }
        catch (...)
        {
            throw;
        }
    }

    try
    {
        alloc.construct(alloc.get() + alloc.count(), value);
    }
    catch(...)
    {
        throw;
    }
}


template <typename T>
auto Stack<T>::pop()  throw (std::logic_error) -> void
{

    if (!empty())
    {
        alloc.destroy(alloc.get() + alloc.count() - 1);
    }
    else
        throw Stack_error("Error of pop()");
}

template <typename T>
auto Stack<T>::top () const throw (std::logic_error) -> T
{
    if (!empty())
    {
        return alloc.get()[alloc.count()-1];
    }
    else
        throw Stack_error ("Error of top()");
}

#endif //Stack_1_0_Stack_H
