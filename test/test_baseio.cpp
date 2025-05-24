#include "IO/interative_io/IOFrontEnd.h"
#include <cassert>
#include <sstream>

#define TEST_BASE_CASE "Hello, World!"

int main() {

	// Redirect the standard io
	auto cin_buf = std::cin.rdbuf();
	auto cout_buf = std::cout.rdbuf();

	std::istringstream input_stream(TEST_BASE_CASE "\n");
	std::ostringstream output_stream;

	std::cin.rdbuf(input_stream.rdbuf());
	std::cout.rdbuf(output_stream.rdbuf());

	// main core test

	StandardShellIO shell_io;
	std::string buffer;
	shell_io.from_io_raw_buffer(buffer);
	shell_io.write_raw_buffer_to_io(buffer);

	// reset to the normal
	std::string result = output_stream.str();
	std::cin.rdbuf(cin_buf);
	std::cout.rdbuf(cout_buf);

	// make assertions

	assert(result == TEST_BASE_CASE);
}
