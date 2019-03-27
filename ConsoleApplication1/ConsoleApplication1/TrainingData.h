#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
#include <math.h>

using std::map;
using std::string;
using std::vector;

double CalculateLabelPriorProbability(int label, vector<int>& training_labels);

vector<double> VectorLabelPriors(vector<int>& training_labels);

double FindFeatureProbabilityFromClass(int row, int col, int label,
	vector<vector<vector<int>>>& vector_of_images, vector<int>& vector_of_labels);

vector<vector<vector<double>>> VectorClassFeatureProbability(vector<vector<vector<int>>>& vector_of_images,
	vector<int>& vector_of_labels, string file_name, string second_file_name);

double WriteLabelPriorProbabilitiesToFile(vector<double>& vector_label_priors, string file_name);

double WriteClassWhiteFeatureProbability(vector<vector<vector<double>>>& vector_class_feature_probability, string file_name);

const double laplace_smoothing_factor = 0.1;