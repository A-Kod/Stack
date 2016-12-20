#ifndef STACK_Allocator_HPP
#define STACK_Allocator_HPP

template <typename T>
class Allocator
{
public:
    explicit
    Allocator( std::size_t size = 0);
    Allocator( Allocator const& other);
    auto operator =( Allocator const& other ) -> Allocator& = delete;
    ~Allocator();
    auto resize() -> void;
    auto swap(Allocator& other ) -> void;
    auto construct(T* ptr, T const & value ) -> void;
    auto destroy(T* ptr ) -> void;
    auto get() -> T*;
    auto get() const -> T const*;
    auto count() const noexcept -> size_t;
    auto full() const noexcept -> bool;
    auto empty() const noexcept-> bool;

private:
    T * p = nullptr;
    size_t size_ = 0;
    size_t count_ = 0;
};

template <typename T>
Allocator<T>::Allocator( std::size_t size ) : size_(size), p(static_cast<T*>(::operator new(size * sizeof(T), std::nothrow_t()))), count_(0)
{

}

template <typename T>
Allocator<T>::Allocator( Allocator const& other )
{
    if (count_ > 0)
    {
        for (int32_t i = --count_; i >= 0; --i)
            destroy(p+i);
    }
    operator delete(p);

    size_  = other.size_;
    count_ = other.count_;

    p = static_cast<T *>(::operator new(size_ * sizeof(T), std::nothrow_t()));
    for (size_t i = 0; i < other.count_; i++)
            construct(p + i, other.p[i]);
}

template <typename T>
Allocator<T>::~Allocator()
{
    if (count_ > 0)
    {
        for (int32_t i = --count_; i >= 0; --i)
            destroy(p+i);

    }
    operator delete(p);
}

template <typename T>
auto Allocator<T>::resize() -> void
{
    Allocator<T> alloc (size_ * 2 + (size_ == 0));
    for (size_t i = 0; i < size_; ++i)
        alloc.construct(alloc.get() + i, p[i]);
    alloc.swap(*this);
}

template <typename T>
auto Allocator<T>::swap(Allocator& other ) -> void
{
    std::swap(p, other.p);
    std::swap(size_, other.size_);
    std::swap(count_, other.count_);
}

template <typename T>
auto Allocator<T>::construct(T* ptr, T const & value ) -> void
{
    if ((ptr >= p) && (ptr < p + size_))
    {
        //По адресу ptr присваиваем значение value
            //placement new
        new(ptr)T(value);
        ++count_;
    }
    else
        {
            throw("error");
        }
}

template <typename T>
auto Allocator<T>::destroy(T* ptr ) -> void
{
    if ((ptr >= p) && (ptr <= p + count_))
    {
        ptr->~T();
        --count_;
    }
}

template <typename T>
auto Allocator<T>::get() -> T*
{
    return p;
}

template <typename T>
auto Allocator<T>::get() const -> T const*
{
    return p;
}

template <typename T>
auto Allocator<T>::count() const noexcept -> size_t
{
    return count_;
}

template <typename T>
auto Allocator<T>::full() const noexcept -> bool
{
    return count_ == size_ ? true: false;
}

template <typename T>
auto Allocator<T>::empty() const noexcept -> bool
{
    return count_ > 0 ? false: true;
}
#endif
