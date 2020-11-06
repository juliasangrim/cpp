#include <gtest/gtest.h>
#include "tritSet.h"

TEST (CapacityTests, StandartValues) {

    TritSet set1(1);
    ASSERT_GE(set1.getCapacity(), 1/ 4 / sizeof(size_t));

    TritSet set2(1000);
    ASSERT_GE(set2.getCapacity(), 1000/ 4 / sizeof(size_t));

    TritSet set3(UINT32_MAX);
    ASSERT_GE(set3.getCapacity(), UINT32_MAX/ 4 / sizeof(size_t));
}

TEST (CapacityTests, ZeroValues) {
    TritSet set1(0);
    ASSERT_EQ(set1.getCapacity(), 0);
}

TEST (SizeTest, StandartValues) {
    TritSet set1(1);
    ASSERT_EQ(set1.getSize(), 1);

    TritSet set2(1000);
    ASSERT_EQ(set2.getSize(), 1000);

    TritSet set3(UINT32_MAX);
    ASSERT_EQ(set3.getSize(), UINT32_MAX);
}

TEST (SizeTest, ZeroValues) {
    TritSet set1(0);
    ASSERT_EQ(set1.getSize(), 0);
}

TEST (SquareBracketsTest, GetValue) {
    TritSet set1(10000, F);
    TritSet set2(10000, T);
    TritSet set3(10000, U);
    for (int i = 0; i < 10000; i++) {
        ASSERT_EQ(static_cast<Trit>(set1[i]), F);
        ASSERT_EQ(static_cast<Trit>(set2[i]), T);
        ASSERT_EQ(static_cast<Trit>(set3[i]), U);
    }
}
TEST (SquareBracketsTest, SetValue) {
    TritSet set(150);
    for (int i = 0; i < 100; i++) {
        if (i < 50) {
            set[i] = T;
        }
        else if (i < 100) {
                set[i] = F;
            }
    }
    for (int i = 0; i < 100; i++) {
        if (i < 50) {
            ASSERT_EQ(static_cast<Trit>(set[i]), T);
        }
        else if (i < 100) {
            ASSERT_EQ(static_cast<Trit>(set[i]), F);
        }
        else {
            ASSERT_EQ(static_cast<Trit>(set[i]), U);
        }
    }
}

TEST (SetAssignmen, EqualitySizeTest) {
    TritSet set1(100, T);
    TritSet set2(50, F);
    TritSet setResult1(100);
    TritSet setResult2(50);
    setResult1 = set1;
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(static_cast<Trit>(setResult1[i]), T);
    }
    setResult1 = set2;
    for (int i = 0; i < 50; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult1[i]), F);
    }
    setResult2 = set1;
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult2[i]), T);
    }
}


TEST (AndTest, SmallTest) {
    TritSet set1(1, T);
    TritSet set2(1, F);
    TritSet set3(1, U);
    ASSERT_EQ(static_cast<Trit>((set1 & set1)[0]), T);
    ASSERT_EQ(static_cast<Trit>((set2 & set2)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set3 & set3)[0]), U);
    ASSERT_EQ(static_cast<Trit>((set2 & set3)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set3 & set2)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set1 & set2)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set2 & set1)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set1 & set3)[0]), U);
    ASSERT_EQ(static_cast<Trit>((set3 & set1)[0]), U);
}

TEST (AndTest, BigCapacityTest) {
    TritSet setT(100, T);
    TritSet setF(50, F);
    TritSet setResult1(50);
    TritSet setResult2(100);
    setResult1 = setT & setF;
    for (int i = 0; i < 100; i++) {
        if (i < 50) {
            ASSERT_EQ(static_cast<Trit>(setResult1[i]), F);
        }
        else {
            ASSERT_EQ(static_cast<Trit>(setResult1[i]), U);
        }
    }
    setResult2 = setT & setF;
    for (int i = 0; i < 100; i++) {
        if (i < 50) {
            ASSERT_EQ(static_cast<Trit>(setResult2[i]), F);
        }
        else {
            ASSERT_EQ(static_cast<Trit>(setResult2[i]), U);
        }
    }
}

TEST (OrTest, SmallTest) {
    TritSet set1(1, T);
    TritSet set2(1, F);
    TritSet set3(1, U);
    ASSERT_EQ(static_cast<Trit>((set1 | set1)[0]), T);
    ASSERT_EQ(static_cast<Trit>((set2 | set2)[0]), F);
    ASSERT_EQ(static_cast<Trit>((set3 | set3)[0]), U);
    ASSERT_EQ(static_cast<Trit>((set2 | set3)[0]), U);
    ASSERT_EQ(static_cast<Trit>((set3 | set2)[0]), U);
    ASSERT_EQ(static_cast<Trit>((set1 | set2)[0]), T);
    ASSERT_EQ(static_cast<Trit>((set2 | set1)[0]), T);
    ASSERT_EQ(static_cast<Trit>((set1 | set3)[0]), T);
    ASSERT_EQ(static_cast<Trit>((set3 | set1)[0]), T);
}
TEST (OrTest, BigCapacityTest) {
    TritSet setT(100, T);
    TritSet setF(50, F);
    TritSet setResult1(50);
    TritSet setResult2(100);
    setResult1 = setT | setF;
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult1[i]), T);
    }
    setResult2 = setT | setF;
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult2[i]), T);
    }
}

TEST (NegativeTest, SmallTest) {
    TritSet setT(1, T);
    TritSet setF(1, F);
    TritSet setU(1, U);
    ASSERT_EQ(static_cast<Trit>((~setT)[0]), F);
    ASSERT_EQ(static_cast<Trit>((~setF)[0]), T);
    ASSERT_EQ(static_cast<Trit>((~setU)[0]), U);
}

TEST (NegativeTest, BigCapacityTest) {
    TritSet setT(100, T);
    TritSet setF(50, F);
    TritSet setResult1(50);
    TritSet setResult2(100);
    setResult1 = ~setT;
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult1[i]), F);
    }
    setResult2 = ~setF;
    for (int i = 0; i < 50; i++) {
        ASSERT_EQ(static_cast<Trit>(setResult2[i]), T);
    }
}

TEST (ShrinkTest, SmallTest) {
    TritSet setT(1, T);
    TritSet setU(2, U);
    setU = setT;
    setU.shrink();
    ASSERT_EQ(static_cast<Trit>(setU[0]), T);
    ASSERT_EQ(setU.getSize(), 1);
    TritSet setU2(10, U);
    setU2.shrink();
    ASSERT_EQ(setU2.getCapacity(), 0);
}

TEST (ShrinkTest, BigCapacityTest) {
    TritSet setT(100, T);
    TritSet setU(2, U);
}