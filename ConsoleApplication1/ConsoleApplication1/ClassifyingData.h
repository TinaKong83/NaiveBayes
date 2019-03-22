#pragma once
#include <math.h>;
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;

double CalculatePosteriorProbability(vector<vector<double>>& vector_feature_probabilities);
map<vector<vector<int>>, vector<double>> MapClassPosteriorProbabilities(map<int, double>& map_label_priors,
	map<int, vector<vector<double>>>& map_feature_probability, vector<vector<vector<int>>>& testing_images);
map<vector<vector<int>>, int> MapImageToEstimatedClass(map<vector<vector<int>>, vector<double>>& map_class_posterior_probabilities);
int EstimateImageClass(vector<double>& vector_posterior_probabilities_per_class);
