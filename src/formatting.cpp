#include <initializer_list>
#include <vector>

namespace freyr
{
    namespace inner
    {

        /**
         *  Assuming struct and class works the same in vcformat
         */
        struct A
        {
            A()
                : x()
                , y()
                , z{}
            {
            }

        public:
            int x;

            void foo(int a, int b, int) const
            {
            }

        protected:
            int y;

            int bar(int, int c) const
            {
                return 0;
            }

        private:
            int z;
        };

        struct B: A
        {
        };

        struct C
            : A
            , B
        {
        };

        struct D: public A
        {
        };
    }
}

void foo(
    int this_is_a_very_long_name_____________________________,
    int where_should_this_variable_go,
    int how_about_this_variable
)
{
}

template <typename... T>
void bar___________________(T...)
{
}

int main(int argc, char const** argv)
{
    int x;
    switch (x)
    {
    case 1:
    {
        break;
    }
    default:
        break;
    }

    for (int x = 0; x < 10; ++x)
    {
        continue;
    }

    for (auto const& c : {1, 2, 3})
    {
        break;
    }

    while (false)
    {
    }

    do
    {
        foo(1, 2, 3);
    } while (false);

    if (false)
    {
    }

    std::vector<int> z{1, 2, 3, 4, 5};
    z[1];

    auto const l = []() { int p; };
    int q;

    bar___________________(
        1, []() { int z; }, []() { int z; }
    );

    try
    {
    }
    catch (...)
    {
    }

    return 0;
}
