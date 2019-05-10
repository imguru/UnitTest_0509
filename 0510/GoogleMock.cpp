#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct User {
	virtual ~User() {}

	virtual void Stop() = 0;
	virtual void Say(const std::string& message) = 0;
	virtual void Attack(User *target) = 0;
	virtual void Move(int x, int y) = 0;
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
};

// $ ./gmock_gen.py ~/chansik.yun/0510/User2.h
class MockUser : public User {
 public:
  MOCK_METHOD0(Stop,
      void());
  MOCK_METHOD1(Say,
      void(const std::string& message));
  MOCK_METHOD1(Attack,
      void(User *target));
  MOCK_METHOD2(Move,
      void(int x, int y));
  MOCK_CONST_METHOD0(GetX,
      int());
  MOCK_CONST_METHOD0(GetY,
      int());
};

// 행위 기반 검증
// 1. 호출 여부 검증 - EXPECT_CALL
// 2. 호출 횟수 검증 - EXPECT_CALL(...).Times(2)
// 3. 호출 순서 검증 - InSequence
// 4. 인자 검증

void foo(User* p) {
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
}

// AnyNumber
using ::testing::AnyNumber;
TEST(GoogleMockTest, example1) {
	// 1. Mock 객체 생성
	MockUser mock;

	// 2. 기대 행위 명시
	// EXPECT_CALL(mock, Stop());
	// EXPECT_CALL(mock, Stop()).Times(2);
	EXPECT_CALL(mock, Stop()).Times(AnyNumber());

	// 3. 수행
	foo(&mock);
}

void goo(User* p) {
	p->Move(10, 20);
	p->Move(20, 30);
	p->Stop();
}


// 인자를 항상 명시해야 하는 것이 아닙니다.
using ::testing::_;

using ::testing::InSequence;
// 순서를 검증하고 싶다면, InSequence 객체를 생성하면 됩니다.
TEST(GoogleMockTest, example2) {
	InSequence seq; // !!
	MockUser mock;

	EXPECT_CALL(mock, Move(10, _));
	EXPECT_CALL(mock, Move(_, _));
	EXPECT_CALL(mock, Stop());

	goo(&mock);
}
















