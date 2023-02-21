#include "csv_operate.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

void write_csv()
{
    std::ofstream file25("25.csv");
    if (file25.is_open())
    {
        file25 << "Id, Name, Age, Grade\n";
        file25 << "5, John Doe, 25, 80\n";
        file25 << "6, Jane Doe, 25, 90\n";
        file25 << "7, Alice, 25, 90\n";
        file25 << "8, Tom, 25, 90\n";
        file25.close();
        std::cout << "Data25 written to file\n";
    }
    else
    {
        std::cout << "Unable to open file\n";
    }

    std::ofstream file18("18.csv");
    if (file18.is_open())
    {
        file18 << "Id, Name, Age, Grade\n";
        file18 << "1, John Doe, 18, 80\n";
        file18 << "2, Jane Doe, 18, 90\n";
        file18 << "3, Alice, 18, 90\n";
        file18 << "4, Tom, 18, 90\n";
        file18.close();
        std::cout << "Data18 written to file\n";
    }
    else
    {
        std::cout << "Unable to open file\n";
    }

    std::ofstream file33("33.csv");
    if (file33.is_open())
    {
        file33 << "Id, Name, Age, Grade\n";
        file33 << "9, John Doe, 33, 80\n";
        file33 << "10, Jane Doe, 33, 90\n";
        file33.close();
        std::cout << "Data33 written to file\n";
    }
    else
    {
        std::cout << "Unable to open file\n";
    }
}

std::vector<int> get_id_from_csv(const std::string& filename)
{
    std::vector<int> ids;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        // 忽略第一行的标题
        getline(file, line);

        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string cell;
            // 获取第一列的数据
            getline(ss, cell, ',');
            ids.push_back(std::stoi(cell));
        }
        file.close();
        std::cout << "Data read from file\n";
    }
    else
    {
        std::cout << "Unable to open file\n";
    }

    return ids;
}

int get_age_from_csv(const std::string& filename) {
    int ages = 0;
    std::ifstream file(filename);
    std::string line;
    // 跳过标题行
    std::getline(file, line);
    // 获取第二行数据
    std::getline(file, line);
    // 使用istringstream从行字符串中解析数据
    std::istringstream ss(line);
    std::string cell;
    // 循环解析每个单元格的数据
    for (int i = 0; i < 3; i++) {
        std::getline(ss, cell, ',');
        // 第三列为age
        if (i == 2) {
            ages = std::stoi(cell);
            break;
        }
    }
    return ages;
}

bool comp(const std::vector<int>& a, const std::vector<int>& b) {
    return a[0] > b[0];
}

void sort_all_ages(std::vector<std::vector<int>>& all_ages) {
    std::sort(all_ages.begin(), all_ages.end(), comp);
}
