#ifndef FILE_SYSTEM_IMPL_HPP
#define FILE_SYSTEM_IMPL_HPP

#include "interfaces/FileSystem.hpp"

namespace sx
{
	class FileSystemImpl
		: public FileSystem
	{
	public:
		FileSystemImpl() = default;
		virtual ~FileSystemImpl() = default;

		std::vector<uint32_t> ReadBinary(std::string fileName) const override;
		void ReadBinary(const std::string fileName, const std::function<void(std::istream&)> streamAvailable) const override;
		void WriteBinary(const std::string fileName, const std::function<void(std::ostream&)> streamAvailable) const override;
	};
}

#endif