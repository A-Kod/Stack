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

    std::cout << "Range of stack of Elements - " << st_.count() << std::endl << st_.top().get_x() <<std::endl << std::endl;
    for (int i = 0; i < 10 ; ++i)
    {
        st.push(rand()%50 + 5);
        std::cout << st.top() << std::endl;
    }

    std::cout << "Range of stack - " << st.count() << std::endl;
    std:: cout << "Top of stack - " << st.top() << std::endl;
    st.pop();
    std::cout << "Range of stack - " << st.count() << std::endl;
    return 0;
}
