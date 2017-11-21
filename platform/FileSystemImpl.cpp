#include "platform/FileSystemImpl.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

namespace sx
{
	CannotOpenFileException::CannotOpenFileException(const std::string path)
		: path(path)
	{}
	
	std::vector<uint32_t> FileSystemImpl::ReadBinary(std::string fileName) const
	{
		std::ifstream file(fileName, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw CannotOpenFileException(fileName);

		size_t fileSize = (size_t)file.tellg();
		std::vector<uint32_t> buffer(fileSize);

		file.seekg(0);
		file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

		file.close();

		return buffer;
	}

	void FileSystemImpl::ReadBinary(const std::string fileName, const std::function<void(std::istream&)> streamAvailable) const
	{
		std::ifstream input(fileName, std::ios::binary);

		if (!input)
			throw CannotOpenFileException(fileName);

		streamAvailable(input);
	}

	void FileSystemImpl::WriteBinary(const std::string fileName, const std::function<void(std::ostream&)> streamAvailable) const
	{
		std::ofstream output(fileName, std::ios::binary);

		if (!output)
			throw CannotOpenFileException(fileName);

		streamAvailable(output);
	}

}
