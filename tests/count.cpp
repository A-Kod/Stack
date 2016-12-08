#include "stack.hpp"
#include "catch.hpp"


SCENARIO("st.count in case of empty stack")
{
    GIVEN("empty stack")
    {
        Stack<int> st;

        WHEN("")
        {
            THEN("st.count == 0")
            {
                REQUIRE(st.count() == 0);
            }
        }
    }
}

SCENARIO("st.count in case of non-empty stack")
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
            THEN("st.count() != 0")
            {
                REQUIRE(st.count() != 0);
            }
        }
    }
}