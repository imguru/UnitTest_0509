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
//   => 암묵적 설치/해체
//     : 여러 테스트에서 같은 테스트 픽스쳐를 SetUp/TearDown 함수를 통해 설치한다.
//       xUnit Test Framework가 암묵적으로 호출해줍니다.
//   단점: 픽스쳐 설치 코드가 테스트 함수 밖에 있으므로, 테스트 함수만으로 인과 관계를 이해하기 어려울 수 있다.

// 4단계 테스트 패턴
//  : xUnit Test Pattern에서의 테스트를 구성하는 방법
//   1단계
//     테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업.
//   2단계
//     SUT와 상호작용한다.
//   3단계
//     기대 결과를 확인한다.
//   4단계
//     테스트 픽스쳐를 해체해서, 테스트 시작 상태로 돌려놓는다.
//     => 신선한 픽스쳐 전략.

class CalculatorTest : public ::testing::Test {
protected: // private은 사용할 수 없습니다.
	Calculator* create() {
		return new Calculator(0);
	}

	Calculator* calc;

	// SetUp 함수를 테스트 프레임워크가 암묵적으로 호출하기 때문에,
	// 픽스쳐 설치에 대한 코드를 SetUp을 통해 처리하면 된다.
	virtual void SetUp() override {
		printf("SetUp()\n");
		Calculator *calc = create();
	}

	// 픽스쳐를 해체하는 목적으로 사용합니다.
	// => 테스트 함수 수행 이전의 상태와 수행 이후의 상태가 동일하도록 해주어야 합니다.
	virtual void TearDown() {
		printf("TearDown()\n");
		delete calc;
	}
};

// TEST라는 매크로 말고, TEST_F라는 매크로로 테스트 함수를 구성해야 합니다.
TEST_F(CalculatorTest, plusTest) {
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
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST_F(CalculatorTest, pressPlus_AddingTwoPlusTwo_DisplaysFour) {
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display()) << "When adding 2 + 2";
}
