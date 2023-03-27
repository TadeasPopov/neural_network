#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

#include "./HeaderFiles.hpp"
#include "./NeuralNetwork.hpp"

int main() {
	/* std::cout << "create nn\n";
	NeuralNetwork nn;
	std::cout << "add input\n";
	nn.Add( 2 );	// input
	std::cout << "add output\n";
	nn.Add( 1 );	// output
	std::cout << "print\n";
	nn.Print();

	// LOGICAL AND
	std::cout << "prepare train sets\n";
	std::vector<std::pair<std::vector<float>, std::vector<float>>> train_sets = {
		std::make_pair( std::vector<float>( { 0.f, 0.f } ), std::vector<float>( { 0.f } ) ),
		std::make_pair( std::vector<float>( { 0.f, 1.f } ), std::vector<float>( { 0.f } ) ),
		std::make_pair( std::vector<float>( { 1.f, 0.f } ), std::vector<float>( { 0.f } ) ),
		std::make_pair( std::vector<float>( { 1.f, 1.f } ), std::vector<float>( { 1.f } ) )
	};
	std::cout << "train\n";
	nn.Train(train_sets, 4, 64);
	std::cout << "print\n";
	nn.Print();

	// test
	for ( int i = 0; i < 4; i++ ) {
		std::vector<float> result = nn.Model( train_sets[i].first );

		if (result[0] == train_sets[i].second[0]) {
			std::cout << i << " OK\n";
		} else {
			std::cout << i << " ER: " << result[0] << " REAL: " << train_sets[i].second[0] << "\n";
		}
	}; */

	// ONE LINE
	/* std::cout << "create nn\n";
	NeuralNetwork nn;
	std::cout << "add input\n";
	nn.Add( 2 );
	std::cout << "add output\n";
	nn.Add( 1 );
	std::cout << "init train set\n";
	std::vector<std::pair<std::vector<float>, std::vector<float>>> train_sets;

	for ( int i = 0; i < 10000; i++ ) {
		float x = get_random_float(0.f, 256.f);
		float y = get_random_float(0.f, 770.f);
		float result1 = (3 * x + 2) > y;
		// float result2 = (3 * x + 2) == y;
		train_sets.push_back( std::make_pair( std::vector<float>( { x, y } ), std::vector<float>( { result1 } ) ) );
	}

	nn.Train(train_sets, 256, 64);

	cv::Mat image( 770, 256, CV_32FC3 );
	cv::line( image, cv::Point( 0, std::abs( 3 * 0 + 2 - 770 ) ), cv::Point( 256, std::abs( 3 * 256 + 2 - 770 ) ), { 1.f, 1.f, 1.f } );

	for ( int i = 0; i < 100; i++ ) {
		float x = get_random_float(0.f, 256.f);
		float y = get_random_float(0.f, 770.f);
		std::vector<float> test( { x, y } );
		float result1 = (3 * x + 2) > y;
		// float result2 = (3 * x + 2) == y;
		std::vector<float> result = nn.Model( test );

		if (result[0] == result1) {
			if (result1 == 1) {
				cv::circle( image, cv::Point( x, std::abs(y - 770) ), 3, { 0.f, 1.f, 0.f }, cv::FILLED );
			} else {
				cv::circle( image, cv::Point( x, std::abs(y - 770) ), 3, { 1.f, 0.f, 0.f }, cv::FILLED );
			}
			std::cout <<
				i << " OK " <<
				"\tx: " << x <<
				"\ty: " << y <<
				"\t>?: " << result1 <<
				"\tr: " << 3 * x + 2 <<
				"\n";
		} else {
			cv::circle( image, cv::Point( x, std::abs(y - 770) ), 3, { 0.f, 0.f, 1.f }, cv::FILLED );
			std::cout << i << " ER: " << result[0] << " REAL: " << result1 << " " << "\n";
		}
	}

	cv::namedWindow( "NN result", cv::WINDOW_AUTOSIZE );
	cv::imshow( "NN result", image ); */

	NeuralNetwork nn;
	nn.Add( 2 );
	nn.Add( 2 );
	nn.Add( 1 );
	std::vector<std::pair<std::vector<float>, std::vector<float>>> train_sets({
		std::make_pair( std::vector<float>( { 0, 0 } ), std::vector<float>( { 0 } ) ),
		std::make_pair( std::vector<float>( { 0, 1 } ), std::vector<float>( { 1 } ) ),
		std::make_pair( std::vector<float>( { 1, 0 } ), std::vector<float>( { 1 } ) ),
		std::make_pair( std::vector<float>( { 1, 1 } ), std::vector<float>( { 0 } ) )
	});

	// nn.Print();
	nn.Train( train_sets, 4, 100000 );
	std::cout << "\n--TEST--\n\n";

	for ( int i = 0; i < 4; i++ ) {
		std::vector<float> result = nn.Model( train_sets[i].first );

		if (
			(result[0] > 0.5f && train_sets[i].second[0] == 1) ||
			(result[0] <= 0.5f && train_sets[i].second[0] == 0)
		) {
			std::cout <<
				i << " OK " <<
				train_sets[i].first[0] <<
				" XOR " <<
				train_sets[i].first[1] << " = " <<
				train_sets[i].second[0] << "\n";
		} else {
			std::cout << i << " ER: " << result[0] << " REAL: " << train_sets[i].second[0] << " " << "\n";
		}
	}

	cv::waitKey( 0 );
}
