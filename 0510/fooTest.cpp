#include <gtest/gtest.h>
#include <stdio.h>

// static 함수를 테스트에서 확인해볼 수 없을까?
#include "foo.c"

TEST(FooTest, add) {
	printf("%d\n", add(10, 32));
}
