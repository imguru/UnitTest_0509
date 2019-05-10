
// Parameterized Test
//  : 파라미터화 테스트
// => 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심 테스트의 코드 중복을 없애주는 기술.

bool isPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

// xUnit Test Pattern에서 말하는 파라미터화 테스트의 문제점
// 1) 테스트의 이름에서 어떤 데이터인지 드러나지 않는다.
// 2) 테스트의 파라미터화 값에 대한 형식을 원하는 형태로 출력하기 힘들다.
//  => 테스트의 가독성이 떨어질 수 있다.
//     테스트 코드의 복잡도가 올라갈 수 있다.


#include <gtest/gtest.h>
// xUnit Test Framework이 지원하는 기능을 이용해서, 데이터 중심 테스트를 수행해보자.
// class PrimeTest: public ::testing::Test {

// 1. ::testing::TestWithParam<데이터 타입> 자식 클래스 => 테스트 케이스 클래스
class PrimeTest: public ::testing::TestWithParam<int> {
};

// 2. 데이터를 정의하는 방법
int data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 41, 11, 20, 40, 60 };
INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest, ::testing::ValuesIn(data));

// 3. 테스트 함수를 추가하면 됩니다.
TEST_P(PrimeTest, isPrime) {
	EXPECT_TRUE(isPrime(GetParam()));
}

TEST_P(PrimeTest, isPrime2) {
	EXPECT_TRUE(isPrime(GetParam()));
}

#if 0
TEST(PrimeTest, isPrime) {
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(3));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
	EXPECT_TRUE(isPrime(41));
	EXPECT_TRUE(isPrime(11));
}
#endif



















