// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ImageLabelsData.h"
using namespace std;

//method that reads a file of integer labels. push each integer into a vector of image labels
vector<int> CreateVectorOfLabels(string file_name) {
	vector<int> vector_labels;
	ifstream read_file;
	read_file.open(file_name);
	if (read_file.fail()) {
		cout << "File is invalid." << endl;
	} else {
		int label;
		//read file line by line, assuming each line is some integer
		while (read_file >> label) {
			vector_labels.push_back(label);
			//cout << label << endl;
		}
	}
	read_file.close();
	return vector_labels;
}

//method that reads a file of character images. 
//returns a list of 2d vector images w/ binary features
vector<vector<vector<int>>> CreateVectorOfImages(string file_name) {
	vector<vector<vector<int>>> vector_image_features;
	ifstream read_file;
	read_file.open(file_name);
	if (read_file.fail()) {
		cout << "File is invalid." << endl;
	} else {
		char image_char;
		while (!read_file.eof()) {
			vector<vector<int>> single_image;
			single_image.resize(28);
			for (int i = 0; i < 28; i++) {
				single_image[i].resize(29);
				for (int j = 0; j < 29; j++) {
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

	//prints out the images
	/*for (int i = 0; i < vector_image_features.size(); i++) {
		for (int j = 0; j < vector_image_features[i].size(); j++) {
			for (int k = 0; k < vector_image_features[i][j].size(); k++) {
				cout << vector_image_features[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}*/
	return vector_image_features;
}

//multimap that maps a number-image in an image file to its class label
//read the image file 
//key: class (as an int)
//value: number-image as a (2d vector of chars)

multimap<int, vector<vector<int>>> MapLabelsToImages(string labels_file, string images_file) {
	multimap <int, vector<vector<int>>> map_label_to_image;
	vector<int> vector_of_labels = CreateVectorOfLabels(labels_file);
	vector<vector<vector<int>>> vector_of_images = CreateVectorOfImages(images_file);
	for (int i = 0; i < vector_of_labels.size(); i++) {
		map_label_to_image.insert(pair<int, vector<vector<int>>>(vector_of_labels.at(i), vector_of_images.at(i)));
	}
	return map_label_to_image;
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
