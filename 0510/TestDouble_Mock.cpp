#include <stdio.h>
#include <string>
#include <vector>

enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

class DLog {
	std::vector<DLogTarget*> targets;
public:
	void AddTarget(DLogTarget* p) { targets.push_back(p); }

	void Write(DLogLevel level, const std::string& message) {
		for (DLogTarget* e : targets) {
			// e->Write(level, message);
		}
	}
};

//------------------------
// Mock Object Pattern
//  : 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서, 테스트 안된 요구사항이 있다.
//  => 행위 검증을 통해 검증한다.

// 테스트 코드를 작성하는 방식이 다릅니다.
//   => ASSERT(EXPECT): 상태 검증
//      ; 함수를 호출하였을 때, 값이 변경이 발생해야 한다.

//   => 행위 검증
//     ; 함수를 호출하였을 때, 협력 객체에 대해서, 어떤 함수가 호출될지, 검증하는 방법.
//      1. 호출된 함수
//      2. 호출된 함수 횟수
//      3. 호출된 함수의 순서
//      : Mock Framework를 이용해야 합니다.
//       => Google Mock
#if 0
$ g++ gmock-gtest-all.cc -c -I.
$ ar rcv gmock.a gmock-gtest-all.o
$ g++ ~/chansik.yun/googletest/googlemock/src/gmock_main.cc -c -I.
$ ar rcv gmock.a gmock_main.o
$ g++ TestDouble_Mock.cpp gmock.a -I. -pthread

#endif
#include <gtest/gtest.h>
#include <gmock/gmock.h> // !!!

// Java's Mock Framework은 동적으로 테스트 대역을 생성할 수 있습니다.
//  => C++은 불가능합니다.
//  => Mock을 작성해야 합니다.
//     : 매크로

// int n;

// virtual void Write(DLogLevel level, const std::string& message) = 0;
class DLogTargetMock : public DLogTarget {
public:
	// MOCK_METHOD{인자개수}(함수의 이름, 함수의 타입)
	MOCK_METHOD2(Write, void(DLogLevel, const std::string&));
};

// 내가 등록한 협력 객체에 대해서 Write가 호출될 것이다.
TEST(DLogTest, WriteTest) {
	// Arrange
	DLogTargetMock mock1, mock2;
	DLogLevel level = INFO;
	std::string message = "test_message";

	DLog log;
	log.AddTarget(&mock1);
	log.AddTarget(&mock2);

	// Assert
	EXPECT_CALL(mock1, Write(level, message));
	EXPECT_CALL(mock2, Write(level, message));

	// Act
	log.Write(level, message);
	// Mock 객체가 파괴되는 시점에, 예측과 다르면, 예외가 발생하고, 테스트가 실패합니다.
}

// 테스트 대역 목적
//  1) 비결정적 요소를 제어
//      "시간", "네트워크", "파일 시스템"
//  2) 만들어지지 않은 모듈에 의존하는 객체를 검증.
//  3) 협력 객체가 너무 느려서 느린 테스트 문제가 발생.
//  4) 숨겨진 정보를 확인하거나, 테스트를 위한 정보를 기록하는 목적.
//  5) 행위 기반 검증

// 테스트 대역 종류
//  1) Stub - *
//  2) Fake
//  3) Spy
//  4) Mock - *

















