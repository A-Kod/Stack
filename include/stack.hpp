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
    auto push(T const&) /*strong*/ -> void;
    auto pop() throw (std::logic_error) /*strong*/ -> void;
    auto top () throw (std::logic_error) /*strong*/ ->  T;
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
auto Stack<T>::push(T const& value_) /*strong*/ -> void
{
    T* b;

    try
    {
        b = new T[array_size_];
        std::copy(array_, array_+count_, b);
    }
    catch(...)
    {
        delete[] b;
        throw ;
    }

    if (count_ == array_size_)
    {
        array_size_ += array_size_;
        T* a;

        try
        {
            a = new T[array_size_];
            std::copy(array_, array_+count_, a);
            delete[] array_;
            array_ = a;
        }
        catch (...)
        {
            array_size_ /= 2;
            delete[] a;
            delete[] b;

            throw ;
        }

    }

    try
    {
        array_[count_] = value_;
        ++count_;
    }
    catch (...)
    {
        delete[] array_;
        array_ = b;
        array_size_ /= 2;
        throw;
    }

    delete[] b;
}

template <typename T>
auto Stack<T>::pop()  throw (std::logic_error) /*strong*/ -> void
{
    //
    if (!empty())
    {
        count_--;
    }
    else
        throw stack_error("Error of pop()");
}

template <typename T>
auto Stack<T>::top () throw (std::logic_error) /*strong*/ -> T
{
    if (!empty())
    {
        return array_[count_-1];
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
