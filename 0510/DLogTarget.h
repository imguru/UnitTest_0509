#ifndef DLOGTARGET_H
#define DLOGTARGET_H
#include <string>

// Google Mock은 헤더 파일 선언을 기반으로 코드를 자동으로 생성하는 기능을 제공합니다.

enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

#endif
