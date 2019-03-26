#include "ClassifyingData.h"
#include "ImageLabelsData.h"
#include "TrainingData.h"
#include "Evaluation.h"

using namespace std;

int main()
{
	string training_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\trainingimages";
	string training_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\traininglabels";

	string test_images = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testimages";
	string test_labels = "C:\\Users\\kongt\\naivebayes-TinaKong83\\digitdata (1)\\testlabels";

	vector<vector<vector<int>>> vector_test_images = CreateVectorOfImages(test_images);
	vector<int> vector_test_labels = CreateVectorOfLabels(test_labels);
	vector<vector<vector<int>>> vector_training_images = CreateVectorOfImages(training_images);
	vector<int> vector_training_labels = CreateVectorOfLabels(training_labels);

	string black_features_file = "C:\\Users\\kongt\\naivebayes-TinaKong83\\WriteClassBlackFeatureProb.txt";
	string white_features_file = "C:\\Users\\kongt\\naivebayes-TinaKong83\\WriteClassWhiteFeatureProb.txt";

	vector<vector<vector<double>>> vector_class_feature_probability = 
		VectorClassFeatureProbability(vector_training_images, vector_training_labels, white_features_file, black_features_file);

	vector<double> vector_label_priors = VectorLabelPriors(vector_training_labels);
	string vector_label_priors_file = "C:\\Users\\kongt\\naivebayes-TinaKong83\\MapLabelPriors.txt";
	WriteLabelPriorProbabilitiesToFile(vector_label_priors, vector_label_priors_file);

	map<vector<vector<int>>, vector<double>> map_class_posterior_probabilities
		= MapClassPosteriorProbabilities(vector_label_priors, vector_class_feature_probability, vector_test_images);

	//confusion matrix stuff...can fix this
	map<vector<vector<int>>, int> map_image_to_estimated_class = MapImageToEstimatedClass(map_class_posterior_probabilities);

	map<vector<vector<int>>, int> map_test_image_to_actual_class =
		MapTestImageToActualClass(vector_test_images, vector_test_labels);
	
	multimap<int, int> map_actual_class_to_estimated = MapActualClassToEstimated(map_image_to_estimated_class, map_test_image_to_actual_class);

	vector<vector<double>> generate_confusion_matrix = GenerateConfusionMatrix(map_actual_class_to_estimated);

	PrintConfusionMatrix(generate_confusion_matrix);

}

