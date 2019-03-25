#include <iostream>
#include"Evaluation.h"
using namespace std;

//Given all of your testing images: Now map the test image's actual class to its estimated class
multimap<int, int> MapActualClassToEstimated(map<vector<vector<int>>, int>& map_test_image_to_estimated_class,
	map<vector<vector<int>>, int>& map_test_image_to_actual_class) {

	multimap<int, int> map_actual_class_to_estimated;
	for (map<vector<vector<int>>, int>::iterator it = map_test_image_to_estimated_class.begin(); it != map_test_image_to_estimated_class.end(); ++it) {
		vector<vector<int>> current_image = it->first;
		int estimated_class = it->second;
		int actual_class = map_test_image_to_actual_class[current_image];
		map_actual_class_to_estimated.insert(pair<int, int>(actual_class, estimated_class));
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

vector<vector<double>> GenerateConfusionMatrix(multimap<int, int>& map_actual_class_to_estimated) {
	vector<vector<double>> confusion_matrix(10, vector<double>(10, 0.0));
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			//# images actually from class r?
			double count_images_actually_from_r = map_actual_class_to_estimated.count(r);
			confusion_matrix[r][c] = (double)CountImagesFromRowInCol(r, c, map_actual_class_to_estimated) / count_images_actually_from_r;
		}
	}
	return confusion_matrix;
}

void PrintConfusionMatrix(vector<vector<double>>& confusion_matrix) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%.2f  ", confusion_matrix[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}