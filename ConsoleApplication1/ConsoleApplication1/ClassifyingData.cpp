#include <iostream>
#include "ClassifyingData.h"

//Calculates the posterior probabilities of a class
double CalculatePosteriorProbability(vector<vector<double>>& vector_feature_probabilities) {
	double posterior_probability_of_class = 0.0;
	for (int i = 0; i < kCurrentImageSize; i++) {
		for (int j = 0; j < kCurrentImageSize; j++) {
			posterior_probability_of_class = posterior_probability_of_class + log(vector_feature_probabilities[i][j]);
		}
	}
	return posterior_probability_of_class;
}

//Maps an image to a list of its posterior probabilities per class
map<vector<vector<int>>, vector<double>> MapClassPosteriorProbabilities(vector<double>& vector_label_priors,
	vector<vector<vector<double>>>& vector_class_feature_probability, vector<vector<vector<int>>>& testing_images) {
	map<vector<vector<int>>, vector<double>> map_class_posterior_probabilities;

	for (int i = 0; i < testing_images.size(); i++) {
		vector<vector<int>> current_image = testing_images[i];
		vector<double> vector_test_probabilities;
		for (int j = 0; j < vector_class_feature_probability.size(); j++) {
			int current_label = j;
			vector<vector<double>> vector_feature_probabilities_of_a_class = vector_class_feature_probability[j];
			vector<vector<double>> set_vector_feature_probabilities = 
				SetImageTestFeatureProbabilities(current_image, vector_feature_probabilities_of_a_class);

			double posterior_probability = log(vector_label_priors[current_label])
				+ CalculatePosteriorProbability(set_vector_feature_probabilities);
			vector_test_probabilities.push_back(posterior_probability);
		}
		map_class_posterior_probabilities.insert(std::pair<vector<vector<int>>, vector<double>>(current_image, vector_test_probabilities));
	}
	return map_class_posterior_probabilities;
}

/*Since the feature probabilities are calculated for white pixels by default, this method allows the probability of black
pixel to be stored as well*/
vector<vector<double>> SetImageTestFeatureProbabilities(vector<vector<int>>& current_image, 
	vector<vector<double>>& vector_feature_probabilities) {
	vector<vector<double>> set_vector_feature_probabilities(28, vector<double>(28, 0.0));

	for (int i = 0; i < kCurrentImageSize; i++) {
		for (int j = 0; j < kCurrentImageSize; j++) {
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

//Maps an image to its estimated class, based on the posterior probabilities 
map<vector<vector<int>>, int> MapImageToEstimatedClass(map<vector<vector<int>>, vector<double>>& map_class_posterior_probabilities) {
	map<vector<vector<int>>, int> map_image_to_estimated_class;

	for (map<vector<vector<int>>, vector<double>>::iterator it = map_class_posterior_probabilities.begin(); it != map_class_posterior_probabilities.end(); ++it) {
		vector<vector<int>> current_image = it->first;
		vector<double> vector_posterior_probabilities_per_class = it->second;
		int estimated_class = EstimateImageClass(vector_posterior_probabilities_per_class);
		map_image_to_estimated_class.insert(std::pair<vector<vector<int>>, int>(current_image, estimated_class));
	}
	return map_image_to_estimated_class;
}

//Uses the calculated posterior probabilities to estimate the test image's class by taking the max posterior probability
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

//Maps an image to its actual class
map<vector<vector<int>>, int> MapTestImageToActualClass(vector<vector<vector<int>>>& test_images, vector<int>& test_labels) {
	map<vector<vector<int>>, int> map_test_image_to_actual_class;
	
	for (int i = 0; i < test_images.size(); i++) {
		vector<vector<int>> current_image = test_images.at(i);
		int correct_test_label = test_labels.at(i);
		map_test_image_to_actual_class.insert(std::pair<vector<vector<int>>, int>(current_image, correct_test_label));
	}
	return map_test_image_to_actual_class;
}

