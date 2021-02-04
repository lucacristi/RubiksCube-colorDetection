#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "GetColors.h"

using namespace std;
using namespace cv;

vector <char*> colors_each_face;

//function used to get the colors from the generated dll
extern "C" char __declspec(dllexport) __stdcall get_cube(int i, int j) {
	return colors_each_face[i][j];
}

extern "C" int __declspec(dllexport) __stdcall main() {
	char *face_colors[9];

	int face_number = 0;
	int pressedKey = 0;

	// x and y coordinates for the first square of the grid and the length of a square
	int x_coord_pt1 = 7;
	int y_coord_pt1 = 7;
	int length = 60;

	//a matrix that will contain all the pixels of a frame
	Mat frame;				

	//an object used to open the webcam
	VideoCapture video(0);														

	//a vector of points containing the center of each square
	vector<Point> squares_center;												
	squares_center = get_squares_center(x_coord_pt1, y_coord_pt1, length);

	for (int i = 0; i < 6; i++) {
		face_colors[i] = new char[9];
		colors_each_face.push_back(face_colors[i]);
	}

	if (!video.isOpened())
		return -1;

	while (1) {

		video.read(frame);			
		//flip the obtained frame horizontally to get rid of the mirro effect
		flip(frame, frame, 1);	
		//draw a grid of squares
		draw_rectangles(frame, x_coord_pt1, y_coord_pt1, length);				
		imshow("webCAM", frame);

		pressedKey = waitKey(33);												//"read" the key pressed
		if (pressedKey == 27) {													// 27 = 'Esc' key -  to stop	
			destroyAllWindows();
			break;
		}

		if (pressedKey == -1) {													//normally - 1 returned, so just continue to "read" frames
			continue;
		}

		if (pressedKey == 121) {													// 121 = 'y' key - in order to scan the colors

			char *color = get_color(frame, squares_center);

			if (check_colors_ok(frame, color, squares_center, length)) {			//check if the scanned colors are okay

				if (check_face_duplicated(color, colors_each_face, face_number))	//if the colors are okay, check if these colors are already on another face
					show_duplicated_face(frame, color, squares_center, length);		//and if they are on another face, show that face

				else {																//if is not duplicated
					for (int i = 0; i < 9; i++)
						colors_each_face[face_number][i] = *(color + i);			//save the colors in the vector containing all faces
					if (face_number == 5) {											// exit when all the faces were scanned	
						destroyAllWindows();
						break;
					}
					face_number++;													//incremnt the nr of the face when all the colors were corectly scanned
				}
			}
		}
	}

	order_faces();
	show_colors();
}
