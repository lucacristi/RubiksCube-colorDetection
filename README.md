# RubiksCube-colorDetection
-- The project was done in 2019 --

## Objective
- The aim of this application is to detect the colors of a Rubik's cube with the help of the user's webcam.  
- The implementation is done using C++ OpenCV libraries.  
- The data is saved into a .dll file, which is later used in Unity ([Rubik's Cube - Unity](https://github.com/lucacristi/RubiksCube-cubeRenderAndSolving.git)).  
 
Implementation of the Application's objective is illustrated in the following image.
<p align="center">
  <img width="500" height="300" src="https://user-images.githubusercontent.com/54026035/106899295-1aedb380-66ed-11eb-9507-c6c0c460a3bd.png" alt="Colors Detection Diagram">
  <br clear="center"/>
      Application Objectives
</p>

## Application Flow
<details>
<summary>Application Flow</summary>
         
The implementation steps of the application are:
* Start a video stream capture using the webcam;  
* Display of the colors’ detection spots;  
* Color scanning by double-checking;  
* Transmit colors to Unity;  

A simple Flow chart of the app can be seen in the following image.
<p align="center">
  <img width="500" height="700" src="https://user-images.githubusercontent.com/54026035/106904934-a9fdca00-66f3-11eb-8015-6d2adacb174b.png" alt="Colors Detection Flow">
  <br clear="center"/>
      Flows chart of the colors' detection
</p>

1. **Grid drawing**  
A grid is a bunch of adjacent squares next to each other to take a shape like a cube’s face. The grid consists of 9 squares spaced a little apart. Grid drawing is performed by calling the *draw_rectangles()* function.
<p align="center">
  <img width="450" height="300" src="https://user-images.githubusercontent.com/54026035/106907544-45903a00-66f6-11eb-941b-1b02fc856d4f.JPG" alt="Grid squares">
  <br clear="center"/>
      Squares' grid drawn upon a frame
</p>

2. **Getting colors**  
After the frame containing the grid is displayed, the user must match his cube with the grid. It is expected that 'y' key to be pressed for colors to be detected. After 'y' is pressed, *get_color()* function is called, passing to it the frame and the centers of all the grid’s squares.  
The central pixel of each square and its neighbours are stored in order to determin the color.
<p align="center">
  <img width="450" height="300" src="https://user-images.githubusercontent.com/54026035/106909663-69547f80-66f8-11eb-8184-29d59db0c479.png" alt="Grid pixels">
  <br clear="center"/>
      Squares' grid and pixels of interest 
</p>

Following HSV values were used for descriminating between the colors.  
Color    | HUE               | SATURATION   | VALUE
-------- | ------------------| -------------| -------------
Green    | 59 – 84           |  80 – 170    |  75 – 155
Blue     | 102 – 111         |  130 – 195   |  80 – 154
Red      | 1 – 6 & 167 – 180 |  83 – 155    |  56 – 101
Orange   | 7 – 25            |  166 – 194   |  142 – 203
Yellow   | 30 – 57           |  102 – 115   |  174 – 216
White    | None of the above |  68 – 97     |  181 – 220

3. **Scan accuracy**  
After the colors’ have been saved, a copy of the cube scanned face is displayed next to the original grid and the user is asked for the correctness of the scan. The copy of the scanned face is similar to the grid, only this time, the squares in the grid are colored. Verification of scan accuracy is performed by the *check_colors_ok()* function, which waits for confirmation from the user.
- 'y' key, if the scan is alright;
- 'n' key, otherwise. (In this case, the user will need to scan again)

<p align="center">
  <img width="450" height="300" src="https://user-images.githubusercontent.com/54026035/106912799-48d9f480-66fb-11eb-943e-50e2ad9bf5e1.png" alt="Detected colors">
  <br clear="center"/>
      Detected colors shown in a colorful grid 
</p>

4. **Face duplication**  
Even if the user will type "n", after some tries eventually, it will be able to correctly scan the colors. After it scans the colors successfully, the problem is whether the scanned face had previously been scanned. To get rid of this problem, *check_face_duplicated()* has been implemented.

<p align="center">
  <img width="450" height="300" src="https://user-images.githubusercontent.com/54026035/106921905-61024180-6704-11eb-8d6e-6c679933ae37.png" alt="Face duplication">
  <br clear="center"/>
      Face duplication window
</p>
</details>

## How to "install" the app
**You need to have OpenCV installed**  
- clone or download the project;  
- in Visual Studio: File -> Open -> Project and select "ColorDetection.sln" from above downloaded files;  
- open Solution Explorer window -> Alt + Enter (project Property Pages should pop-up);  
- on the left navigation tree -> Configuration Properties -> General tab; 
- check that "Target Extension" = ".dll";
- run the app as usually.  

A "ColorDetection.dll" file will be created under "x64" folder.  

## How to use the app
In order to application work properly, a very important thing to be mention is how the cube will be shown to the webcam. A face of the cube with any color must be shown to the webcam, but considering the following orientations:
-	The ![#red](https://via.placeholder.com/15/ff0000/000000?text=+) `#red_face` will be scanned with the ![#white](https://via.placeholder.com/15/ffffff/000000?text=+) `#white_face` up;
-	The ![#white](https://via.placeholder.com/15/ffffff/000000?text=+) `#white_face` will be scanned with the ![#orange](https://via.placeholder.com/15/ff7700/000000?text=+) `#orange_face` up;
-	The ![#blue](https://via.placeholder.com/15/0000ff/000000?text=+) `#blue_face` will be scanned with the ![#white](https://via.placeholder.com/15/ffffff/000000?text=+) `#white_face` up;
-	The ![#yellow](https://via.placeholder.com/15/ffff00/000000?text=+) `#yellow_face` will be scanned with the ![#red](https://via.placeholder.com/15/ff0000/000000?text=+) `#red_face` up;
-	The ![#green](https://via.placeholder.com/15/00ff00/000000?text=+) `#green_face` will be scanned with the ![#white](https://via.placeholder.com/15/ffffff/000000?text=+) `#white_face` up;
-	The ![#orange](https://via.placeholder.com/15/ff7700/000000?text=+) `#orange_face` will be scanned with the ![#white](https://via.placeholder.com/15/ffffff/000000?text=+) `#white_face` up.

## Development Directions
 - [ ] ask user to scan each color individually, in order to adept HSV values based on user input;
 - [ ] extract pixels from a bigger Region Of Interest for an accurate color scanning; 
 - [ ] extend application for other types of cubes/puzzles;
 
 ## License & Copyright
 All tools and libraries used are open-source and can be used by anyone.  
 Feel free to use the code and don't forget to help others, too.
