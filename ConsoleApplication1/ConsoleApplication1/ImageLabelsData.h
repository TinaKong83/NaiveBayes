#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;

class ImageLabelsData {
public:
	multimap<int, vector<vector<int>>> MapLabelsToImages(string labels_file, string images_file);
	//vector<int> vector_image_labels;
	//vector<vector<int>> single_image;

	vector<int> CreateVectorOfLabels(string file_name);
	vector<vector<vector<int>>> CreateVectorOfImages(string file_name);

	//list of 2d char vectors (each 2d vector is a single image)
	//single 3d vector represents list of all the images in a file
	//vector<vector<vector<int>>> vector_image_features;

	//vector<vector<vector<int>>> ConvertToBinaryFeature(vector<vector<vector<char>>> vector_image_characters);

};

