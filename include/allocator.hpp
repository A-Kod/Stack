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
    auto deallocate() -> void;

    T * p = nullptr;
    size_t size_ = 0;
    size_t count_ = 0;
};

template <typename T>
allocator<T>::allocator(size_t size)
{
    // инициализация полей класса
    size_ = size;
    // выделение памяти и приведение void*, который возвращает new, к T*
    p = static_cast<T*>(::operator new(size * sizeof(T)));
}

// деструктор
template <typename T>
allocator<T>::~allocator()
{
    // освобождаем выделенную динамическую память
    for(int i = 0; i < count_; ++i)
        p[i].~T();
    ::operator delete(p);
}

// обмен значениями на уровне указателей - вспомогательный метод для allocate()
template <typename T>
auto allocator<T>::swap(allocator & other) -> void
{
    std::swap(p, other.p);
    std::swap(count_, other.count_);
    std::swap(size_, other.size_);
}


template <typename T>
auto allocator<T>::allocate() -> void
{
    T* b = p;
    size_ *= 2;
    try
    {
        allocator<T> alloc(size_);
        std::copy(p, p + count_, alloc.p);
        alloc.count_ = count_;
        swap(alloc);
    }
    catch(...)
    {
        p = b;
        size_ /= 2;
        b = nullptr;
        throw;
    }
}

template <typename T>
auto allocator<T>::deallocate() -> void
{
    size_ /= 2;
    allocator<T> dealloc(size_);
    std::copy(p, p + count_, dealloc.p);
    swap(dealloc);
}

#endif
