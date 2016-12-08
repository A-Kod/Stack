#include "stack.hpp"
#include "catch.hpp"


SCENARIO("empty must return true")
{
    GIVEN("empty stack")
    {
        Stack<int> st;

        WHEN("")
        {
            THEN("st.empty() == true")
            {
                REQUIRE(st.empty());
            }
        }
    }
}

SCENARIO("empty must return false")
{
    GIVEN("non-empty stack")
    {
        Stack<int> st;
        for (int i = 0; i < 10 ; ++i)
        {
            st.push(rand()%50 + 5);
        }

        WHEN("")
        {
            THEN("st.empty() == false")
            {
                REQUIRE_FALSE(st.empty());
            }
        }
    }
}