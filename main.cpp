#include "Application/application.h"

int main() {
	auto& app = TinyTaskManagerApplication::application_instance();
	app.app_loop();
}