#include <dyntypes.h>
#include <stdio.h>

#define TO_STRING(X) Dt_asStr(DT_invokeMethod0(X, Dt_M_ToStr))

int main(int argc, char const *argv[])
{
    Dt_ValuePtr b0 = Dt_newBool(true), b1 = Dt_newBool(false);
    Dt_ValuePtr i0 = Dt_newInt(1), i1 = Dt_newInt(1000);
    Dt_ValuePtr f0 = Dt_newFloat(0), f1 = Dt_newFloat(3.14159265);
    Dt_ValuePtr s0 = Dt_newStr("hello"), s1 = Dt_newStr(NULL);
    Dt_ValuePtr l0 = Dt_newList(4, b1, i1, f1, s0, NULL);
    Dt_ValuePtr v0 = Dt_newValue(-15);

    printf("%s: %s - %s\n%s: %s - %s\n%s: %s - %s\n%s: '%s' - '%s'\n%s: %s\n%s: %s\n",
        DT_TypeNameOf(b0), TO_STRING(b0), TO_STRING(b1),
        DT_TypeNameOf(i0), TO_STRING(i0), TO_STRING(i1),
        DT_TypeNameOf(f0), TO_STRING(f0), TO_STRING(f1),
        DT_TypeNameOf(s0), TO_STRING(s0), TO_STRING(s1),
        DT_TypeNameOf(l0), TO_STRING(l0),
        DT_TypeNameOf(v0), TO_STRING(v0)
    );

    printf("%i - %i = %i\n", Dt_asInt(i0), Dt_asInt(i1), Dt_asInt(DT_Add(i0, i1)));
    printf("%s * %i = %s\n", Dt_asStr(s0), 3, Dt_asStr(DT_Mul(s0, Dt_newInt(3))));
    printf("[...] << Nil = %s\n", TO_STRING(DT_Shl(l0, Dt_Nil)));

    DT_decRef(b0);
    DT_decRef(b1);
    DT_decRef(i0);
    DT_decRef(i1);
    DT_decRef(f0);
    DT_decRef(f1);
    DT_decRef(s0);
    DT_decRef(s1);
    DT_decRef(l0);
    DT_decRef(v0);

    return 0;
}
