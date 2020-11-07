#include <dyntypes.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    auto v0 = Dt_newValue("hello, world");
    auto v1 = Dt_newValue(2.718281828459);

    std::cout
        << Dt_asStr(Dt_invokeMethod(v0, Dt_M_ToStr)) << '\t'
        << Dt_asStr(Dt_invokeMethod(v1, Dt_M_ToStr)) << '\n';

    DT_decRef(v0);
    DT_decRef(v1);

    return 0;
}
