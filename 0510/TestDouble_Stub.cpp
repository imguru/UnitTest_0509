#include <exception>

// 테스트 대역 4가지 종류
//  1. Test Stub
//  2. Fake Object
//  3. Test Spy
//  4. Mock Object
// => xUnit Test Pattern을 기준

class IOException : public std::exception {
public:
	virtual const char* what() {
		return "Bad connection";
	}
};

class User;
struct IConnection {
	virtual void Move(int x, int y) = 0;
	virtual void Attack(User* p) = 0;

	virtual ~IConnection() {}
};

// TCPConnection, BluetoothConnection ...

class User {
	IConnection *connection;
public:
	User(IConnection* p) : connection(p) {}

	void Move(int x, int y) {
		connection->Move(x, y);
	}

	void Attack(User* user) {
		connection->Attack(user);
	}
};
#include <gtest/gtest.h>

// Test Stub
//  : 특수한 상황을 시뮬레이션 할 수 있다.
//   => 제어할 수 없는 외부 의존물을 통제하는 목적.
//   => 하나의 결과를 처리한다. 

// 네트워크 연결이 끊겼을 때, IOException 예외가 발생하는지 여부를 검증하고 싶다.
class StubConnection : public IConnection {
public:
	virtual void Move(int x, int y) {
		throw IOException();
	}

	virtual void Attack(User* p) {
		throw IOException();
	}
};

TEST(UserTest, moveTest) {
	StubConnection stub;
	User user(&stub);

	EXPECT_THROW(user.Move(10, 20), IOException);
}

TEST(UserTest, attackTest) {
	StubConnection stub;
	User user(&stub);

	EXPECT_THROW(user.Attack(nullptr), IOException);
}





















