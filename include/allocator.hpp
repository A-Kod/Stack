#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP

#include <algorithm>

template <typename T>
class allocator
{
protected:
    allocator(size_t size = 0);
    allocator(const allocator &) = delete;
    ~allocator();

    auto operator = (const allocator &) -> allocator & = delete;
    auto swap(allocator & other) -> void;
    auto allocate() -> void;

    T * p;
    size_t size_;
    size_t count_;
};

template <typename T>
allocator<T>::allocator(size_t size)
{
    // инициализация полей класса
    count_ = 0;
    size_ = size;
    p = new T[size_];
    // выделение памяти и приведение void*, который возвращает new, к T*
    // static_cast<T*>(::operator new(size * sizeof(T)));
}

// деструктор
template <typename T>
allocator<T>::~allocator()
{
    // освобождаем выделенную динамическую память
    //delete [] _ptr;
    for(int i = 0; i < count_; ++i)
        p[i].~T();
    ::operator delete(p);
}

// обмен значениями на уровне указателей - вспомогательный метод для allocate()
template <typename T>
auto allocator<T>::swap(allocator & other) -> void
{
    auto t = p;
    p = other.p;
    other.p = t;
}

template <typename T>
auto allocator<T>::allocate() -> void
{
    // если выделенная память закончилась
    if (size_ == count_ )
    {
        auto s = 1;

        // если размер выделенной памяти больше 0
        if (size_)
         s = size_*2;

        // копируем данные в новую область памяти, меняем размер
        allocator<T> alloc(s);
        std::copy(p, p + count_, alloc.p);
        swap(alloc);
        size_ = s;
    }
}


#endif
