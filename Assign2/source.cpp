#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct STUDENT_DATA {
    std::string first_name;
    std::string last_name;
    std::string email; // Optional field for pre-release mode
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

// Function to read emails (for pre-release only)
std::vector<STUDENT_DATA> readStudentEmails(const std::string& filename, std::vector<STUDENT_DATA>& students) {
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Error opening email file: " << filename << std::endl;
        return students;
    }

    size_t index = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string last_name, first_name, email;

        // Splitting based on the comma
        if (std::getline(ss, last_name, ',') && std::getline(ss, first_name, ',') && std::getline(ss, email)) {
            // If names match with students list, add email
            if (index < students.size() && students[index].first_name == first_name && students[index].last_name == last_name) {
                students[index].email = email;
                index++;
            }
        }
    }

    file.close();
    return students;
}

int main() {
    // Display if it's standard or pre-release mode
#ifdef PRE_RELEASE
    std::cout << "Application running in pre-release mode" << std::endl;
#else
    std::cout << "Application running in standard mode" << std::endl;
#endif

    std::vector<STUDENT_DATA> students = readStudentData("StudentData.txt");

#ifdef PRE_RELEASE
    // If pre-release, read emails from StudentData_Emails.txt
    students = readStudentEmails("StudentData_Emails.txt", students);
#endif

    // Print out the students and their emails if available
    for (const auto& student : students) {
        std::cout << student.first_name << " " << student.last_name; // display names for debugging
        if (!student.email.empty()) {
            std::cout << " - Email: " << student.email;
        }
        std::cout << std::endl;
    }

    return 1;
}