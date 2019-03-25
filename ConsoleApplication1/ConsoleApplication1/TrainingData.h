#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;

double CalculateLabelPriorProbability(int label, vector<int>& training_labels);
map<int, double> MapLabelPriors(vector<int>& training_labels);
double FindFeatureProbabilityFromClass(int row, int col, int label, multimap <int, vector<vector<int>>>& map_label_to_image);
map<int, vector<vector<double>>> MapClassFeatureProbability(multimap <int, vector<vector<int>>>& map_label_to_image, string file_name);

double WriteLabelPriorProbabilitiesToFile(map<int, double> map_label_priors, string file_name);
double WriteClassWhiteFeatureProbability(map<int, vector<vector<double>>> map_class_feature_probability, string file_name);

const double laplace_smoothing_factor = 0.1;