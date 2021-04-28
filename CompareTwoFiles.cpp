#include <vector>
#include <string>
#include <fstream>

bool CompareTwoFiles(const std::string &file_1_name, bool &file_1_open_succeed, const std::string &file_2_name, bool &file_2_open_succeed) {
    std::ifstream file_1, file_2;
    file_1.open(file_1_name, std::ios::binary);
    file_1_open_succeed = static_cast<bool>(file_1);
    if (file_1_open_succeed && file_1_name == file_2_name) {
        file_2_open_succeed = true;
        return true;
    }
    file_2.open(file_2_name, std::ios::binary);
    file_2_open_succeed = static_cast<bool>(file_2);
    if (!file_1_open_succeed || !file_2_open_succeed) {
        return false;
    }

    const std::streampos file_1_begin = file_1.tellg();
    file_1.seekg(0, std::ios::end);
    const std::streampos file_1_end = file_1.tellg();
    const unsigned long long file_1_size = (file_1_end - file_1_begin);
    file_1.seekg(0);
    const std::streampos file_2_begin = file_2.tellg();
    file_2.seekg(0, std::ios::end);
    const std::streampos file_2_end = file_2.tellg();
    const unsigned long long file_2_size = (file_2_end - file_2_begin);
    file_2.seekg(0);
    if (file_1_size != file_2_size) {
        return false;
    }

    const unsigned long long compare_block_size = 4096;
    std::vector<char> file_1_compare_block(compare_block_size, 0), file_2_compare_block(compare_block_size, 0);
    while (true) {
        file_1.read(&file_1_compare_block[0], compare_block_size);
        file_2.read(&file_2_compare_block[0], compare_block_size);
        if (file_1_compare_block != file_2_compare_block) {
            return false;
        }
        if (file_1.eof()) {
            return true;
        }
    }
}
