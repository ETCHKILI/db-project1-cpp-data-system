#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>


struct SelectCourse {
    int student_id;
    int main_course_id;
};

class Compare {
public:
    bool operator () (SelectCourse &a, SelectCourse &b) const
    {
        return a.main_course_id < b.main_course_id;
    }
};


void ReadCities(const std::string& source, std::vector<SelectCourse>& scs);
void ConvertLineToSc(std::string& line, SelectCourse& sc);


int main() {
    clock_t startTime,endTime;
    startTime = clock();

    std::vector<SelectCourse> scs;
    try {
        ReadCities("select_course.csv", scs); //file should be place in the same directory with the .exe file.
    } catch (int a){
    }
    endTime = clock();
    double time1 = endTime - startTime;

    std::vector<SelectCourse> scs2;
    startTime = clock();
    for (auto sc:scs) {
        if (sc.main_course_id < 10 && sc.main_course_id > 2) {
            scs2.push_back(sc);
        }
    }
    for (int i = 0; i < 500; ++i) {
        std::cout << scs2[i].student_id << "|" << scs2[i].main_course_id << '\n';
    }
    endTime = clock();
    double time2 = endTime - startTime;

    startTime = clock();
    std::sort(scs.begin(),scs.end(),Compare());
    for (int i = 0; i < 500; ++i) {
        std::cout << scs[i].student_id << "|" << scs[i].main_course_id << '\n';
    }
    endTime = clock();


    std::cout << "The Read time is: " << time1 / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "The Select time is: " << time2 / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "The Sort time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
}


// open file and take lines one by one and convert them as scs
// return exception_id
void ReadCities(const std::string& source, std::vector<SelectCourse>& scs) {
    std::ifstream in_file(source, std::ios_base::in);
    if (!in_file) {
        throw 10; // exception_id: 11: when read city, cannot open file;
    }
    std::string tmp_line;

    int count = 0;
    while (std::getline(in_file, tmp_line)) {
        SelectCourse tmp_sc;
        ConvertLineToSc(tmp_line, tmp_sc);

        ++count;
        scs.push_back(tmp_sc);
    }
}

// convert one line in the file(string) to sc data
// return int exception_id
void ConvertLineToSc(std::string& line, SelectCourse& sc) {
    int col = 0; // count of column.
    int start = 0; // current index of start char for current column
    int end = 0; // current index of end char for current column
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == ',' || i == line.size() - 1) {
            if (i == line.size() - 1) {
                ++end;
            }
            switch (col) {
                case 0:
                    sc.student_id = std::stoi(line.substr(start, end - start));
                    break;
                case 1:
                    sc.main_course_id = std::stoi(line.substr(start, end - start));
                    break;
                default:
                    break;
            }
            ++col;
            start = i + 1;
        }
        ++end;
    }
}

