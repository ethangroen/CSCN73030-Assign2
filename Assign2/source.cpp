#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct STUDENT_DATA {
    std::string first_name;
    std::string last_name;
};

std::vector<STUDENT_DATA> readStudentData(const std::string& filename) {
    std::vector<STUDENT_DATA> students;
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return students;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string first_name, last_name;

        // Splitting based on the comma
        if (std::getline(ss, last_name, ',') && std::getline(ss, first_name)) {
            STUDENT_DATA student = { first_name, last_name };
            students.push_back(student);
        }
    }

    file.close();
    return students;
}

int main() {
    std::vector<STUDENT_DATA> students = readStudentData("StudentData.txt");

    // Display loaded students for verification
    for (const auto& student : students) {
        std::cout << student.first_name << " " << student.last_name << std::endl;     // display names for debugging
    }

    return 1;
}