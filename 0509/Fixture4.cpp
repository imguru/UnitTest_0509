#include <gtest/gtest.h> 

// => NUnit
// CalculatorTest()
//   SetUp()
//     foo()
//   TearDown()
//   SetUp()
//     goo()
//   TearDown()

// => 신선한 픽스쳐 전략
// => xUnit Test Framework은 아래와 같이 동작합니다.
// CalculatorTest()
//   SetUp()
//     foo()
//   TearDown()
// CalculatorTest()
//   SetUp()
//     goo()
//   TearDown()

class CalculatorTest : public ::testing::Test {
protected: 
	CalculatorTest() { 
		printf("CalculatorTest()\n");
	}

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(CalculatorTest, foo) {
	printf("  foo\n");
}

TEST_F(CalculatorTest, goo) {
	printf("  goo\n");
}

