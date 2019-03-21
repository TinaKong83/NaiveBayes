#include <iostream>
#include "TrainingData.h"
#include <math.h>
using namespace std;

//use formula for estimating priors
double CalculateLabelPriorProbability(int label, vector<int> training_labels) {
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
map<int, double> MapLabelPriors(vector<int> training_labels) {
	map<int, double> map_label_priors;
	for (int i = 0; i < 10; i++) {
		double prior_probability = CalculateLabelPriorProbability(i, training_labels);
		map_label_priors.insert(pair<int, double>(i, prior_probability));
	}

	/*for (map<int, double>::iterator it = map_label_priors.begin(); it != map_label_priors.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}*/

	return map_label_priors;
}

//Find the probability that a feature is some value in your specified position, 
//given an image that is a certain label
//Use formula: P(Fi,j =f|class=c)= (k + # of times F(i,j) =f when class=c) / (2k + Total number of training examples where class = c)
//multimap <int, vector<vector<int>>> map_label_to_image;
double FindFeatureProbabilityFromClass(int row, int col, int label, int feature, 
	multimap <int, vector<vector<int>>> map_label_to_image) {

	//loop through the training image labels (key in your map), finding occurances of it
	int count_label_occurrence = map_label_to_image.count(label);
	int count_position_matches_feature = 0;
	
	//now loop through your map map_label_to_image
	for (multimap<int, vector<vector<int>>>::iterator it = map_label_to_image.begin(); it != map_label_to_image.end(); ++it) {
		//it->first gives you the key (the label)
		int current_label = it->first;
		if (current_label == label) {
			vector<vector<int>> current_image = it->second;
			//at position (row, column) in the current image 2d vector, 
			if (current_image.at(row).at(col) == feature) {
				//cout << "for class " << current_label << " at position " << row << ", " << col << "matches feature" << endl;
				count_position_matches_feature++;
			}
		}
	}
	double feature_probability = (laplace_smoothing_factor + count_position_matches_feature) / (2 * laplace_smoothing_factor + count_label_occurrence);
	return feature_probability;
}

//create a map <int, vector<vector<double>>>
//vector is of size 28x28, each element in vector is the feature probability of that position
map<int, vector<vector<double>>> MapClassFeatureProbability(int feature, multimap <int, vector<vector<int>>> map_label_to_image) {
	cout << "entering method" << endl;
	map<int, vector<vector<double>>> map_feature_probability;
	
	for (int class_value = 0; class_value < 10; class_value++) {
		vector<vector<double>> vector_of_probabilities(28, vector<double>(28, 0.0));
		for (int i = 0; i < 28; i++) {
			for (int j = 0; j < 28; j++) {
				vector_of_probabilities[i][j] = FindFeatureProbabilityFromClass(i, j, class_value, feature, map_label_to_image);
				cout << vector_of_probabilities[i][j] << " ";
			}
			cout << endl;
		}
		map_feature_probability.insert(pair<int, vector<vector<double>>>(class_value, vector_of_probabilities));
	}
	
	for (map<int, vector<vector<double>>>::iterator it = map_feature_probability.begin(); it != map_feature_probability.end(); ++it) {
		int class_value = it->first;
		cout << class_value << endl;
		cout << "For label " << class_value << " we have this vector of probabilities";
		vector<vector<double>> vector_of_probabilities = it->second;
		for (int i = 0; i < vector_of_probabilities.size(); i++) {
			for (int j = 0; j < vector_of_probabilities[i].size(); j++) {
				cout << vector_of_probabilities[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}



	return map_feature_probability;
}