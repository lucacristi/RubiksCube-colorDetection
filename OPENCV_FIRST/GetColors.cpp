#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "GetColors.h"

using namespace std;
using namespace cv;

extern vector <char*> colors_each_face;


void draw_rectangles(Mat initial_image, int x_coordinate, int y_coordinate, int length) {
	// gap is the distance between 2 squares
	int gap = 4;

	//choose 'a' as a reference point
	Point a = Point(x_coordinate, y_coordinate);					

	//draw the 3x3 grid with gaps between squares
	rectangle(initial_image, a, Point(a.x + length, a.y + length), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + length + gap, y_coordinate), Point(a.x + 2 * length + gap, a.y + length), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + 2 * length + 2 * gap, y_coordinate), Point(a.x + 2 * gap + 3 * length, a.y + length), Scalar(0, 255, 0));

	rectangle(initial_image, Point(a.x, a.y + length + gap), Point(a.x + length, a.y + 2 * length + gap), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + length + gap, a.y + length + gap), Point(a.x + gap + 2 * length, a.y + 2 * length + gap), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + 2 * length + 2 * gap, a.y + length + gap), Point(a.x + 3 * length + 2 * gap, a.y + 2 * length + gap), Scalar(0, 255, 0));

	rectangle(initial_image, Point(a.x, a.y + 2 * length + 2 * gap), Point(a.x + length, a.y + 3 * length + 2 * gap), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + length + gap, a.y + 2 * length + 2 * gap), Point(a.x + gap + 2 * length, a.y + 3 * length + 2 * gap), Scalar(0, 255, 0));
	rectangle(initial_image, Point(a.x + 2 * length + 2 * gap, a.y + 2 * length + 2 * gap), Point(a.x + 2 * gap + 3 * length, a.y + 3 * length + 2 * gap), Scalar(0, 255, 0));

}

vector <Point> get_squares_center(int x_coordinate, int y_coordinate, int length) {
	//vector that keeps the center points of each square
	vector <Point> square_center;						

	//gap between 2 squares of the grid
	int gap = 4;																	

	//center point of each square in order to extract later the hsv and rgb values
	Point sq1_center = Point(x_coordinate + (length / 2), y_coordinate + (length / 2));
	Point sq2_center = Point(sq1_center.x + length, sq1_center.y);
	Point sq3_center = Point(sq2_center.x + length, sq1_center.y);

	Point sq4_center = Point(x_coordinate + (length / 2), y_coordinate + length + gap + (length / 2));
	Point sq5_center = Point(sq4_center.x + length, sq4_center.y);
	Point sq6_center = Point(sq5_center.x + length, sq5_center.y);

	Point sq7_center = Point(x_coordinate + (length / 2), y_coordinate + 2 * length + 2 * gap + (length / 2));
	Point sq8_center = Point(sq7_center.x + length, sq7_center.y);
	Point sq9_center = Point(sq8_center.x + length, sq8_center.y);

	square_center.push_back(sq1_center);
	square_center.push_back(sq2_center);
	square_center.push_back(sq3_center);
	square_center.push_back(sq4_center);			
	square_center.push_back(sq5_center);
	square_center.push_back(sq6_center);
	square_center.push_back(sq7_center);
	square_center.push_back(sq8_center);
	square_center.push_back(sq9_center);

	return square_center;
}

