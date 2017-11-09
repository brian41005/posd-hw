#include <gtest/gtest.h>
#include "../utest/utList.h"
#include "../utest/utStruct.h"
#include "../utest/utTerm.h"
#include "../utest/utVariable.h"
#include "../utest/utParser.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
