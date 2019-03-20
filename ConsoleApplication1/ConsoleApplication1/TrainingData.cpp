#include <iostream>
#include "TrainingData.h"
using namespace std;

//use formula for esimating priors
double TrainingData::CalculateLabelPriorProbability(int label, vector<int> training_labels) {
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
map<int, double> TrainingData::MapLabelPriors(vector<int> training_labels) {
	map<int, double> map_label_priors;
	for (int i = 0; i < 10; i++) {
		double prior_probability = CalculateLabelPriorProbability(i, training_labels);
		map_label_priors.insert(pair<int, double>(i, prior_probability));
	}
	return map_label_priors;
}

//Find the probability that a feature is some value in your specified position, 
//given an image that is a certain label
//Use formula: P(Fi,j =f|class=c)= (k + # of times F(i,j) =f when class=c) / (2k + Total number of training examples where class = c)
//multimap <int, vector<vector<int>>> map_label_to_image;
double TrainingData::FindFeatureProbabilityFromClass(int row, int col, int label, int feature, 
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
				count_position_matches_feature++;
			}
		}
	}
	double feature_probability = (laplace_smoothing_factor + count_position_matches_feature) / (2 * laplace_smoothing_factor + count_label_occurrence);
	return feature_probability;
}

