#include "stack.hpp"

using namespace std;


int main()
{
    Stack <int> st;
    
    for (int i = 0; i < 10 ; ++i)
    {
        st.push(rand()%50 + 5);
    }
    
    std::cout << "Range of stack - " << st.count() << std::endl;
    st.print();
    
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
