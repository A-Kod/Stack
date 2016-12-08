#include "stack.hpp"
#include "catch.hpp"


SCENARIO("Check if pushi")
{
    GIVEN("stack and its size")
    {
        Stack<int> st;
        WHEN("push one element")
        {
            st.push(0);

            THEN("st.count == 1")
            {
                REQUIRE(st.count() == 1);
            }
        }
    }
}