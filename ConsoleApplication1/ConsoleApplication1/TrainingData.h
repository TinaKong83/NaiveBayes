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
};