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
    auto pop() throw (std::logic_error) -> void;
    auto top () throw (std::logic_error) ->  T;
    auto print () -> void;
    auto empty() -> bool;
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
    array_size_ = 100;
    array_ = new T[array_size_];

    // изначально стек пустой
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
    // если элемент не помещается в стек
   if (count_ + 1 > array_size_) {
       // сохранение данных
       T *a = new T[array_size_];
       for (int i = 0; i < array_size_; ++i) {
           a[i] = array_[i];
       }
       delete[] array_;
       array_size_ += 100;

       // выделение новой памяти
       array_ = new T[array_size_];
       for (int i = 0; i < array_size_ - 100; ++i) {
           array_[i] = a[i];
       }
   }

    // освобождаем место для очередного элемента
    for (int i = count_-1; i>=0 ; i--)
    {
        array_[i+1] = array_[i];
    }

    // добавляем элемент в вершику стека
    array_[0] = value_;

    // увеличиваем размер стека
    count_++;

}

template <typename T>
auto Stack<T>::pop()  throw (std::logic_error) -> void
{
    // если стек не пустой
    if (!empty())
    {
        // сохраняем вершину стека
        T value_ = array_[0];

        // уменьшаем количество элементов на 1
        count_--;

        // смещаем стек на один элемент
        for (int i = 0; i < count_; ++i) {
            array_[i] = array_[i + 1];
        }
    }
    else
        throw stack_error("Error of pop()");
}

template <typename T>
auto Stack<T>::top () throw (std::logic_error) -> T
{
    if (!empty())
     return array_[0];
    else
        throw stack_error("Error of top()");
}

template <typename T>
auto Stack<T>::print () -> void
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
auto Stack<T>::empty() -> bool
{
   return count_>0 ? false: true;
}

template <typename T>
Stack<T>::~Stack()
{
    delete [] array_;
    array_size_ = 0;
}
