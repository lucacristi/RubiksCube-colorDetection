#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//draws a 3x3 grid of squares on the given image, modifying that image
void draw_rectangles(Mat initial_image, int x_coordinate, int y_coordinate, int length);

//calculates the center of each square and returns the points into a vector
vector <Point> get_squares_center(int x_coordinate, int y_coordinate, int length);

//gets the color of each square of a face and returns a 3x3 array
char* get_color(Mat initial_image, vector <Point> square_center);

//checks if the scanned colors are okay
bool check_colors_ok(Mat initial_image, char* face_colors, vector <Point> square_center, int sq_length);

//checks if a face was already scanned
bool check_face_duplicated(char* colors, vector <char*> colors_each_face, int face_number);

//show a face if it was already scanned
void show_duplicated_face(Mat initial_image, char* face_colors, vector <Point> square_center, int sq_length);

void order_faces();

void show_colors();
