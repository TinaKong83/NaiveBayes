#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
using std::map;
using std::string;
using std::vector;
using std::multimap;

multimap<int, int> MapActualClassToEstimated(map<vector<vector<int>>, int>& map_test_image_to_estimated_class,
	map<vector<vector<int>>, int>& map_test_image_to_actual_class);

int CountImagesFromRowInCol(int row, int col, multimap<int, int>& map_actual_class_to_estimated);

vector<vector<double>> PopulateConfusionMatrix(multimap<int, int>& map_actual_class_to_estimated);

void PrintConfusionMatrix(vector<vector<double>>& confusion_matrix);

const int kMatrixSize = 10;
