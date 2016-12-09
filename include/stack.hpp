#ifndef STACK_1_0_STACK_H
#define STACK_1_0_STACK_H
#include <iostream>
#include <stdexcept>

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
    size_t count() const;
    void push(T const&);
    auto pop()  throw (std::logic_error) -> T;
    void print ();
    bool empty();
    ~Stack();
private:
    T * array_;
    size_t array_size_;
    size_t count_;
};

template <typename T>
Stack<T>::Stack()
{
    // общее количество памяти при инициализации стека - под 100 элементов
    array_size_ = 5;
    array_ = new T[array_size_];

    // изначально стек пустой
    count_ = 0;
}

template <typename T>
size_t Stack<T>::count() const
{
    return count_;
}



template <typename T>
void Stack<T>::push(T const& value_)
{

    // если элемент не помещается в стек
    if (count_ == array_size_)
    {
        //новый размер
        size_t size = 2 * array_size_;
        //новая временная память - это a
        T *a = new T[size];
        //сохраняем в массив a то, что лежит в array
        //std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
        std::copy(array_, array_ + array_size_, a);
        delete[] array_;
        //перекидываем указатель
        array_ = a;
        array_size_ = size;
    }
    array_[count_] = value_;
    ++count_;
}


template <typename T>
auto Stack<T>::pop() throw (std::logic_error) -> T
{
    // если стек не пустой
    if (!empty())
    {
        --count_;
        return array_[count_];
    }
    else
        throw stack_error ("Error of pop()");
}

template <typename T>
void Stack<T>::print ()
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
bool Stack<T>::empty()
{
    if (count_ == 0)
        return 1;
    return 0;

    //    return array_size_>0 ? false: true;
}

template <typename T>
Stack<T>::~Stack()
{
    delete [] array_;
    array_size_ = 0;
}

#endif //STACK_1_0_STACK_H
