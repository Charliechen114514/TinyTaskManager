#include "IO/IOBaseDriver.h"
#include <filesystem>
#include <fstream>
namespace FileIOTools {
namespace fs = std::filesystem;

inline bool is_file_exsited(const fs::path& path) {
	return fs::exists(path);
}

/**
 * @brief check if the file is readable
 *
 * @param path
 * @return true
 * @return false
 */
inline bool is_readable(const fs::path& path) {
	fs::file_status status = fs::status(path);
	return (status.permissions() & fs::perms::owner_read) != fs::perms::none;
}

/**
 * @brief check if the file is writable
 *
 * @param path
 * @return true
 * @return false
 */
inline bool is_writable(const fs::path& path) {
	fs::file_status status = fs::status(path);
	return (status.permissions() & fs::perms::owner_write) != fs::perms::none;
}

/**
 * @brief to absolute path
 *
 * @param path
 * @return fs::path
 */
inline fs::path to_abs_Path(const fs::path& path) {
	return fs::absolute(path);
}

/**
 * @brief this functions check if the given path target
 *
 * @param file_path the path to the file
 * @param extension the target check extension
 * @return true
 * @return false
 */
inline bool is_target_extension_file(const fs::path& file_path, const char* extension) {
	if (!fs::is_regular_file(file_path)) {
		return false;
	}

	std::string ext = file_path.extension().string();
	std::transform(ext.begin(), ext.end(), ext.begin(),
	               [](unsigned char c) { return std::tolower(c); });

	return ext == extension;
}

};

/**
 * @brief File IO makes IO sessions with files
 *
 */
struct FileIO : public IOBase {
private:
	std::fstream ofs;

public:
	explicit FileIO(const std::filesystem::path& path)
	    : IOBase()
	    , ofs(path) { }
	~FileIO() { ofs.close(); }

	/**
	 * @brief read a line from file
	 *
	 * @param raw_buffer
	 */
	void inline from_io_raw_buffer(std::string& raw_buffer) override {
		std::getline(ofs, raw_buffer);
	}

	/**
	 * @brief write somethings to the file
	 *
	 * @param raw_buffer
	 */
	void inline write_raw_buffer_to_io(const std::string& raw_buffer) override {
		ofs << raw_buffer;
	}
};