char* get_color(Mat initial_image, vector<Point> square_center) {
	//a copy of the initial image used when change the color spaces
	Mat cpy_initial_image = initial_image.clone();							

	//aux mat that keeps the HSV converted image
	Mat HSV = Mat(initial_image.rows, initial_image.cols, initial_image.depth());	

	//aux mat that keeps the RGB converted image
	Mat RGB = Mat(cpy_initial_image.rows, cpy_initial_image.cols, cpy_initial_image.depth());	

	//vector that will host the R, G and B components from the center of a square
	Vec3b rgb[9];			

	//vector that will host the H, S and V components from the center of a square
	Vec3b hsv[9];																				


	//conversion of the initial image in HSV
	cvtColor(initial_image, HSV, COLOR_BGR2HSV);		

	//convertion of the initial image in RGB
	cvtColor(cpy_initial_image, RGB, COLOR_BGR2RGB);											

	GaussianBlur(HSV, HSV, Size(5, 5), 0);									
	GaussianBlur(RGB, RGB, Size(5, 5), 0);									

	char* face_aux = new char[9];											

	//looping through the squares of the grid
	for (int i = 0; i < 9; i++) {											

		//getting r - values in 1-st iteration, g - values in 2-nd iteration, b - values in 3-rd iteration 
		for (int k = 0; k < 3; k++) {
			// extracting the rgb values from the center of each square. Aux hold the sumt of 5 pixels
			int aux = (RGB.at<Vec3b>(square_center[i])[k] + RGB.at<Vec3b>(Point(square_center[i].x + 1, square_center[i].y))[k] +
				RGB.at<Vec3b>(Point(square_center[i].x - 1, square_center[i].y))[k] + RGB.at<Vec3b>(Point(square_center[i].x, square_center[i].y + 1))[k] +
				RGB.at<Vec3b>(Point(square_center[i].x, square_center[i].y - 1))[k]);		
			rgb[i][k] = aux / 5;															
		}
		// extracting the hue value from the center of each square
		int aux = (HSV.at<Vec3b>(square_center[i])[0] + HSV.at<Vec3b>(Point(square_center[i].x + 1, square_center[i].y))[0] +
			HSV.at<Vec3b>(Point(square_center[i].x - 1, square_center[i].y))[0] + HSV.at<Vec3b>(Point(square_center[i].x, square_center[i].y + 1))[0] +
			HSV.at<Vec3b>(Point(square_center[i].x, square_center[i].y - 1))[0]);		

		hsv[i][0] = aux / 5;

	}

	cout << endl << " Print HSV values" << endl;
	for (int i = 0; i < 9; i++) {
		int k = 0;
		cout << endl << "Print CUBLET " << i + 1 << ":\tH: " << (int)hsv[i][k] << ", S: " << (int)hsv[i][k + 1] << ", V: " << (int)hsv[i][k + 2] << endl;

	}

	cout << endl << endl << " Print RGB values" << endl;
	for (int i = 0; i < 9; i++) {
		int k = 0;
		cout << endl << "Print CUBLET " << i + 1 << ":\tR: " << (int)rgb[i][k] << ", G: " << (int)rgb[i][k + 1] << ", B: " << (int)rgb[i][k + 2] << endl;
	}

	for (int j = 0; j < 9; j++) {

		int hue_value = hsv[j][0];
		int r_value = rgb[j][0];
		int g_value = rgb[j][1];
		int b_value = rgb[j][2];

		//if hue between 58 & 80 => G.reen
		if ((hue_value > 58) && (hue_value < 85)) {						
			*(face_aux + j) = 'g';

		}

		//if hue between 102 & 111 => B.lue
		else if ((hue_value > 102) && (hue_value < 111)) {				
			*(face_aux + j) = 'b';
		}

		//if hue between given values => R.ed
		else if (((hue_value > -1) && (hue_value < 7)) || ((hue_value > 167) && (hue_value < 180))) {		
			*(face_aux + j) = 'r';
		}

		//if hue between 6 & 25 => O.range
		else if ((hue_value > 6) && (hue_value < 25)) {					
			*(face_aux + j) = 'o';
		}
			   
		//if hue between 30 & 57 => Y.ellow
		else if ((hue_value > 30) && (hue_value < 57)) {					
			*(face_aux + j) = 'y';
		}

		//if it's not match until here => W.hite
		else													
			*(face_aux + j) = 'w';
	}

	return face_aux;
}

bool check_colors_ok(Mat initial_image, char* face_colors, vector <Point> square_center, int sq_length) {
	//a copy of the initial image in order to keep the original unchanged
	Mat img_with_text = initial_image.clone();								
	int gap = 4;

	//looping over the face_colors in order to sketch the face
	for (int j = 0; j < 9; j++) {											
		if (*(face_colors + j) == 'r')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 0, 255), -1);

		if (*(face_colors + j) == 'g')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 255, 0), -1);

		if (*(face_colors + j) == 'b')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(255, 0, 0), -1);

		if (*(face_colors + j) == 'w')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(255, 255, 255), -1);

		if (*(face_colors + j) == 'o')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(45, 130, 235), -1);

		if (*(face_colors + j) == 'y')
			rectangle(img_with_text, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 255, 255), -1);
	}

	// after we printed the squares of the face, we ask the user if the color are okay scanned
	putText(img_with_text, "Are the colors scanned okay? [Y/N]", Point(10, 450), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 4, LINE_AA);

	//show the user the resulted image = sketched squares + text
	imshow("webCAM2", img_with_text);								
	
	while (1) {
		int pressedKey = waitKey(33);								//"read" the key pressed
		if (pressedKey == 27) {										// 27 = 'Esc' key -  to stop
			break;
		}

		if (pressedKey == -1) {										//normally -1 returned, so just continue to "read" the pressed key
			continue;
		}

		if (pressedKey == 121) {									// 121 = 'y' key - which means that the colors were scanned correctly 
			destroyWindow("webCAM2");								// we don't want the image anymore
			return true;											// return true = the colors were okay scanned
		}
		if (pressedKey == 110) {									// 110 = 'n' key - which means that the colors weren't scanned correctly
			destroyWindow("webCAM2");								//destroy the image because we don't want it anymore
			return false;											//return false = the colors were not scanned correctly 
		}
	}

}


