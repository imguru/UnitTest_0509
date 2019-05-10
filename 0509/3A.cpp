// SUT(System Under Test) : 테스트 대상 시스템
//  => CUT(Class Under Test or Code Under Test)

class Calculator {
public:
	double display() { return 0; }

	void enter(double value) {}
	void pressPlus() {}
	void pressMinuss() {}
	void pressEqual() {}
};

// g++ 3A.cpp gtest.a -I. -pthread
// 3A.cpp
// : 단위 테스트를 구성하는 방법.

// 1. Arrange: 객체를 생성하거나, 적절하게 설정하고 준비하는 과정
// 2. Act: 객체에 작용을 가한다. 
// 3. Assert: 객체의 상태에 대해서 기대하는 바를 단언한다.


#include <gtest/gtest.h> // !!

// SUT: Calculator
// TestCase Name: CalculatorTest(Spec)
// Test Name: plusTest
TEST(CalculatorTest, plusTest) {
	// Arrange
	Calculator *calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	if (calc->display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
}


// TDD(테스트 주도 개발)
//   3A

// BDD(행위 주도 개발)
//   1) 용어
//   2) 테스트 대역

// * 단위 테스트를 검증하는 테스트 코드는 존재하지 않습니다.
//  => 검증이 필요하지 않도록, 최대한 간결하게 작성해야 합니다.
//  => 테스트 코드 안에서는 절대 제어 구문을 사용하면 안됩니다.
//                              (조건문, 반복문, 예외처리)

// 테스트 코드 품질
// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성
TEST(CalculatorTest, plusTest2) {
	// Arrange -> Given
	Calculator *calc = new Calculator;

	// Act     -> When
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert -> Then
	// 아래의 코드를 별도의 유틸리티 함수를 통해 제공하고 있습니다.
	//  => 단언 함수
	//   : 구글 테스트는 함수가 아닌 매크로의 형식으로 제공하고 있습니다.
	//     ASSERT_EQ/GT/LT/GE/LE
	// ASSERT_EQ(calc->display(), 4); - X
	// 위의 함수를 사용할 때는 주의할 점이 있습니다.
	//  => 인자의 순서를 정확하게 사용해야 합니다.
	//     ASSERT_EQ(기대값, 실제값)

	ASSERT_EQ(4, calc->display());
#if 0
	if (calc->display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
#endif
}

// 위 함수의 문제점
//  : 실패하였을 때, 해당 테스트의 결과에 대해서 코드를 보지 않고는 알 수 없다.
//  => 자체 검사 테스트
//    : 코드를 보지 않아도, 테스트의 실패 원인을 알 수 있어야 한다.
//      1) 테스트 함수의 이름을 설명적으로 작성해야 한다.
//        => ex) 테스트대상함수_시나리오_기대값

//      2) 단언함수의 실패 메세지를 명확하게 작성해야 한다.
TEST(CalculatorTest, pressPlus_AddingTwoPlusTwo_DisplaysFour) {
	// Arrange -> Given
	Calculator *calc = new Calculator;

	// Act     -> When
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert -> Then
	// 아래의 코드를 별도의 유틸리티 함수를 통해 제공하고 있습니다.
	//  => 단언 함수
	//   : 구글 테스트는 함수가 아닌 매크로의 형식으로 제공하고 있습니다.
	//     ASSERT_EQ/GT/LT/GE/LE
	// ASSERT_EQ(calc->display(), 4); - X
	// 위의 함수를 사용할 때는 주의할 점이 있습니다.
	//  => 인자의 순서를 정확하게 사용해야 합니다.
	//     ASSERT_EQ(기대값, 실제값)

	ASSERT_EQ(4, calc->display()) << "When adding 2 + 2";
#if 0
	if (calc->display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
#endif
}






















