#include <iostream>
#include"Evaluation.h"
using namespace std;

vector<vector<double>> GenerateConfusionMatrix(map<vector<vector<int>>, int> map_image_to_estimated_class, map<vector<vector<int>>, int> map_test_image_to_actual_class) {
	
	for (map<vector<vector<int>>, int>::iterator it = map_image_to_estimated_class.begin(); it != map_image_to_estimated_class.end(); ++it) {
		vector<vector<int>> current_image = it->first;
		int estimated_class = it->second;
		int actual_class = map_test_image_to_actual_class[current_image];
	}
	
	
	
	/*vector<vector<double>> confusion_matrix(10, vector<double>(10, 0.0));
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {

			//int count_estimated_images_of_class_r = 

			confusion_matrix[r][c] = 0; //FIX THIS

		}
	}*/

}


//e.g. (r, c) = (3, 1)
//num of images actually from class 3, but predicted to be in class 1


//create a multimap: estimated class to actual class. map is the size of all testing images..
//e.g. (1, 9) (5, 0) (3, 2) (3, 5) (0, 1) (9, 9) (1, 3) (2, 3) (1, 3)
//method: CountImagesFromRPredictedToBeInC(int row, int col, map<int, int> estimate_to_actual_class);
// int count_num_images_from_r_estimated_in_c;
//for (loop through map.....) {
//   if (it->second = row) {
//      if (it->second = col) {
//         count_num_images_from_r_estimated_in_c++;
//      }
//   }
//}