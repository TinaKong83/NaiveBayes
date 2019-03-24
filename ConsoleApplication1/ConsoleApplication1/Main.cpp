#include "ClassifyingData.h"
#include "ImageLabelsData.h"
#include "TrainingData.h"
#include "Evaluation.h"

using namespace std;

int main()
{
	std::cout << "Hello World!\n";
	string training_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\trainingimages";
	string training_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\traininglabels";

	string test_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testimages";
	string test_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testlabels";

	vector<vector<vector<int>>> vector_test_images = CreateVectorOfImages(test_images);
	vector<int> vector_test_labels = CreateVectorOfLabels(test_labels);

	vector<int> vector_training_labels = CreateVectorOfLabels(training_labels);
	//vector<vector<vector<int>>> vector_training_images = CreateVectorOfImages(training_images);

	multimap<int, vector<vector<int>>> map_labels_to_images = MapLabelsToImages(training_labels, training_images);

	map<int, vector<vector<double>>> map_class_feature_probability = MapClassFeatureProbability(map_labels_to_images);
	map<int, double> map_label_priors = MapLabelPriors(vector_training_labels);

	map<vector<vector<int>>, vector<double>> map_class_posterior_probabilities
		= MapClassPosteriorProbabilities(map_label_priors, map_class_feature_probability, vector_test_images);

	map<vector<vector<int>>, int> map_image_to_estimated_class = MapImageToEstimatedClass(map_class_posterior_probabilities);

	map<vector<vector<int>>, int> map_test_image_to_actual_class =
		MapTestImageToActualClass(vector_test_images, vector_test_labels);

	multimap<int, int> map_actual_class_to_estimated = MapActualClassToEstimated(map_image_to_estimated_class, map_test_image_to_actual_class);

	vector<vector<double>> generate_confusion_matrix = GenerateConfusionMatrix(map_actual_class_to_estimated);

	PrintConfusionMatrix(generate_confusion_matrix);

}

