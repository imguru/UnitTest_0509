class Calculator {
public:
	Calculator(int n) {}

	double display() { return 4; }

	void enter(double value) {}
	void pressPlus() {}
	void pressMinuss() {}
	void pressEqual() {}
};

#include <gtest/gtest.h> 
//   => 위임 설치
//    1) 동일한 픽스쳐를 가지는 테스트 함수를 동일한 테스트 케이스 클래스로 묶는다.
//    2) 픽스쳐 설치에 관해 중복되는 코드를 함수로 묶는다.

// Google Test를 이용해서 테스트 케이스 클래스를 만드는 방법.
class CalculatorTest : public ::testing::Test {
protected: // private은 사용할 수 없습니다.
	Calculator* create() {
		return new Calculator(0);
	}
};

// TEST라는 매크로 말고, TEST_F라는 매크로로 테스트 함수를 구성해야 합니다.
TEST_F(CalculatorTest, plusTest) {
	Calculator *calc = create();

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	if (calc->display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
}

TEST_F(CalculatorTest, plusTest2) {
	Calculator *calc = create();

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST_F(CalculatorTest, pressPlus_AddingTwoPlusTwo_DisplaysFour) {
	Calculator *calc = create();

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display()) << "When adding 2 + 2";
}
