#include <iostream>
#include "TrainingData.h"
using namespace std;

//use formula for esimating priors
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

map<int, double> MapLabelPriors(vector<int> training_labels) {
	map<int, double> map_label_priors;
	for (int i = 0; i < training_labels.size(); i++) {
		double prior_probability = CalculateLabelPriorProbability(training_labels.at(i), training_labels);
		map_label_priors.insert(pair<int, double>(training_labels.at(i), prior_probability));
	}
	return map_label_priors;
}

