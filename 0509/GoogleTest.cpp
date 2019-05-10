
#include <gtest/gtest.h>

// 1. ASSERT_EQ/NE/GT/LT/GE/LE
//   주의할점
//    : 하나의 단언 매크로가 실패할 경우
//      이후의 코드는 수행하지 않는다.

// 하나의 테스트 함수 안에서는 하나의 단언문만 사용해야 한다.
//  => 테스트 함수가 너무 많아질 수 있다.

// 구글 테스트는 위의 단언 매크로가 실패하더라도, 계속 검증을 수행하는 매크로를 제공합니다.
//  => EXPECT_ 계열 매크로를 제공합니다. 
TEST(DISABLED_GoogleTestSample, example1) {
	int expected = 42;

	int actual1 = 10;
	int actual2 = 20;
	
	EXPECT_EQ(expected, actual1) << "이유 1";
	EXPECT_EQ(expected, actual2) << "이유 2";
#if 0
	ASSERT_EQ(expected, actual1) << "이유 1";
	ASSERT_EQ(expected, actual2) << "이유 2";
#endif
}

#include <string>

// 2. 문자열 비교를 위한 단언 매크로 
// C++ 에서 문자열을 표현하는 방법.
//   1) const char *
//     : ASSERT_STREQ / ASSERT_STRNE

//   2) std::string
//     : ASSERT_EQ / ASSERT_NE
TEST(DISABLED_GoogleTestSample, example2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	ASSERT_EQ(s1, s2) << "s1 == s2";
	// s1 == s2

	// C 언어의 문자열을 다룰 때, 포인터의 주소를 비교하는 것이 아니라,
	// 값을 비교해야 한다.
	const char* s3 = "hello";
	const char* s4 = s2.c_str();

	// ASSERT_EQ(s3, s4) << "s3 == s4";
	// : 포인터의 주소를 비교하므로 실패!

	ASSERT_STREQ(s3, s4) << "s3 == s4";
}

// 3. 부동 소수점 비교
//   : 오차가 있는 타입입니다.
//     절대 같은 값을 가질 수 없는 타입이다.
//    => 별도의 연산을 통해 비교를 수행해야 합니다.
TEST(DISABLED_GoogleTest, example3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// ASSERT_EQ(a, b) << "a == b";
	ASSERT_DOUBLE_EQ(a, b) << "a == b"; // 4ULP

	// 직접 오차 범위를 지정하고 싶을 때
	ASSERT_NEAR(a, b, 0.);
}

// 4. 예외 테스트
//  : SUT가 특정 상황에서 기대한 예외가 제대로 발생하는지 여부를 검증하는 작업.
void foo(const std::string& name) {
	//------ SUT BEGIN
	// return;
	// throw 1;
	if (name.empty()) {
		throw std::invalid_argument("name must not empty!");
	}
	//------ SUT END

	// ...
}

#if 0
// 단위 테스트 프레임워크가 예외 테스트를 지원하지 않는 경우.
test(DISABLED_GoogleTest, DISABLED_example4) {
	try {
		foo("");
		FAIL() << "예외가 발생하지 않음.";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였다.\n";
	}
}
#endif

// ./a.out --gtest_also_run_disabled_tests
//  : 비활성화된 테스트를 수행할 수 있습니다.
TEST(DISABLED_GoogleTest, DISABLED_example4) {
	// - 예외 타입을 명확하게 지정하고 싶을 때
	// ASSERT_THROW(foo(""), std::invalid_argument);
	
	// - 어떤 예외든 상관없을 때
	ASSERT_ANY_THROW(foo(""));
}

// Google Test에서 테스트를 비활성화하는 방법.
//  => 유지 보수의 대상이 되는 테스트를 주석으로 비활성화하면 안됩니다.
//  => 잊혀진 테스트가 될 수 있습니다.
//  => 테스트를 비활성화한 사실을 확인할 수 있어야 합니다.
//  => TestCase 이름 또는, Test 함수의 이름이 DISABLED_로 시작되면, 수행하지 않습니다.
