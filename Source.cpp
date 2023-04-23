#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Course {
public:
    std::string courseNumber;
    std::string name;
    std::vector<std::string> prerequisites;

    Course() {}

    Course(std::string courseNumber, std::string name, std::vector<std::string> prerequisites) {
        this->courseNumber = courseNumber;
        this->name = name;
        this->prerequisites = prerequisites;
    }
};

void load_data_structure(std::unordered_map<std::string, Course>& courses);
void print_course_list(const std::unordered_map<std::string, Course>& courses);
void print_course(const std::unordered_map<std::string, Course>& courses);

int main() {
    std::unordered_map<std::string, Course> courses;
    int choice = 0;

    while (choice != 4) {
        std::cout << "Menu:\n";
        std::cout << "1. Load Data Structure\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            load_data_structure(courses);
            break;
        case 2:
            print_course_list(courses);
            break;
        case 3:
            print_course(courses);
            break;
        case 4:
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

void load_data_structure(std::unordered_map<std::string, Course>& courses) {
    std::string fileName;
    std::cout << "Enter the file name containing the course data: ";
    std::cin >> fileName;

    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::vector<std::string> tokens;
            std::string token;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            std::string courseNumber = tokens[0];
            std::string name = tokens[1];
            std::vector<std::string> prerequisites(tokens.begin() + 2, tokens.end());

            courses[courseNumber] = Course(courseNumber, name, prerequisites);
        }
        file.close();
        std::cout << "Data loaded successfully.\n";
    }
    else {
        std::cout << "Error opening file.\n";
    }
}

void print_course_list(const std::unordered_map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;
    for (const auto& course : courses) {
        courseNumbers.push_back(course.first);
    }

    std::sort(courseNumbers.begin(), courseNumbers.end());

    std::cout << "Course List:\n";
    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << courseNumber << ": " << course.name << "\n";
        std::cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            std::cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                if (i != 0) {
                    std::cout << ", ";
                }
                std::cout << course.prerequisites[i];
            }
        }
        std::cout << "\n";
    }
}

void print_course(const std::unordered_map<std::string, Course>& courses) {
    std::string courseNumber;
    std::cout << "Enter the course number: ";
    std::cin >> courseNumber;

    auto courseIter = courses.find(courseNumber);
    if (courseIter != courses.end()) {
        const Course& course = courseIter->second;
        std::cout << "Course Number: " << course.courseNumber << "\n";
        std::cout << "Course Name: " << course.name << "\n";
        std::cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            std::cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                if (i != 0) {
                    std::cout << ", ";
                }
                std::cout << course.prerequisites[i];
            }
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Course not found.\n";
    }
}
