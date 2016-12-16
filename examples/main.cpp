#include <stdlib.h>

#include "stack.hpp"

class Element
{
   private:
   int x;

   public:
   Element (int _x = 0)
   {
       x = _x;
   }

   int get_x()
   {
       return x;
   }

    void set_x(int _x)
    {
        x = _x;
    }

};



using namespace std;


int main()
{
    Element e[10];
    Stack <Element> st_;
    Stack <int> st;


    for (int j = 0; j < 10 ; ++j)
    {
       e[j].set_x(j);
        st_.push(e[j]);
    }

    std::cout << "Range of stack of Elements - " << st_.count() << std::endl;


    for (int i = 0; i < 10 ; ++i)
    {
        st.push(rand()%50 + 5);
    }

    std::cout << "Range of stack - " << st.count() << std::endl;
    st.print();

    std:: cout << "Top of stack - " << st.top() << std::endl;
    
    st.pop();
    std::cout << "Stack after pop:" << std::endl;
    st.print();
    std::cout << "Range of stack - " << st.count() << std::endl;
    
    try
    {
        for (int i = 0; i < 10; ++i)
            st.pop();
    }
    
    catch (stack_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
