#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "ImageLabelsData.h";

TEST_CASE("Checks if vector of labels is created") {
	string labels_test_file = "C:\\Users\\kongt\\naivebayes-TinaKong83\\CreateLabelsTestCase.txt";
	vector<int> vector_labels;
	vector_labels.push_back(9);
	vector_labels.push_back(0);
	vector_labels.push_back(2);

	REQUIRE(CreateVectorOfLabels(labels_test_file) == vector_labels);
}



