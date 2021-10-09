#include "File.hpp" 

void File::open(std::filesystem::path t_filePath, std::fstream::openmode t_fileFlags) {
	this->m_filePath = t_filePath;
	if (!FileUtil::validateFilePath(this->m_filePath)) {
		FileUtil::correctInvalidFilePath(this->m_filePath);
	}
	this->m_fileStream.open(this->m_filePath, t_fileFlags);
	if (!this->m_fileStream.is_open()) {
		std::cerr << this->m_filePath << " couldn't be opened!" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	this->m_fileStream.seekg(0);
	this->m_fileStream.seekp(0);
	this->m_fileFlags = t_fileFlags;
}

bool File::hasReachedEOF() {
	return this->m_fileStream.eof();
}

void File::moveReadPosition(const std::streampos t_position) {
	this->m_fileStream.seekg(t_position);
}
void File::moveWritePosition(const std::streampos t_position) {
	this->m_fileStream.seekp(t_position);
}

const std::streampos File::getReadPosition() {
	return this->m_fileStream.tellg();
}
const std::streampos File::getWritePosition() {
	return this->m_fileStream.tellp();
}


std::string File::read(const std::streampos t_line) {
	if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::in)) {
		std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		return "";
	}
	else {
		std::string m_temp;
		std::streampos m_previousReadPosition = this->m_fileStream.tellg();
		this->m_fileStream.seekg(t_line);
		std::getline(this->m_fileStream, m_temp);
		this->m_fileStream.seekg(m_previousReadPosition);
		return m_temp;
	}
}
std::string File::read() {
	if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::in)) {
		std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		return "";
	}
	else {
		std::string m_temp;
		std::getline(this->m_fileStream, m_temp);
		return m_temp;
	}
}

std::string File::readWholeFile() {
	if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::in)) {
		std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
		return "";
	}
	else {
		std::string m_temp;
		std::string m_currentLine;
		while (!this->hasReachedEOF()) {
			std::getline(this->m_fileStream, m_currentLine);
			m_temp += m_currentLine + '\n';
		}
		return m_temp;
	}
}

void File::write(const std::streampos t_line, std::string t_data) {
	if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::out)) {
		std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
	}
	else {
		std::streampos m_previousReadPosition = this->m_fileStream.tellp();
		this->m_fileStream.seekp(t_line);
		this->m_fileStream << t_data;
		this->m_fileStream.seekp(m_previousReadPosition);
	}
}

void File::write(std::string t_data) {
	if (!this->m_fileStream.good() || !FileUtil::checkFileFlags(this->m_fileFlags, std::fstream::out)) {
		std::cerr << "Filestream error!" << std::endl;//TODO use liblogging
	}
	else {
		this->m_fileStream << t_data;
	}
}


void File::flush() {
	this->m_fileStream.flush();
}

void File::close() {
	this->m_fileStream.close();
}


File::File(std::filesystem::path t_filePath, std::fstream::openmode t_fileFlags) {
	this->open(t_filePath, t_fileFlags);
}
File::File(const File&) {

}
File::~File() {
	this->flush();
	this->close();
}