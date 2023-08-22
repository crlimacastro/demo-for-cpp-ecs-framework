#include "fae_framework.hpp"
#include <GLFW/glfw3.h>

int main()
{
	fae::ecs_application test_application{};
	test_application.run();

	glfwInit();
	fae::glfw_window test_window{};
	do {
		glfwPollEvents();
	} while (!test_window.should_close());
}