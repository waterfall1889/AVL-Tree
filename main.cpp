#include <iostream>
#include "AVLTree.h"
#include <string>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <sstream>

using namespace std;

void load_student_info(const std::string &filename, std::vector<key_value_pair<int32_t, std::string>> &data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key_str, value;

        if (std::getline(ss, key_str, ',') && std::getline(ss, value)) {
            try {
                int32_t key = std::stoi(key_str);
                data.emplace_back(key, value);
            } catch (const std::exception &e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        }
    }
    file.close();
}

int main() {
    std::vector<key_value_pair<int32_t, std::string>> data;
    load_student_info("F:\\AVL_tree\\student_info.txt", data);

    AVL_tree<int32_t,std::string > student_information(data);
    student_information.dataStructure();
    return 0;
}
