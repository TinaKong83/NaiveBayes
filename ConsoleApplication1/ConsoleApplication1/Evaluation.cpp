#include <iostream>
#include "Evaluation.h"

//Given all of your testing images: Now map the test image's actual class to its estimated class
multimap<int, int> MapActualClassToEstimated(map<vector<vector<int>>, int>& map_test_image_to_estimated_class,
	map<vector<vector<int>>, int>& map_test_image_to_actual_class) {
	multimap<int, int> map_actual_class_to_estimated;
	for (map<vector<vector<int>>, int>::iterator it = map_test_image_to_estimated_class.begin(); it != map_test_image_to_estimated_class.end(); ++it) {
		vector<vector<int>> current_image = it->first;
		int estimated_class = it->second;
		int actual_class = map_test_image_to_actual_class[current_image];
		map_actual_class_to_estimated.insert(std::pair<int, int>(actual_class, estimated_class));
	}
	return map_actual_class_to_estimated;
}

int CountImagesFromRowInCol(int row, int col, multimap<int, int>& map_actual_class_to_estimated) {
	int count_num_images_from_r_estimated_in_c = 0;
	for (multimap<int, int>::iterator it = map_actual_class_to_estimated.begin(); it != map_actual_class_to_estimated.end(); ++it) {
		int actual_class = it->first;
		int estimated_class = it->second;
		if (actual_class == row && estimated_class == col) {
			count_num_images_from_r_estimated_in_c++;
		}
	}
	return count_num_images_from_r_estimated_in_c;
}

vector<vector<double>> PopulateConfusionMatrix(multimap<int, int>& map_actual_class_to_estimated) {
	vector<vector<double>> confusion_matrix(10, vector<double>(kMatrixSize, 0.0));
	for (int r = 0; r < kMatrixSize; r++) {
		for (int c = 0; c < kMatrixSize; c++) {
			double count_images_actually_from_r = map_actual_class_to_estimated.count(r);
			confusion_matrix[r][c] = (double) CountImagesFromRowInCol(r, c, map_actual_class_to_estimated) / count_images_actually_from_r;
		}
	}
	return confusion_matrix;
}

void PrintConfusionMatrix(vector<vector<double>>& confusion_matrix) {
	for (int i = 0; i < kMatrixSize; i++) {
		for (int j = 0; j < kMatrixSize; j++) {
			printf("%.2f  ", confusion_matrix[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}