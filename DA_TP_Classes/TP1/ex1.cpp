// By: Gonçalo Leão

#include "exercises.h"

bool sum3(unsigned int T, unsigned int nums[3]) {
    //TODO...
    if (T <= 2) return false;
    for(int i = 1; i <= T - 2; i++){
        for(int j = 1; j <= T - i; j++){
            for(int k = 1; j <= T - j; k++){
                if(i+j+k == T){
                    nums[0] = i;
                    nums[1] = j;
                    nums[2] = k;
                    return true;
                }
            }
        }
    }
    return false;
}

bool sum3_a(unsigned int T, unsigned int nums[3]) {
    //TODO...
    if (T <= 2) return false;
    for(int i = 1; i <= T - 2; i++){
        for(int j = 1; j <= T - 2; j++){
            for(int k = 1; j <= T - 2; k++){
                if(i+j+k == T){
                    nums[0] = i;
                    nums[1] = j;
                    nums[2] = k;
                    return true;
                }
            }
        }
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

void compareSums(unsigned int selected[3], unsigned int expectedSum) {
    EXPECT_EQ(selected[0] + selected[1] + selected[2], expectedSum);
}

TEST(TP1_Ex1, 3sumExists) {
    unsigned int selected[3];

    unsigned int T = 10;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);

    T = 18;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
}

TEST(TP1_Ex1, 3sumNotExists) {
    unsigned int selected[3];

    unsigned int T = 1;
    EXPECT_EQ(sum3(T,selected), false);
}