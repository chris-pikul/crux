#include <cstdlib>
#include <iostream>

#include <crux-common/common.h>
#include <crux-window/window.h>

int main() {
	// Test the common lib
	crux::TestCommon();

	// Test the window creation
	auto optWindow = crux::Window::Create({ "Crux Example", 800, 600 });
	if( optWindow ) {
		std::cout << "Window created successfully!" << std::endl;
	}
	auto window = optWindow.value();

	auto props = window->GetProperties();
	printf("Window Properties: W=%d H=%d X=%d Y=%d\n", props.width, props.height, props.positionX, props.positionY);
	
	system("pause");
	return 0;
}