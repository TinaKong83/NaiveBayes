#include <iostream>
#include "ClassifyingData.h"
using namespace std;

double CalculatePosteriorProbability(vector<vector<double>>& vector_feature_probabilities) {
	double posterior_probability_of_class = 0.0;
	for (int i = 0; i < vector_feature_probabilities.size(); i++) {
		for (int j = 0; j < vector_feature_probabilities[i].size(); j++) {
			posterior_probability_of_class = posterior_probability_of_class + log(vector_feature_probabilities[i][j]);
		}
	}
	return posterior_probability_of_class;
}

//Calculate the posterior probabilities for each class in a single image???
map<int, double> MapClassPosteriorProbabilities(map<int, double>& map_label_priors, map<int, vector<vector<double>>>& map_feature_probability) {
	map<int, double> map_class_posterior_probabilities;

	for (map<int, vector<vector<double>>>::iterator it = map_feature_probability.begin(); it != map_feature_probability.end(); ++it) {
		int current_label = it->first;
		vector<vector<double>> vector_feature_probabilities = it->second;
		double posterior_probability = log(map_label_priors.find(current_label)->second)
			+ CalculatePosteriorProbability(vector_feature_probabilities);
		map_class_posterior_probabilities.insert(pair<int, double>(current_label, posterior_probability));
	}

	for (map<int, double>::iterator it = map_class_posterior_probabilities.begin(); it != map_class_posterior_probabilities.end(); ++it) {
		cout << "key: \"" << it->first << "\" "
			<< "value: " << it->second << endl;
	}
	return map_class_posterior_probabilities;
}

int EstimateImageClass(map<int, double>& map_class_posterior_probabilities) {
	int assigned_class = 0;
	double max_posterior_probability = map_class_posterior_probabilities.begin()->second;

	for (map<int, double>::iterator it = map_class_posterior_probabilities.begin(); it != map_class_posterior_probabilities.end(); ++it) {
		int current_label = it->first;
		double current_posterior_probability = it->second;
		if (current_posterior_probability >= max_posterior_probability) {
			max_posterior_probability = current_posterior_probability;
			assigned_class = current_label;
		}
	}
	return assigned_class;
}

//now map an estimated class to an image??
map<int, vector<vector<int>>> MapEstimatedClassToImage(multimap<int, vector<vector<int>>>& map_labels_to_images, 
	map<int, double>& map_class_posterior_probabilities) {

	map<int, vector<vector<int>>> map_estimated_class_to_image;

	for (multimap<int, vector<vector<int>>>::iterator it = map_labels_to_images.begin(); it != map_labels_to_images.end(); ++it) {
		vector<vector<int>> current_image = it->second;
		int estimated_class = EstimateImageClass(map_class_posterior_probabilities);
		map_estimated_class_to_image.insert(pair<int, vector<vector<int>>>(estimated_class, current_image));
		cout << "estimated class of the image is: " << estimated_class << endl;
	}
	return map_estimated_class_to_image;
}
