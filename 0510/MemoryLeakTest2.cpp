#include <gtest/gtest.h>

// C / C++에서 프로그램의 수정없이 성능을 올리는 방법 => 공짜 점심
//  => 메모리 할당기 변경하는 방법
//     tcmalloc, jemalloc

// 매크로를 이용해서 아래의 코드를 자동으로 생성하도록 만들어줍시다.
#ifdef MEMORY_TEST
#define DECLARE_MEMORY_TEST()           \
public:							        \
	static int allocObjectCount;        \
									    \
	void* operator new(size_t size) {   \
		++allocObjectCount;             \
		return malloc(size);            \
	}                                   \
								        \
	void operator delete(void* p, size_t) { \
		--allocObjectCount;                 \
		free(p);                            \
	}

#define IMPLEMENTS_MEMORY_TEST(classname)     \
	int classname::allocObjectCount = 0
#else
#define DECLARE_MEMORY_TEST()
#define IMPLEMENTS_MEMORY_TEST(classname)
#endif


class Image {
	DECLARE_MEMORY_TEST()
};

IMPLEMENTS_MEMORY_TEST(Image);

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
#ifdef MEMORY_TEST
	int allocCount;

	virtual void SetUp() override {
		allocCount = Image::allocObjectCount;
	}

	virtual void TearDown() override {
		int diff = Image::allocObjectCount - allocCount;
		EXPECT_EQ(0, diff) << "Memory Leak - " << diff << " objects";
	}
#endif
};

TEST_F(MemoryTest, imageTest) {
	foo();
}















