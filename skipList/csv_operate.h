#ifndef CSV_OPERATE_H
#define CSV_OPERATE_H

#include <fstream>
#include <string>
#include <vector>

void write_csv();
std::vector<int> get_id_from_csv(const std::string& filename);
bool comp(const std::vector<int>& a, const std::vector<int>& b);
void sort_all_ages(std::vector<std::vector<int>>& all_ages);
int get_age_from_csv(const std::string& filename);

#endif
