#ifndef __FILE_READER_HPP__
#define __FILE_READER_HPP__
#include <string>
#include <fstream>

class FileReader{
public:
    FileReader() = delete;
    ~FileReader() = default;
    static auto ReadFile(std::string_view path) -> std::string;
};

#endif //!__FILE_READER_HPP__