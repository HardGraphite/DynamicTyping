#include <dyntypes.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace DtLiterals;

    auto v0 = "hello, world"_s;
    auto v1 = 2.718281828459_f;
    auto v2 = Dt_newValue(true);

    std::cout
        << Dt_asStr(Dt_invokeMethod(v0, Dt_M_ToStr)) << '\t'
        << Dt_asStr(Dt_invokeMethod(v1, Dt_M_ToStr)) << '\t'
        << Dt_asStr(Dt_invokeMethod(v2, Dt_M_ToStr)) << '\n';

    DT_decRef(v0);
    DT_decRef(v1);
    DT_decRef(v2);

    return 0;
}
