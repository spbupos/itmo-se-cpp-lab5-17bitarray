#include <lib/3DArray.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(Array3DTests, GetSet) {
    Array3D array(3, 3, 3);
    auto a = array.at(0, 0, 0);
    a = 1;
    array.at(0, 0, 1) = 2;
    array.at(2, 0, 0) = 228;
    array.at(2, 2, 2) = 1337;
    auto b = array.at(2, 0, 0);

    EXPECT_EQ(array.at(0, 0, 0), 1);
    EXPECT_EQ(array.at(0, 0, 1), 2);
    EXPECT_EQ(b, 228);
    EXPECT_EQ(array.at(2, 2, 2), 1337);
}

TEST(Array3DTests, GetSetBig) {
    Array3D array(100, 100, 100);
    array.at(0, 0, 0) = 1;
    array.at(10, 10, 10) = 2;
    array.at(99, 99, 99) = 3;

    EXPECT_EQ(array.at(0, 0, 1), 0);
    EXPECT_THROW(array.at(101, 102, 103), std::out_of_range);
    EXPECT_THROW(array.at(-1, -1, -1), std::out_of_range);
}

TEST(Array3DTests, BadDeclaration) {
    EXPECT_THROW(Array3D array(5, 6, 0), std::invalid_argument);
    EXPECT_THROW(Array3D array(2, -1, 3), std::invalid_argument);
    EXPECT_THROW(Array3D array(10000, 10000, 10000), std::out_of_range);
    /*
     * WARNING: if some of the coordinates will be bigger than 2^31 - 1, or it's
     * product will be bigger than 2^64 - 1, it's possible stack overflow, and
     * sometimes won't throw anything, but it's not a problem of this class
     */
}

TEST(Array3DTests, StaticDeclaration) {
    auto array = Array3D::newArray3D(3, 3, 3);
    array.at(0, 0, 0) = 1;
    EXPECT_EQ(array.at(0, 0, 0), 1);
    EXPECT_EQ(array.at(2, 0, 1), 0);
}

TEST(Array3DTests, OutputToSstreamTest) {
    auto array = Array3D::newArray3D(3, 5, 3);
    array.at(0, 0, 0) = 1;
    array.at(0, 0, 1) = 2;
    array.at(2, 0, 0) = 228;
    array.at(0, 4, 0) = 1337;

    EXPECT_EQ(array.at(0, 0, 0), 1);
    EXPECT_EQ(array.at(0, 0, 2), 0);
    EXPECT_EQ(array.at(0, 4, 0), 1337);

    std::stringstream ss;
    ss << array;
    EXPECT_EQ(ss.str(), "Array3D(3, 5, 3)\n"
                        "z = 0\n"
                        "1, 0, 228\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "1337, 0, 0\n"
                        "z = 1\n"
                        "2, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "z = 2\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n"
                        "0, 0, 0\n");
}

TEST(Array3DTests, InputFromSstreamTest) {
    Array3D array(2, 2, 2);

    std::string input = "1 2 3 4 5 6 7 8";
    std::stringstream os(input);
    os >> array;

    EXPECT_EQ(array.at(0, 0, 0), 1);
    EXPECT_EQ(array.at(1, 0, 0), 2);
    EXPECT_EQ(array.at(1, 1, 1), 8);
}

TEST(Array3DTests, MultiplicationTest) {
    Array3D array(2, 2, 2);

    std::string input = "1 2 3 4 5 6 7 8";
    std::stringstream os(input);
    os >> array;

    auto arr2 = array * 2;
    EXPECT_EQ(arr2.at(0, 0, 0), 2);
    EXPECT_EQ(arr2.at(1, 1, 1), 16);

    auto arr25 = array * 2.5;
    EXPECT_EQ(arr25.at(0, 0, 0), 2);
    EXPECT_EQ(arr25.at(0, 1, 0), 7);
    EXPECT_EQ(arr25.at(0, 1, 1), 17);
    EXPECT_EQ(arr25.at(1, 1, 1), 20);

    auto arr0 = array * 0;
    EXPECT_EQ(arr0.at(0, 0, 0), 0);
    EXPECT_EQ(arr0.at(1, 1, 1), 0);

    EXPECT_THROW(array * -1, std::invalid_argument);
}

TEST(Array3DTests, PlusMinusTest) {
    Array3D array1(2, 2, 2);
    std::stringstream("8 7 6 5 5 6 7 8") >> array1;

    Array3D array2(2, 2, 2);
    std::stringstream("131071 131071 131071 131071 131071 131071 131071 131071") >> array2;

    Array3D array3(2, 2, 2);
    std::stringstream("5 5 5 5 5 5 5 5") >> array3;

    Array3D array4(2, 2, 1);
    std::stringstream("1 2 3 4") >> array4;

    auto res1 = array1 + array3;
    EXPECT_EQ(res1.at(0, 0, 0), 13);
    EXPECT_EQ(res1.at(1, 1, 1), 13);
    EXPECT_EQ(res1.at(1, 1, 0), 10);

    auto res2 = array1 - array3;
    EXPECT_EQ(res2.at(0, 0, 0), 3);
    EXPECT_EQ(res2.at(1, 1, 1), 3);
    EXPECT_EQ(res2.at(1, 1, 0), 0);

    EXPECT_THROW(array1 + array2, std::out_of_range);
    EXPECT_THROW(array3 - array1, std::out_of_range);
    EXPECT_THROW(array1 + array4, std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
