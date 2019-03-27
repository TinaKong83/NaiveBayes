// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ImageLabelsData.h"
#include "TrainingData.h"
#include "ClassifyingData.h"
#include "Evaluation.h"

//Method that reads a file of integer labels. Push each integer into a vector of image labels
vector<int> CreateVectorOfLabels(string file_name) {
	vector<int> vector_labels;
	std::ifstream read_file;
	read_file.open(file_name);
	if (read_file.fail()) {
		std::cout << "File is invalid." << std::endl;
	} else {
		int label;
		//read file line by line, assuming each line is some integer
		while (read_file >> label) {
			vector_labels.push_back(label);
		}
	}
	read_file.close();
	return vector_labels;
}

//Method that reads a file of character images. Returns a list of 2d vector images with binary features
vector<vector<vector<int>>> CreateVectorOfImages(string file_name) {
	vector<vector<vector<int>>> vector_image_features;
	std::ifstream read_file;
	read_file.open(file_name);
	if (read_file.fail()) {
		std::cout << "File is invalid." << std::endl;
	} else {
		char image_char;
		while (!read_file.eof()) {
			vector<vector<int>> single_image;
			single_image.resize(kImageSize);
			for (int i = 0; i < kImageSize; i++) {
				single_image[i].resize(kImageSize + 1);
				for (int j = 0; j < kImageSize + 1; j++) {
					read_file.get(image_char);
					if (image_char == '\n') {
						continue;
					}
					if (image_char == ' ') {
						single_image[i][j] = 0;
					}
					else if (image_char == '#' || image_char == '+') {
						single_image[i][j] = 1;
					}
				}
			}
			vector_image_features.push_back(single_image);
		}
	}
	vector_image_features.pop_back();
	return vector_image_features;
}

int TakeCommandArgument(int argc, char *argv[]) {
	string training_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\trainingimages";
	string training_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\traininglabels";

	string test_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testimages";
	string test_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testlabels";

	if (argc == 4) {
		vector<vector<vector<int>>> vector_test_images = CreateVectorOfImages(test_images);
		vector<int> vector_test_labels = CreateVectorOfLabels(test_labels);
		vector<vector<vector<int>>> vector_training_images = CreateVectorOfImages(training_images);
		vector<int> vector_training_labels = CreateVectorOfLabels(training_labels);

		string black_features_file = argv[1];
		string white_features_file = argv[2];

		vector<vector<vector<double>>> vector_class_feature_probability =
			VectorClassFeatureProbability(vector_training_images, vector_training_labels, white_features_file, black_features_file);

		vector<double> vector_label_priors = VectorLabelPriors(vector_training_labels);
		string vector_label_priors_file = argv[3];
		WriteLabelPriorProbabilitiesToFile(vector_label_priors, vector_label_priors_file);
		map<vector<vector<int>>, vector<double>> map_class_posterior_probabilities
			= MapClassPosteriorProbabilities(vector_label_priors, vector_class_feature_probability, vector_test_images);

		map<vector<vector<int>>, int> map_image_to_estimated_class = MapImageToEstimatedClass(map_class_posterior_probabilities);
		map<vector<vector<int>>, int> map_test_image_to_actual_class =
			MapTestImageToActualClass(vector_test_images, vector_test_labels);
		multimap<int, int> map_actual_class_to_estimated = MapActualClassToEstimated(map_image_to_estimated_class, map_test_image_to_actual_class);
		vector<vector<double>> generate_confusion_matrix = PopulateConfusionMatrix(map_actual_class_to_estimated);
		PrintConfusionMatrix(generate_confusion_matrix);
	}
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
