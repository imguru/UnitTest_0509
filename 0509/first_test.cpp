// 구글 테스트를 사용할 때 반드시 포함해야 하는 헤더파일 입니다.
// g++ first_test.cpp gtest.a -I. -o first_test -pthread

// * 구글 테스트 라이브러리는 반드시 정적 라이브러리를 사용하는 것이 좋습니다.
// * 패키지 매니저를 통해서 설치하는 것 보다는, 직접 소스를 다운 받아서 설치하는 것이 좋습니다.

#include <gtest/gtest.h>
#include <stdio.h>

// 3. 구글 테스트에서 테스트 함수를 만드는 방법.
//  TEST(TestCase 이름, Test 이름)

// 절대 실패하지 않는 테스트입니다.
//  : 테스트 코드를 작성 중이면, 반드시 실패해야 합니다.
//  => 명시적으로 실패하는 방법.

//  : 테스트가 실패한 경우, 실패의 이유를 테스트 결과창을 통해 알 수 있어야 합니다.
//  => 단언 함수나 FAIL 함수를 사용할 때, 실패의 이유를 명시해야 합니다.
TEST(FirstTest, foo) {
	FAIL() << "코드를 작성 중입니다.";
}

TEST(FirstTest, goo) {
	printf("goo\n");
}

// 아래 코드는 테스트를 수행하기 위해서, 프로그램의 시작 시점에 무엇인가 초기화해야 하는 것이 아니라면
// 변하지 않습니다.
//  => 직접 작성하기 보다는, 구글 테스트가 제공하는 main이 있습니다.
#if 0
// 구글 테스트에서 메인을 직접 작성해야 합니다.
int main(int argc, char **argv) {
	// 1. 구글 테스트 프레임워크 초기화 코드
	testing::InitGoogleTest(&argc, argv);
	
	// 2. 모든 단위 테스트를 수행합니다.
	return RUN_ALL_TESTS();
}
#endif
















