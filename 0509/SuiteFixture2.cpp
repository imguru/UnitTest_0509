#include <string>
#include <stdio.h>

#include <unistd.h> // sleep(2)

class Database {
public:
	// Connect / Disconnect가 느리다고 가정해보자.
	void Connect() { sleep(2); }    // SetUp
	void Disconnect() { sleep(1); } // TearDown
	
	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};

// - SetUpTestCase()
// DatabaseTest()
//  SetUp()
//   foo()
//  TearDown()
// DatabaseTest()
//  SetUp()
//   goo()
//  TearDown()
// - TearDownTestCase()

// Test Suite(Test Case): 동일한 픽스쳐를 공유하는 테스트 함수의 집합.

// Suite Fixture
//  : 픽스쳐 설치/해체의 시간이 오래 걸려서, 테스트 함수가 추가될 때마다
//    전체적인 테스트 시간이 늘어나는 문제를 해결하기 위해서 사용한다.
//   => Slow Test 문제
//     : 테스트가 너무 느려서, 개발자들이 SUT가 변경되어도 테스트를 실행하지 않는다.
//       (테스트를 실행하는 개발자의 생산성을 떨어뜨린다.)

//  문제점
//    : 공유하는 픽스쳐 전략.
//     => 각각의 테스트 함수는 더 이상 독립적이지 않다.

#include <gtest/gtest.h>

class DatabaseTest : public ::testing::Test {
protected:
	static Database *database;
	DatabaseTest() { printf("DatabaseTest()\n"); }

	// Suite Fixture SetUp / TearDown 함수는 정적 멤버 함수로 구현되어 있습니다.
	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
		database = new Database;
		database->Connect();
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
		database->Disconnect();
		delete database;
	}

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

// C++은 정적 멤버 변수에 대해서 소스파일에 정의가 필요합니다.
Database* DatabaseTest::database = nullptr;

TEST_F(DatabaseTest, foo) { printf("  foo()\n"); }
TEST_F(DatabaseTest, goo) { printf("  goo()\n"); }
TEST_F(DatabaseTest, hoo) { printf("  goo()\n"); }
TEST_F(DatabaseTest, xoo) { printf("  goo()\n"); }

TEST_F(DatabaseTest, DISABLED_loginTest) {
	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인 하였을 때";
}

TEST_F(DatabaseTest, DISABLED_logoutTest) {
	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "데이터베이스에 로그아웃 하였을 때";
}
