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

map<vector<vector<int>>, vector<double>> MapClassPosteriorProbabilities(vector<double>& vector_label_priors,
	vector<vector<vector<double>>>& vector_class_feature_probability, vector<vector<vector<int>>>& testing_images);

vector<vector<double>> SetImageTestFeatureProbabilities(vector<vector<int>>& current_image,
	vector<vector<double>>& vector_feature_probabilities);

map<vector<vector<int>>, int> MapImageToEstimatedClass(map<vector<vector<int>>, vector<double>>& map_class_posterior_probabilities);

vector<int> VectorTestImageEstimatedClasses(map<vector<vector<int>>, vector<double>>& map_class_posterior_probabilities);

int EstimateImageClass(vector<double>& vector_posterior_probabilities_per_class);

map<vector<vector<int>>, int> MapTestImageToActualClass(vector<vector<vector<int>>>& test_images, vector<int>& test_labels);

const int kCurrentImageSize = 28;
