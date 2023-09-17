#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


template <class T, class Allocator = std::allocator<T> >
struct my_vector {
void push_back(const T& x)
{
    std::cout<<"size:"<<size<<std::endl;
    if (!size)
    {
        capacity = 1;
        data = alloc.allocate(capacity);
        //std::cout<<"1"<<std::endl;
    }
    else 
    if (size == capacity)
    {
        //std::cout<<"1.25"<<std::endl;
        capacity = capacity * 2 + 1;
        std::cout<<"capacity:"<<capacity<<std::endl;
        //T* newData = ::operator new(capacity * sizeof(T));
        T* newData = alloc.allocate(capacity);
        //std::cout<<"1 4"<<std::endl;
        std::copy(data, data + size * sizeof(T), newData); //naive
        //std::cout<<"1 5"<<std::endl;
        std::swap(newData, data);
        //std::cout<<"1 6"<<std::endl;
        alloc.deallocate(newData, size);
    }
    //std::cout<<"1.5"<<std::endl;
    alloc.construct(data + size * sizeof(T), x);
    ++size;
    //std::cout<<"2"<<std::endl;
}

T operator[](unsigned int i)
{
    return *(data+size*i);
}
void allocate(const int n)
{
    data = alloc.allocate(capacity);
    //???
}

private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    T* data = nullptr;

    Allocator alloc;
};

my_vector<int, std::allocator<int>> m;


//stateless allocator
template <class T>
struct std_03_allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    std_03_allocator () noexcept {}
    template <class U> std_03_allocator  (const std_03_allocator <U>&) noexcept {}

    T* allocate (std::size_t n)
    {
        std::cout<<"allocate:"<<n*sizeof(T)<<std::endl;
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n)
    {
        ::operator delete(p);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args) {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

    template< class U >
    struct rebind
    {
        typedef std_03_allocator<U> other;
    };
};

int factorial(int i)
{
    if (i==0)
        return 1;
    else
        return i*factorial(i-1);
}

void printMap(std::map<int, int, std::less<int>,
                        std_03_allocator<std::pair<int, int>>> &my_map2) {
    for (int i = 0; i < 10; i++)
        std::cout << i << " " << my_map2[i] << std::endl;
}

int main(/*int argc, char const *argv[]*/) {

     std::map<int,int> std_map;
     for (int i = 0; i<10; i++)
         std_map[i] = factorial(i);

     std::cout<<"step0"<<std::endl;

     std::map<int,int,std::less<int>,std_03_allocator<std::pair<int,int>>> my_map1;
     my_map1.get_allocator().allocate(10);
         for (int i = 0; i<10; i++)
     my_map1[i]= factorial(i);

     std::cout<<"step1"<<std::endl;

     std::map<int,int,std::less<int>,std_03_allocator<std::pair<int,int>>> my_map2;
     my_map2.get_allocator().allocate(10);
     for (int i = 0; i<10; i++)
         my_map2[i]= factorial(i);
    
     std::cout<<"step2"<<std::endl;

     printMap(my_map2);

    std::cout<<"step3"<<std::endl;

    my_vector<int> my_vector1;
    for (int i = 0; i<10; i++)
        my_vector1.push_back(i);
    
    std::cout<<"step4"<<std::endl;

    my_vector<int,std_03_allocator<int>> my_vector2;
    for (int i = 0; i<10; i++)
        my_vector2.push_back(i);

    std::cout<<"step5"<<std::endl;

    for (int i = 0; i<10; i++)
        std::cout<<my_vector2[i]<<std::endl;

    std::cout<<"stepEnd"<<std::endl;

    return 0;
}
