#include <gtest/gtest.h>
#include "../utest/utTerm.h"
#include "../utest/utVariable.h"
#include "../utest/utStruct.h"

int main(int argc , char **argv)
{
    testing :: InitGoogleTest(&argc , argv);
    return RUN_ALL_TESTS();
}
