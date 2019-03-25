#include <iostream>
#include "ClassifyingData.h"
using namespace std;

double CalculatePosteriorProbability(vector<vector<double>>& vector_feature_probabilities) {
	double posterior_probability_of_class = 0.0;
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			posterior_probability_of_class = posterior_probability_of_class + log(vector_feature_probabilities[i][j]);
		}
	}
	return posterior_probability_of_class;
}

//key: image
//value: posterior probability per class for that image
map<vector<vector<int>>, vector<double>> MapClassPosteriorProbabilities(map<int, double>& map_label_priors,
	map<int, vector<vector<double>>>& map_feature_probability, vector<vector<vector<int>>>& testing_images) {

	map<vector<vector<int>>, vector<double>> map_class_posterior_probabilities;

	for (int i = 0; i < testing_images.size(); i++) {
		vector<vector<int>> current_image = testing_images[i];
		vector<double> vector_test_probabilities;

		for (map<int, vector<vector<double>>>::iterator it = map_feature_probability.begin(); it != map_feature_probability.end(); ++it) {
			int current_label = it->first;
			vector<vector<double>> vector_feature_probabilities = it->second;
			vector<vector<double>> set_vector_feature_probabilities = SetImageTestFeatureProbabilities(current_image, vector_feature_probabilities);

			double posterior_probability = log(map_label_priors[current_label])
				+ CalculatePosteriorProbability(set_vector_feature_probabilities);
			//PrintVector(set_vector_feature_probabilities);
			cout << "posterior proability is: " << posterior_probability << endl;
			vector_test_probabilities.push_back(posterior_probability);
		}
		map_class_posterior_probabilities.insert(pair<vector<vector<int>>, vector<double>>(current_image, vector_test_probabilities));
	}
	return map_class_posterior_probabilities;
}

vector<vector<double>> SetImageTestFeatureProbabilities(vector<vector<int>>& current_image, vector<vector<double>>& vector_feature_probabilities) {
	vector<vector<double>> set_vector_feature_probabilities(28, vector<double>(28, 0.0));

	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			if (current_image[i][j] == 0) {
				set_vector_feature_probabilities[i][j] = vector_feature_probabilities[i][j];
			}
			else if (current_image[i][j] == 1) {
				set_vector_feature_probabilities[i][j] = 1.0 - (vector_feature_probabilities[i][j]);
			}
		}
	}
	return set_vector_feature_probabilities;
}

//key: image
//value: estimated class
map<vector<vector<int>>, int> MapImageToEstimatedClass(map<vector<vector<int>>, vector<double>>& map_class_posterior_probabilities) {

	map<vector<vector<int>>, int> map_image_to_estimated_class;

	for (map<vector<vector<int>>, vector<double>>::iterator it = map_class_posterior_probabilities.begin(); it != map_class_posterior_probabilities.end(); ++it) {
		vector<vector<int>> current_image = it->first;
		vector<double> vector_posterior_probabilities_per_class = it->second;
		int estimated_class = EstimateImageClass(vector_posterior_probabilities_per_class);
		map_image_to_estimated_class.insert(pair<vector<vector<int>>, int>(current_image, estimated_class));
		cout << "estimated class: " << estimated_class << endl;
	}
	return map_image_to_estimated_class;
}

int EstimateImageClass(vector<double>& vector_posterior_probabilities_per_class) {
	int estimated_class = 0;
	double max_posterior_probability = vector_posterior_probabilities_per_class.at(0);

	for (int i = 0; i < vector_posterior_probabilities_per_class.size(); i++) {
		int current_class = i;
		double current_posterior_probability = vector_posterior_probabilities_per_class[i];
		if (current_posterior_probability > max_posterior_probability) {
			max_posterior_probability = current_posterior_probability;
			estimated_class = current_class;
		}
	}
	return estimated_class;
}

map<vector<vector<int>>, int> MapTestImageToActualClass(vector<vector<vector<int>>>& test_images, vector<int>& test_labels) {
	map<vector<vector<int>>, int> map_test_image_to_actual_class;
	
	for (int i = 0; i < test_images.size(); i++) {
		vector<vector<int>> current_image = test_images.at(i);
		int correct_test_label = test_labels.at(i);
		map_test_image_to_actual_class.insert(pair<vector<vector<int>>, int>(current_image, correct_test_label));
	}
	return map_test_image_to_actual_class;
}

//use printf to only have 2 decimal points