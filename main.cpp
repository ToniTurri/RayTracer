#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <cmath>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include "triangle.h"
#include "source.h"
#include "vector.h"
#include "sphere.h"
#include "camera.h"
#include "object.h"
#include "plane.h"
#include "light.h"
#include "color.h"
#include "bmp.h"
#include "ray.h"

int winningObjectIndex(const std::vector<double> objectIntersections) {
	//return the index of the winning intersection
		int minIndexVal = 0;

	if (objectIntersections.size() == 0) { return -1; }
	else if (objectIntersections.size() == 1) {
		if (objectIntersections.at(0) > 0) { return 0; }  //if > 0, 0 is the min index
		else { return -1; }  //intersection is neg
	}
	else {
		//more than one intersection
		double max = 0;
		for (int i = 0; i < objectIntersections.size(); i++) {
			if (max < objectIntersections.at(i))
				max = objectIntersections.at(i);
		}
		//starting from max value find the minimum position
		if (max > 0) {
			for (int i = 0; i < objectIntersections.size(); i++) {
				if (objectIntersections.at(i) > 0
					&& objectIntersections.at(i) <= max) {
					max = objectIntersections.at(i);
					minIndexVal = i;
				}
			}
			return minIndexVal;
		}
		else { return -1; }  //all the intersections were neg
	}
}

Color getColorAt(Vector intersectionPos, Vector intersectingRayDir, std::vector<Object*> sceneObjects,
	int indexOfWinningObject, std::vector<Source*>lightSources, double accuracy, unsigned char ambientLight) {

	Color winningColor = sceneObjects.at(indexOfWinningObject)->getColor();
	Vector winningNormal = sceneObjects.at(indexOfWinningObject)->normalAt(intersectionPos);
	Color finalColor = winningColor * ambientLight;
	
	for (int lightIndex = 0; lightIndex < lightSources.size(); lightIndex++) {
		Vector lightDir = (lightSources.at(lightIndex)->lightPosition() + (intersectionPos.negative())).normalize();

		double cosine = winningNormal.dot(lightDir);

		if (cosine > 0) {
			// test shades!
			bool shadow = false;
			Vector lightDist = (lightSources.at(lightIndex)->lightPosition() + (intersectionPos.negative())).normalize();
			double lightDistMag = lightDist.mag();

			Vector rayDir = (lightSources.at(lightIndex)->lightPosition() + intersectionPos.negative()).normalize();
			Ray shadowRay(intersectionPos, rayDir);

			std::vector<double> intersections2;

			for (int objectIndex = 0; objectIndex < sceneObjects.size() && shadow == false; objectIndex++) {
				intersections2.push_back(sceneObjects.at(objectIndex)->findIntersection(shadowRay));
			}

			for (int c = 0; c < intersections2.size(); c++) {
				if (intersections2.at(c) > accuracy){
					if (intersections2.at(c) <= lightDistMag) {
						shadow = true;
					}
				}
				break;
			}

			if (!shadow) finalColor = finalColor + (winningColor * lightSources.at(lightIndex)->lightColor()) * cosine;
		}
	}

	return finalColor;
}

static const int WIDTH = 640;
static const int HEIGHT = 480;

int main(int argc, char **argv) {
	std::cout << "rendering..." << std::endl;
	
	clock_t t1, t2;
	t1 = clock();

	BMP Image(WIDTH, HEIGHT);
	double aspectRatio = (double) WIDTH / (double) HEIGHT;
	unsigned char ambientLight = 255; //
	double accuracy = 0.00000001;

	Vector X = Vector::X();
	Vector Y = Vector::Y();
	Vector Z = Vector::Z();
	Vector O = Vector::zero();

	Vector v0(-1, -1, 0);
	Vector v1(1, -1, 0);
	Vector v2(0, 1, 0);

	Vector camPos(3, 1.4, -4);
	Vector looking_at(0, 0, 0);
	Vector difference(camPos - looking_at);
	Vector camDir = difference.negative().normalize();
	Vector camRight = Y.cross(camDir).normalize();
	Vector camDown = camRight.cross(camDir);
	Camera scene_cam(camPos, camDir, camRight, camDown);

	Color purple(165, 143, 181, 0);
	Color darkPurple(106, 72, 133, 0);
	Color tile(1, 1, 1, 2);
	Color black(0, 0, 0, 0);
	Color white(1, 1, 1, 0);

	// Light sources
	Vector lightPos(1, 7, -3);
	Light sceneLight(lightPos, white);
	std::vector<Source*> lightSources;
	lightSources.push_back(dynamic_cast<Source*>(&sceneLight));

	// Scene objects
	Sphere sceneSphere(O, 1, purple);
	Plane scenePlane(Y, -1, darkPurple);
	//Triangle sceneTriangle(Y, purple, v0, v1, v2);
	std::vector<Object*> sceneObjects;

	//sceneObjects.push_back(dynamic_cast<Object*>(&sceneTriangle));
	sceneObjects.push_back(dynamic_cast<Object*>(&sceneSphere));
	sceneObjects.push_back(dynamic_cast<Object*>(&scenePlane));

	// Slightly shoot rays left of right camera direction
	double xAMT, yAMT;

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			if (WIDTH > HEIGHT) {
				xAMT = ((x + 0.5) / WIDTH) * aspectRatio - (((WIDTH - HEIGHT) / (double)HEIGHT) / 2);
				yAMT = ((HEIGHT - y) + 0.5) / HEIGHT;
			}
			else if (HEIGHT > WIDTH) {
				xAMT = (x + 0.5) / WIDTH;
				yAMT = (((HEIGHT - y) + 0.5) / HEIGHT) / aspectRatio - (((HEIGHT - WIDTH) / (double)WIDTH) / 2);
			}
			else {
				xAMT = (x + 0.5) / WIDTH;
				yAMT = ((HEIGHT - y) + 0.5) / HEIGHT;
			}

			Vector camRayOrigin = scene_cam.getPosition();
			Vector camRightDir = camRight * (xAMT - 0.5);
			Vector camDownDir = camDown  * (yAMT - 0.5);
			Vector camRayDirection = (camDir + (camRightDir + camDownDir)).normalize();

			Ray camRay(camRayOrigin, camRayDirection);

			std::vector<double> intersections;

			for (int i = 0; i < sceneObjects.size(); i++) {
				intersections.push_back(sceneObjects.at(i)->findIntersection(camRay));
			}
			
			int indexOfWinningObject = winningObjectIndex(intersections);

			if (indexOfWinningObject == -1) { Image.setPixel(x, y, 0, 0, 0); }  //set to black

			else  {
				if (intersections.at(indexOfWinningObject) > accuracy) {
					//detemine pos and dir vector at point
					Vector intersectionPos = camRay.origin + (camRayDirection * intersections.at(indexOfWinningObject));
					Vector intersectingRayDir = camRayDirection;
	
					Color intersectionColor = getColorAt(intersectionPos, intersectingRayDir, sceneObjects, indexOfWinningObject, lightSources, accuracy, ambientLight);
					Image.setPixel(x, y, intersectionColor);
				}
			}
		}
	}

	string errMsg;
	string fileName = "sphere-with-white-ambiance.bmp";

	if (!Image.write(fileName, errMsg)) std::cout << errMsg << std::endl;
	else std::cout << "Successfully wrote file: [" << fileName << "]" << std::endl;

	t2 = clock();
	float diff = ((float)t2 - (float)t1) / 1000;
	std::cout << diff << " seconds" << std::endl;

	std::getchar();

	return 0;
}