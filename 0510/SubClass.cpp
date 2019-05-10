// 테스트 전용 하위 클래스 패턴
// SUT
class Engine {
public:
	virtual void Start() { printf("Engine start...\n"); }
	virtual ~Engine() {}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	virtual void Start() { 
		engine->Start(); 
	}
	virtual ~Car() {}
}

//-------------------
#include <gtest/gtest.h>

// 상속: is-a
// class Rect : public Shape {};
//  => Rect is a Shape

// TestEngine is a Engine;
class TestEngine : public Engine {
	bool isStart_;
public:
	TestEngine() : isStart_(false) {}

	virtual void Start() override {
		Engine::Start(); // 부모의 기능을 수행한다.
		isStart_ = true;
	}

	bool IsStart() { return isStart_; }
};

// Car 객체가Start를 호출하면, 소유하고 있는 Engine 객체의 Start가 호출되는지 여부를
// 검증하고 싶다.
class CarTest : public ::testing::Test {};

TEST_F(CarTest, engineTest) {
	TestEngine engine;
	Car car(&engine);

	car.Start();

	ASSERT_TRUE(engine.IsStart());
}


#if 0
TEST_F(CarTest, engineTest) {
	Engine engine;
	Car car(&engine);

	car->Start();

	// 관찰할 수 있는 상태가 존재하지 않아서, ASSERT를 수행할 수 없다.
}
#endif





















