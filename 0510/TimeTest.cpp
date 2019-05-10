#include <unistd.h>
#include <stdio.h>
// 비기능 테스트
//  : 기능이 아닌, 성능 또는 메모리 등을 측정하는 테스트

// foo(): foo 함수는 반드시 2초 이내에 수행되어야 한다.
// 2초
void foo() {
	sleep(2);
}

// 5초
void goo() {
}

#include <time.h>
#include <gtest/gtest.h>

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
// CRTP: 이상하게 반복되는 템플릿 패턴
template <typename T, int PIVOT>
class TimeCriticalTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		// gettimeofday
		// clock_gettime
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;
		EXPECT_TRUE(duration < PIVOT) << "시간 초과: " << duration;
	}
};

// CRTP
//  : 부모 클래스 타입이 템플릿인데, 
//    자신의 타입의 정보를 부모의 템플릿인자로 넘기는 형태의 설계 방식
class TimeTest2Sec : public TimeCriticalTest<TimeTest2Sec, 2> {
};

class TimeTest3Sec : public TimeCriticalTest<TimeTest3Sec, 3> {
};

TEST_F(TimeTest3Sec, fooTest) {
	foo();
}

TEST_F(TimeTest2Sec, fooTest) {
	foo();
}








