#include "FileUtil.hpp"

const bool FileUtil::validateFilePath(std::filesystem::path t_filePath) {
	return std::regex_match(t_filePath.string(), std::regex("^[a-zA-Z0-9_.-]*$"));
}
void FileUtil::correctInvalidFilePath(std::filesystem::path t_filePath) {
	t_filePath = std::regex_replace(t_filePath.string(), std::regex("^[a-zA-Z0-9_.-]*$"),"");
}
const bool FileUtil::checkFileFlags(std::fstream::openmode t_fileFlags, std::fstream::openmode t_requiredFileFlag) {
	return (t_fileFlags & t_requiredFileFlag) == t_requiredFileFlag;
}