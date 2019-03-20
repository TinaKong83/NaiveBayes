#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;

class TrainingData {
public:
	double CalculateLabelPriorProbability(int label, vector<int> training_labels);
	map<int, double> MapLabelPriors(vector<int> training_labels);
	double FindFeatureProbabilityFromClass(int row, int col, int label, int feature, multimap <int, vector<vector<int>>> map_label_to_image);
};

const double laplace_smoothing_factor = 1.0;