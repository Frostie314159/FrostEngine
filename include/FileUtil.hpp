#pragma once
#ifndef FILE_UTIL_HPP_
#define FILE_UTIL_HPP_

#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>

class FileUtil {
public:
	static const bool validateFilePath(std::filesystem::path t_filePath);
	static void correctInvalidFilePath(std::filesystem::path t_filePath);
	static const bool checkFileFlags(std::fstream::openmode t_fileFlags, std::fstream::openmode t_requiredFileFlag);
};

#endif