
// Google Test에서 제공하는 고유한 기능.
//  => C/C++ 테스트 목적으로 사용합니다.

//  => 프로세스 단위의 초기화/정리 작업이 필요할 때 사용할 수 있습니다.
// Program 시작 - SetUp
//  TestCase::SetUpTestCase()
//  TestCase()
//   SetUp()
//   Body()
//   TearDown()
//  TestCase()
//   SetUp()
//   Body()
//   TearDown()
//   ...
//  TestCase::TearDownTestCase()

//  TestCase::SetUpTestCase()
//  TestCase()
//   SetUp()
//   Body()
//   TearDown()
//  TestCase()
//   SetUp()
//   Body()
//   TearDown()
//   ...
//  TestCase::TearDownTestCase()
// Program 종료 - TearDown

#include <stdio.h>
#include <gtest/gtest.h>

class MyTestEnvironment : public ::testing::Environment {
public:
	virtual void SetUp() override {
		printf("Global SetUp()\n");
	}

	virtual void TearDown() override {
		printf("Global TearDown()\n");
	}
};

// Global Fixture 를 설치하는 방법은 2가지
//  1) main을 직접 작성하지 않는 경우.
//    : 전역 변수
#if 0
::testing::Environment *const env = ::testing::AddGlobalTestEnvironment(new MyTestEnvironment); 
#endif

class MyTest1 : public ::testing::Test {};

TEST_F(MyTest1, foo) {}
TEST(MyTest2, foo) {}
TEST(MyTest3, foo) {}
TEST(MyTest4, foo) {}

//  2) main을 직접 작성하는 경우.
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	
	::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

	return RUN_ALL_TESTS();
}
















