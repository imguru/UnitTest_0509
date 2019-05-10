#include <gtest/gtest.h>
// 구글 테스트를 이용해서, 특정 기능이 수행되었을 때, 메모리가 누수되었는지 여부를 검증하고 싶다.
// C++ 에서는 객체에 메모리가 할당되는 new의 연산을 재정의할 수 있습니다.

// SUT
class Image {
public:
	static int allocObjectCount;

	void* operator new(size_t size) {
		printf("Image 객체 할당\n");	
		++allocObjectCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("Image 객체 해지\n");
		--allocObjectCount;
		free(p);
	}
};

int Image::allocObjectCount = 0;


void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;

	// delete p1;
	// delete p2;
	delete p3;
}

class MemoryTest: public ::testing::Test {
protected:
	int allocCount;

	virtual void SetUp() override {
		allocCount = Image::allocObjectCount;
	}

	virtual void TearDown() override {
		int diff = Image::allocObjectCount - allocCount;
		EXPECT_EQ(0, diff) << "Memory Leak - " << diff << " objects";
	}
};

TEST_F(MemoryTest, imageTest) {
	foo();
}















