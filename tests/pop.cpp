#include "stack.hpp"
#include "catch.hpp"

SCENARIO("pop one element from stack with one elem")
{
    GIVEN("empty stack)
    {
        Stack<int> st;
        st.push(0);
        WHEN("pop")
        {
            st.pop();
            THEN("st.count == 0")
            {
                REQUIRE(st.count() == 0);
            }
        }
    }
}
