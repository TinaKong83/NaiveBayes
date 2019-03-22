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
map<int, double> MapClassPosteriorProbabilities(map<int, double>& map_label_priors, map<int, vector<vector<double>>>& map_feature_probability);
int EstimateImageClass(map<int, double>& map_class_posterior_probabilities);
map<int, vector<vector<int>>> MapEstimatedClassToImage(multimap<int, vector<vector<int>>>& map_labels_to_images,
	map<int, double>& map_class_posterior_probabilities);