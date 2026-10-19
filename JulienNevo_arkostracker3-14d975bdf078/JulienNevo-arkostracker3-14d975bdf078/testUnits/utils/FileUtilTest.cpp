#include "../catch.hpp"

#include "../../source/utils/FileUtil.h"

namespace arkostracker
{

TEST_CASE("getFileWithoutCopyIndex, unmodified", "[FileUtil]")
{
    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test.aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (.aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test ).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test ).aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (-1).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (-1).aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1)b.aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (1)b.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1 3).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (1 3).aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test ().aks")) ==
        FileUtil::getFileFromString("/home/stuff/test ().aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (xxx).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (xxx).aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (a1).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (a1).aks")));
}

TEST_CASE("getFileWithoutCopyIndex, modified", "[FileUtil]")
{
    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1)  .aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1 ).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (10).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (01).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test    (0).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test.aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1) (10).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (1).aks")));

    REQUIRE((FileUtil::getFileWithoutCopyIndex(
        FileUtil::getFileFromString("/home/stuff/test (1) (4).aks")) ==
        FileUtil::getFileFromString("/home/stuff/test (1).aks")));
}

}   // namespace arkostracker
