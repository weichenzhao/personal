/* From http://www.cprogramming.com/tutorial/function-pointers.html
 * A test for function pointer
 */
#include <stdio.h>
void my_int_func(int x)
{
    printf( "%d\n", x );
}

int main()
{
    void (*foo)(int);
    /* the ampersand is actually optional */
    foo = &my_int_func;
    foo(1);

    return 0;
}
