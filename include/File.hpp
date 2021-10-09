#pragma once

#ifndef FILE_HPP_
#define FILE_HPP_
#include <iostream>
#include <fstream>
#include "FileUtil.hpp"

class File {
	std::filesystem::path		m_filePath;
	std::ios_base::openmode		m_fileFlags;
	std::fstream				m_fileStream;
public:
	void open(std::filesystem::path t_filePath, std::fstream::openmode t_fileFlags);

	bool hasReachedEOF();

	void moveReadPosition(const std::streampos t_position);
	void moveWritePosition(const std::streampos t_position);

	const std::streampos getReadPosition();
	const std::streampos getWritePosition();

	template<typename T, size_t t_bufferSize>
	void readBinary(const std::streampos t_line, T(&t_buffer)[t_bufferSize]) {
		if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::binary) || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::in)) {
			std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		}
		else {
			std::streampos m_previousReadPosition = this->m_fileStream.tellg();
			this->m_fileStream.seekg(t_line);
			for (size_t i = 0; i < t_bufferSize; i++)
				this->m_fileStream.read((char*)&t_buffer[i], sizeof(T));
			this->m_fileStream.seekg(m_previousReadPosition);
		}
	}

	template<typename T, size_t t_bufferSize>
	void readBinary(T(&t_buffer)[t_bufferSize]) {
		if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::binary) || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::in)) {
			std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		}
		else {
			for (size_t i = 0; i < t_bufferSize; i++)
				this->m_fileStream.read((char*)&t_buffer[i], sizeof(T));
		}
	}


	template<typename T, size_t t_bufferSize>
	void writeBinary(const std::streampos t_line, T(&t_buffer)[t_bufferSize]) {
		if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::binary) || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::out)) {
			std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		}
		else {
			std::streampos m_previousReadPosition = this->m_fileStream.tellp();
			this->m_fileStream.seekp(t_line);
			for (size_t i = 0; i < t_bufferSize; i++)
				this->m_fileStream.write((char*)&t_buffer[i], sizeof(T));
			this->m_fileStream.seekp(m_previousReadPosition);
		}
	}
	template<typename T, size_t t_bufferSize>
	void writeBinary(T(&t_buffer)[t_bufferSize]) {
		if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::binary) || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::out)) {
			std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		}
		else {
			for (size_t i = 0; i < t_bufferSize; i++)
				this->m_fileStream.write((char*)&t_buffer[i], sizeof(T));
		}
	}


	void write(const std::streampos t_line, std::string t_data);
	void write(std::string t_data);

	std::string read(const std::streampos t_line);
	std::string read();

	std::string readWholeFile(const std::streampos t_line);
	std::string readWholeFile();


	void flush();
	void close();
	File(std::filesystem::path t_filePath, std::fstream::openmode t_fileFlags);
	File(const File&);
	File();
	~File();
};

#endif