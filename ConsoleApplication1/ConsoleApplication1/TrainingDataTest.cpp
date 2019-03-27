#pragma once
#include "catch.h"
#include "TrainingData.h"
#include <iostream>

TEST_CASE("Find label prior probability calculations") {
	vector<int> labels_test;
	labels_test.push_back(0);
	labels_test.push_back(0);
	labels_test.push_back(0);
	labels_test.push_back(1);
	labels_test.push_back(1);

	REQUIRE(CalculateLabelPriorProbability(0, labels_test) == 0.6);
}