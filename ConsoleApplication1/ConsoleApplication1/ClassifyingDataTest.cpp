#pragma once
#include "catch.h"
#include "ClassifyingData.h"
#include <iostream>

TEST_CASE("Calculate posterior probabilities of an image") {
	vector<vector<double>> vector_feature_probabilities(28, vector<double>(28, 1.0));
	REQUIRE(CalculatePosteriorProbability(vector_feature_probabilities) == 0.0);
}

TEST_CASE("Estimate the class from posterior probabilities") {
	vector<double> vector_posterior_probabilities_per_class;
	vector_posterior_probabilities_per_class.push_back(-10);
	vector_posterior_probabilities_per_class.push_back(0.0);
	vector_posterior_probabilities_per_class.push_back(0.5);
	vector_posterior_probabilities_per_class.push_back(0.6);

	REQUIRE(EstimateImageClass(vector_posterior_probabilities_per_class) == 3);
}