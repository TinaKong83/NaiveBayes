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

//INSTEAD OF PASSING IN FEATURE AS AN ARGUMENT, COUNT THE NUM OF BLACK PIXELS YOU HAVE..
//look at max piazza post



//Calculate the posterior probabilities for each class in a single image???
/*map<int, double> MapClassPosteriorProbabilities(map<int, double>& map_label_priors, map<int, vector<vector<double>>>& map_feature_probability, vector<vector<int>> single_image) {
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
}*/

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

			double posterior_probability = log(map_label_priors.find(current_label)->second)
				+ CalculatePosteriorProbability(set_vector_feature_probabilities);
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
			if (current_image[i][j] == 1) {
				set_vector_feature_probabilities[i][j] = vector_feature_probabilities[i][j];
			}
			else if (current_image[i][j] == 0) {
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
		if (current_posterior_probability >= max_posterior_probability) {
			max_posterior_probability = current_posterior_probability;
			estimated_class = current_class;
		}
	}
	return estimated_class;
}


/*int EstimateImageClass(map<int, double>& map_class_posterior_probabilities) {
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
}*/

//now map an estimated class to an image??
/*map<int, vector<vector<int>>> MapEstimatedClassToImage(vector<vector<vector<int>>>& vector_of_test_images, 
	map<int, double>& map_class_posterior_probabilities) {

	map<int, vector<vector<int>>> map_estimated_class_to_image;

	/*for (multimap<int, vector<vector<int>>>::iterator it = map_labels_to_images.begin(); it != map_labels_to_images.end(); ++it) {
		vector<vector<int>> current_image = it->second;
		int estimated_class = EstimateImageClass(map_class_posterior_probabilities);
		map_estimated_class_to_image.insert(pair<int, vector<vector<int>>>(estimated_class, current_image));
		cout << "estimated class of the image is: " << estimated_class << endl;
	}*

	for (int i = 0; i < vector_of_test_images.size(); i++) {
		int estimated_class = EstimateImageClass(map_class_posterior_probabilities);
		vector<vector<int>> current_image = vector_of_test_images[i];
		map_estimated_class_to_image.insert(pair<int, vector<vector<int>>>(estimated_class, current_image));
	}
	return map_estimated_class_to_image;
}*/
