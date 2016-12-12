#include "stack.hpp"
#include "catch.hpp"

SCENARIO("top one element from stack with one elem")
{
    GIVEN("stack with one elem")
    {
        Stack<int> st;
        st.push(0);
        WHEN("top")
        {
            THEN("st.top() == 0")
            {
              REQUIRE(st.top() == 0);
            }
        }
    }
}
