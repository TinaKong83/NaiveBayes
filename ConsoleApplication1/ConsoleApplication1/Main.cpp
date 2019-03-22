#include "ClassifyingData.h"
#include "ImageLabelsData.h"
#include "TrainingData.h"

using namespace std;

int main()
{
	std::cout << "Hello World!\n";
	string training_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\trainingimages";
	string training_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\traininglabels";

	//CreateVectorOfLabels(training_labels);
	//CreateVectorOfImages(training_images); 

	vector<int> vector_training_labels = CreateVectorOfLabels(training_labels);
	//vector<vector<vector<int>>> vector_training_images = CreateVectorOfImages(training_images);

	multimap<int, vector<vector<int>>> map_labels_to_images = MapLabelsToImages(training_labels, training_images);

	//using class = 5 as an example
	//double label_prior_probability = CalculateLabelPriorProbability(5, vector_training_labels);
	
	//map<int, double> map_label_priors = MapLabelPriors(vector_training_labels);

	//double example_feature_probability = FindFeatureProbabilityFromClass(3, 2, 5, 1, map_labels_to_images);
	//cout << example_feature_probability;

	map<int, vector<vector<double>>> map_class_feature_probability = MapClassFeatureProbability(0, map_labels_to_images);
	map<int, double> map_label_priors = MapLabelPriors(vector_training_labels);

	/*vector<vector<double>> vector_feature_probabilities_one_class = map_class_feature_probability.begin()->second;
	double posterior_probability_one_class = CalculatePosteriorProbability(vector_feature_probabilities_one_class);
	cout << posterior_probability_one_class << endl;*/

	map<int, double> map_class_posterior_probabilities 
		= MapClassPosteriorProbabilities(map_label_priors, map_class_feature_probability);

	map<int, vector<vector<int>>> map_estimated_class_to_image 
		= MapEstimatedClassToImage(map_labels_to_images, map_class_posterior_probabilities);

}
