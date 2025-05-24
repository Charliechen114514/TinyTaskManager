#include "IO/interative_io/IOFrontEnd.h"

int main() {

	StandardShellIO shell_io;
	std::string buffer;
	shell_io.from_io_raw_buffer(buffer);
	shell_io.write_raw_buffer_to_io(buffer);
}