bool check_face_duplicated(char* colors, vector <char*> colors_each_face, int face_number) {

	for (int i = 0; i < (face_number); i++) {									//we loop over all the faces 'till the curent face
		if (colors_each_face[i][4] == *(colors + 4))							//if the center of a face is equal with the the center of the actual scanned colors
			return true;														//it means that that face was already scanned - it's duplicated
	}
	return false;																//otherwise, the face is not duplicated
}


void show_duplicated_face(Mat initial_image, char* face_colors, vector <Point> square_center, int sq_length) {
	//a copy of the initial image, in order to keep it unchanged
	Mat img_duplicated = initial_image.clone();												
	int gap = 4;

	//a loop over all the squares of a face in order to sketch them
	for (int j = 0; j < 9; j++) {												
		if (*(face_colors + j) == 'r')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 0, 255), -1);

		if (*(face_colors + j) == 'g')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 255, 0), -1);

		if (*(face_colors + j) == 'b')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(255, 0, 0), -1);

		if (*(face_colors + j) == 'w')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(255, 255, 255), -1);

		if (*(face_colors + j) == 'o')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(45, 130, 235), -1);

		if (*(face_colors + j) == 'y')
			rectangle(img_duplicated, (square_center[j] - Point(sq_length / 2, sq_length / 2) + Point(400, 0)), (square_center[j] + Point(sq_length / 2 - gap, sq_length / 2) + Point(400, 0)), Scalar(0, 255, 255), -1);
	}

	//after we sketched all the squares with their colors, we print the message on the same image
	putText(img_duplicated, "This face is duplicated. Press any key...", Point(10, 450), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 4, LINE_AA);

	//we show the resultated image = the squares + text
	imshow("Duplicated Image", img_duplicated);					

	//we wait for 6 second or a key from the user
	waitKey(6 * 1000);				

	//we destroy the image if the time passed or if a key was pressed
	destroyWindow("Duplicated Image");									
}

void order_faces() {
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			if (colors_each_face[i][4] != 'r') {
				for (int j = i + 1; j < 6; j++) {
					if (colors_each_face[j][4] == 'r') {
						char* swap_faces = colors_each_face[i];
						colors_each_face[i] = colors_each_face[j];
						colors_each_face[j] = swap_faces;
						break;
					}
				}
			}
		}

		if (i == 1) {
			if (colors_each_face[i][4] != 'w') {
				for (int j = i + 1; j < 6; j++) {
					if (colors_each_face[j][4] == 'w') {
						char* swap_faces = colors_each_face[i];
						colors_each_face[i] = colors_each_face[j];
						colors_each_face[j] = swap_faces;
						break;
					}
				}
			}
		}

		if (i == 2) {
			if (colors_each_face[i][4] != 'b') {
				for (int j = i + 1; j < 6; j++) {
					if (colors_each_face[j][4] == 'b') {
						char* swap_faces = colors_each_face[i];
						colors_each_face[i] = colors_each_face[j];
						colors_each_face[j] = swap_faces;
						break;
					}
				}
			}
		}

		if (i == 3) {
			if (colors_each_face[i][4] != 'y') {
				for (int j = i + 1; j < 6; j++) {
					if (colors_each_face[j][4] == 'y') {
						char* swap_faces = colors_each_face[i];
						colors_each_face[i] = colors_each_face[j];
						colors_each_face[j] = swap_faces;
						break;
					}
				}
			}
		}

		if (i == 4) {
			if (colors_each_face[i][4] != 'g') {
				for (int j = i + 1; j < 6; j++) {
					if (colors_each_face[j][4] == 'g') {
						char* swap_faces = colors_each_face[i];
						colors_each_face[i] = colors_each_face[j];
						colors_each_face[j] = swap_faces;
						break;
					}
				}
			}
		}

	}
}

void show_colors() {
	cout << "\nI will show the colors: " << endl;
	for (int i = 0; i < 6; i++) {
		cout << "Face number: " << i + 1 << endl;
		for (int j = 0; j < 9; j++) {
			if (j == 4) {
				cout << "\t" << colors_each_face[i][j] << "\t";
				continue;
			}
			cout << colors_each_face[i][j];
			cout << " ";
		}
		cout << endl;
	}
}