
// Google Test 에서 리스너를 이용해, 테스트의 결과를 원하는 형태로 출력 가능합니다.
//  - main을 직접 작성해야 합니다.
#include <gtest/gtest.h>

class MyListener : public ::testing::EmptyTestEventListener {
public:
	virtual void OnTestCaseStart(const ::testing::TestCase& /*test_case*/) {
		printf("OnTestCaseStart\n");
	}

	virtual void OnTestCaseEnd(const ::testing::TestCase& /*test_case*/) { 
		printf("OnTestCaseEnd\n");
	}

	virtual void OnTestStart(const ::testing::TestInfo& info) {
		printf("OnTestStart\n");
	}

	virtual void OnTestPartResult(const ::testing::TestPartResult& result) {
		printf("OnTestPartResult\n");
	}

	virtual void OnTestEnd(const ::testing::TestInfo& info) {
		printf("OnTestEnd\n");
	}
};

// $ ./a.out --gtest_output=xml
// => RecordProperty: xml 파일에 추가적인 정보를 기록할 수 있습니다.
TEST(SampleTest, foo) {
	RecordProperty("cpu", "1.2");
	RecordProperty("memory", "5m");
}

TEST(SampleTest, goo) {
	RecordProperty("cpu", "1.2");
	RecordProperty("memory", "5m");
}

TEST(Sample2Test, foo) {}
TEST(Sample2Test, goo) {}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	// 1. Listener의 목록을 얻어옵니다.
	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new MyListener);

	return RUN_ALL_TESTS();
}









