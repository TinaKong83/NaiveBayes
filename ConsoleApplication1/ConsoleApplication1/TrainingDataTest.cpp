#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "TrainingData.h"
#include <iostream>
using namespace std;

TEST_CASE("Find label prior probability calculations") {
	//string labels_test_file = "C:\\Users\\kongt\\naivebayes-TinaKong83\\CreateLabelsTestCase.txt";
	vector<int> labels_test_file;
	labels_test_file.push_back(0);

	vector<double> vector_label_priors;
	vector_label_priors.push_back(0);

	REQUIRE(VectorLabelPriors(labels_test_file) == vector_label_priors);
}