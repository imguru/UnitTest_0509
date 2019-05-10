#include <unistd.h>
#include <stdio.h>
// 비기능 테스트
//  : 기능이 아닌, 성능 또는 메모리 등을 측정하는 테스트

// foo(): foo 함수는 반드시 2초 이내에 수행되어야 한다.
// 2초
void foo() {
	sleep(3);
}

// 5초
void goo() {
}

#include <time.h>
#include <gtest/gtest.h>

// SetUp() - 현재 시간 측정
// TearDown() - 시간 측정해서 SetUP하고 비교해서, 실패 여부를 확인한다.
#if 0
class TimeCriticalTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;
		EXPECT_TRUE(duration < 2) << "시간 초과: " << duration;
	}
};
#endif
template <typename T, int PIVOT>
class TimeCriticalTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;
		EXPECT_TRUE(duration < PIVOT) << "시간 초과: " << duration;
	}
};

// CRTP
class TimeTest2Sec : public TimeCriticalTest<2, TimeTest2Sec> {
};

class TimeTest3Sec : public TimeCriticalTest<2, TimeTest3Sec> {
};

TEST_F(TimeTest3Sec, fooTest) {
	foo();
}








