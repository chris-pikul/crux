#include "common.h"

#include "platform.h"

namespace crux {
	void TestCommon() {
		printf("crux-common is active\n");

		if (TargetPlatform == Platform::WINDOWS) {
			printf("platform is windows\n");
		}
	}
}
