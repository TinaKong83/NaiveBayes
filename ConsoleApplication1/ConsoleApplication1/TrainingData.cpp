#include <iostream>
#include "TrainingData.h"
#include <math.h>
using namespace std;

//use formula for estimating priors
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

//Creates a map of size 10: each element in the map is a class (0 to 9) as the key,
//and the prior probability of the class as the value
vector<double> VectorLabelPriors(vector<int>& training_labels) {
	vector<double> vector_label_priors;
	for (int i = 0; i < 10; i++) {
		double prior_probability = CalculateLabelPriorProbability(i, training_labels);
		vector_label_priors.push_back(prior_probability);
	}
	return vector_label_priors;
}

//Find the probability that a feature is some value in your specified position, 
//given an image that is a certain label
//Use formula: P(Fi,j =f|class=c)= (k + # of times F(i,j) =f when class=c) / (2k + Total number of training examples where class = c)
//multimap <int, vector<vector<int>>> map_label_to_image;

/*
double FindFeatureProbabilityFromClass(int row, int col, int label, 
	multimap <int, vector<vector<int>>>& map_label_to_image) {

	//loop through the training image labels (key in your map), finding occurances of it
	//int dark_pixel = 1;
	int count_label_occurrence = map_label_to_image.count(label);
	int count_position_matches_feature = 0;
	
	//now loop through your map map_label_to_image
	//count_position_matches_feature looks for dark pixels only, so only stores feature probabiltiies of dark pixels for now
	for (multimap<int, vector<vector<int>>>::iterator it = map_label_to_image.begin(); it != map_label_to_image.end(); ++it) {
		//it->first gives you the key (the label)
		int current_label = it->first;
		if (current_label == label) {
			vector<vector<int>> current_image = it->second;
			if (current_image.at(row).at(col) == 0) {
				count_position_matches_feature++;
			}
		}
	}
	double feature_probability = (laplace_smoothing_factor + count_position_matches_feature) / (2 * laplace_smoothing_factor + count_label_occurrence);
	return feature_probability;
}*/

//=======================================//
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


//list of 2d vectors, size 10 (each index of 3d vector is a class)
//each 2d vector is populated with feature probabiltiies 

//create a map <int, vector<vector<double>>>
//vector is of size 28x28, each element in vector is the feature probability of that position
vector<vector<vector<double>>> VectorClassFeatureProbability(vector<vector<vector<int>>>& vector_of_images, 
	vector<int>& vector_of_labels, string file_name) {

	std::ofstream output_file;
	output_file.open(file_name);

	if (output_file.fail()) {
		cout << "File is invalid." << endl;
	}
	vector<vector<vector<double>>> vector_class_feature_probabilities;

	for (int class_value = 0; class_value < 10; class_value++) {
		cout << endl;
		cout << "I AM IN CLASS: " << class_value << endl;
		vector<vector<double>> vector_of_probabilities(28, vector<double>(28, 0.0));
		for (int i = 0; i < 28; i++) {
			for (int j = 0; j < 28; j++) {
				vector_of_probabilities[i][j] = FindFeatureProbabilityFromClass(i, j, class_value, vector_of_images, vector_of_labels);
				//cout << vector_of_probabilities[i][j] << " ";
				output_file << vector_of_probabilities[i][j] << " ";
			}
			cout << endl;
		}
		vector_class_feature_probabilities.push_back(vector_of_probabilities);
	}
	return vector_class_feature_probabilities;
}

//Writing label prior prob to file
double WriteLabelPriorProbabilitiesToFile(vector<double>& vector_label_priors, string file_name) {
	//cout << "is this being printed?";
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


//FIX THE MAP IN YOUR PARAMETER!!
/*double WriteClassWhiteFeatureProbability(map<int, vector<vector<double>>> map_class_feature_probability, string file_name) {
	std::ofstream output_file;
	output_file.open(file_name);

	if (output_file.fail()) {
		cout << "File is invalid." << endl;
	}
	else {
		for (map<int, vector<vector<double>>>::iterator it = map_class_feature_probability.begin(); 
			it != map_class_feature_probability.end(); ++it) {

			output_file << it->first << endl; 
			vector<vector<double>> current_image_probabilities = it->second;
			for (int i = 0; i < 28; i++) {
				for (int j = 0; j < 28; j++) {
					output_file << current_image_probabilities[i][j] << " " << endl;
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0.0;
}*/

//=====================================================//

double WriteClassWhiteFeatureProbability(vector<vector<vector<double>>>& vector_class_feature_probability, string file_name) {
	std::ofstream output_file;
	output_file.open(file_name);

	if (output_file.fail()) {
		cout << "File is invalid." << endl;
	}
	else {
		for (int i = 0; i < vector_class_feature_probability.size(); i++) {
			int current_label = i;
			output_file << current_label << endl;

			vector<vector<double>> current_image_probabilities = vector_class_feature_probability[i];
			for (int j = 0; j < 28; j++) {
				for (int k = 0; k < 28; k++) {
					output_file << current_image_probabilities[j][k] << " " << endl;
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0.0;
}




//map<int, vector<vector<double>>> MapClassFeatureProbability

