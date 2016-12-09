#include "stack.hpp"
#include "catch.hpp"

SCENARIO("pop one element from stack with one elem")
{
    GIVEN("stack with one elem")
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


SCENARIO("pop from empty stack")
{
    GIVEN("empty stack")
    {
        Stack<int> st;
        WHEN("pop")
        {
            THEN("pop must throw exception")
            {
                REQUIRE_THROWS_AS(st.pop(), std::logic_error);
            }
        }
    }
}
