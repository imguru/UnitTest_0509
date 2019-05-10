class Calculator {
public:
	Calculator(int n) {}

	double display() { return 0; }

	void enter(double value) {}
	void pressPlus() {}
	void pressMinuss() {}
	void pressEqual() {}
};

// DRY(Don't Repeat Yourself)
//  : 중복하지 말라.
//  => 테스트 코드도 동일합니다.

// Fixture
//  정의: xUnit Test Pattern 에서는 SUT를 실행하기 위해 준비해야 하는 모든 과정을 테스트 픽스쳐라고 부릅니다.
//      => 픽스쳐를 구성하는 모든 로직 부분을 '픽스쳐를 설치한다(Fixture Setup)' 라고 합니다.

// 픽스쳐를 설치 하는 방법 3가지.
//  1. 인라인 픽스쳐 설치
//    : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//    장점
//     - 픽스쳐 설치와 검증 로직이 테스트 함수 안에서 존재하기 때문에, 인과 관계를 쉽게 파악할 수 있다.
//    단점
//    - 모든 테스트 함수 안에서 '중복'이 발생한다.

// 리팩토링
//  : 기능을 변경을 하지 않고, 코드의 구조를 개선하는 작업.
// 코드 냄새(Code smells)
//  : 코드의 유지보수성 떨어뜨리는 것

// 테스트 냄새(Test smells)
//  => 코드 중복
//    1) 픽스쳐 설치의 방법이 변경되면, 픽스쳐가 동일한 모든 테스트 함수가 깨진다.
//    2) 픽스쳐 설치의 과정이 복잡해지면, 테스트 함수를 이해하기 어렵게 만들 수 있다.
#include <gtest/gtest.h> 

// 프레임워크의 도움이 없이
//   => 위임 설치
//    1) 동일한 픽스쳐를 가지는 테스트 함수를 동일한 테스트 케이스 클래스로 묶는다.
//    2) 픽스쳐 설치에 관해 중복되는 코드를 함수로 묶는다.

// 프레임워크의 도움을 통해
//  => 암묵적 설치



TEST(CalculatorTest, plusTest) {
	Calculator *calc = new Calculator;

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

TEST(CalculatorTest, plusTest2) {
	Calculator *calc = new Calculator;

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display());
}

TEST(CalculatorTest, pressPlus_AddingTwoPlusTwo_DisplaysFour) {
	Calculator *calc = new Calculator;

	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	ASSERT_EQ(4, calc->display()) << "When adding 2 + 2";
}
