#include <iostream>
#include "TrainingData.h"
#include <math.h>
using namespace std;

//Calculates the prior probability of a label
double CalculateLabelPriorProbability(int label, vector<int>& training_labels) {
	int label_count = 0;
	for (int i = 0; i < training_labels.size(); i++) {
		if (training_labels.at(i) == label) {
			label_count++;
		}
	}
	double label_prior_probability = (double) label_count / training_labels.size();
	return label_prior_probability;
}

//Creates a vector (of size 10), with each position holding the prior probability of that label
vector<double> VectorLabelPriors(vector<int>& training_labels) {
	vector<double> vector_label_priors;
	for (int i = 0; i < 10; i++) {
		double prior_probability = CalculateLabelPriorProbability(i, training_labels);
		vector_label_priors.push_back(prior_probability);
	}
	return vector_label_priors;
}

//Find the probability that a feature is some value in your specified position, 
//Using formula: P(Fi,j =f|class=c)= (k + # of times F(i,j) =f when class=c) / (2k + Total number of training examples where class = c)
double FindFeatureProbabilityFromClass(int row, int col, int label, 
	vector<vector<vector<int>>>& vector_of_images, vector<int>& vector_of_labels) {
	int count_label_occurrence = 0;
	int count_position_matches_feature = 0;

	for (int i = 0; i < vector_of_images.size(); i++) {
		int current_label = vector_of_labels.at(i);
		if (current_label == label) {
			count_label_occurrence++;
			vector<vector<int>> current_image = vector_of_images.at(i);
			if (current_image.at(row).at(col) == 0) {
				count_position_matches_feature++;
			}
		}
	}
	double feature_probability = (laplace_smoothing_factor + count_position_matches_feature) / (2 * laplace_smoothing_factor + count_label_occurrence);
	return feature_probability;
}

//Generates a list of 2D vectors (of size 10). Each 2D vector in the list is populated with feature probabilities (for that class). 
//Writes feature probabilities into white and black pixel files 
vector<vector<vector<double>>> VectorClassFeatureProbability(vector<vector<vector<int>>>& vector_of_images, 
	vector<int>& vector_of_labels, string file_name, string second_file_name) {

	std::ofstream white_feature_file;
	white_feature_file.open(file_name);

	std::ofstream black_feature_file;
	black_feature_file.open(second_file_name);

	if (white_feature_file.fail() || black_feature_file.fail()) {
		cout << "File is invalid." << endl;
	}
	vector<vector<vector<double>>> vector_class_feature_probabilities;

	for (int class_value = 0; class_value < 10; class_value++) {
		vector<vector<double>> vector_of_probabilities(28, vector<double>(28, 0.0));
		for (int i = 0; i < 28; i++) {
			for (int j = 0; j < 28; j++) {
				vector_of_probabilities[i][j] = FindFeatureProbabilityFromClass(i, j, class_value, vector_of_images, vector_of_labels);
				white_feature_file << vector_of_probabilities[i][j] << " ";
				black_feature_file << 1.0 - vector_of_probabilities[i][j] << " ";
			}
			cout << endl;
		}
		vector_class_feature_probabilities.push_back(vector_of_probabilities);
	}
	return vector_class_feature_probabilities;
}

//Writes each label's independent prior probability to a file
double WriteLabelPriorProbabilitiesToFile(vector<double>& vector_label_priors, string file_name) {
	std::ofstream output_file;
	output_file.open(file_name);

	if (output_file.fail()) {
		cout << "File is invalid." << endl;
	}
	else {
		for (int i = 0; i < vector_label_priors.size(); i++) {
			output_file << i << " " << vector_label_priors.at(i) << endl;
		}
	}
	return 0.0;
}

