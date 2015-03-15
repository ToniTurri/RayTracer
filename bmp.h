#ifndef _BMP_H_
#define _BMP_H_

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>

#include "color.h"

using std::string;
using std::vector;
using std::ofstream;
using std::sort;
using std::cout;
using std::endl;
using std::swap;
using std::ios;

typedef vector<Color> ColorRow;

class BMP {
public:

	BMP(int width, int height);
	void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
	void setPixel(int x, int y, const Color &color);
	bool write(string &fileName, string &errMsg) const;

private:
	int bmpWidth;
	int bmpHeight;
	vector<ColorRow> Image;
};

static void doWrite(ofstream &out, int value);
static void doWrite(ofstream &out, short value);
static void doWrite(ofstream &out, const Color &color);


BMP::BMP(int width, int height) : bmpWidth(width), bmpHeight(height) {
	// Initialize the entire bitmap to the default color (white)
	for (int i = 0; i < bmpHeight; i++) {
		ColorRow row;

		for (int j = 0; j < bmpWidth; j++)
			row.push_back(Color());

		Image.push_back(row);
	}
}

void BMP::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue) {
	bool setThis = true;

	if (x < 0 || x >= bmpWidth) {
		cout << "Invalid value: " << x << " (expected: 0 <= x < " << bmpWidth << ")" << endl;
		setThis = false;
	}

	if (y < 0 || y >= bmpHeight) {
		cout << "Invalid value: " << y << " (expected: 0 <= y < " << bmpHeight << ")" << endl;
		setThis = false;
	}

	if (setThis) Image[y][x] = Color(red, green, blue, 0);
}

void BMP::setPixel(int x, int y, const Color &color) {
	setPixel(x, y, color.r, color.g, color.b);
}

bool BMP::write(string &fileName, string &errMsg) const {
	ofstream out(fileName.c_str(), ios::binary);

	if (out.fail()) {
		errMsg = "Could not open: [" + fileName + "]";
		return(false);
	}

	// Header sizes ...
	const int BMP_FILE_HEADER_SIZE = 14;
	const int BMP_INFO_HEADER_SIZE = 40;

	// file header
	out.put('B');
	out.put('M');

	int fileSize =
		bmpWidth * bmpHeight * 3 +
		BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

	doWrite(out, fileSize);

	short reserved = 0;
	doWrite(out, reserved);
	doWrite(out, reserved);

	int offset = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
	doWrite(out, offset);

	// info header
	int headerSize = BMP_INFO_HEADER_SIZE;
	doWrite(out, headerSize);

	doWrite(out, bmpWidth);
	doWrite(out, bmpHeight);

	short colorPlanes = 1;
	doWrite(out, colorPlanes);

	short bitsPerPixel = 24;
	doWrite(out, bitsPerPixel);

	int zero = 0;

	for (int i = 0; i < 6; i++)
		doWrite(out, zero);

	for (int i = 0; i < bmpHeight; i++)
		for (int j = 0; j < bmpWidth; j++)
			doWrite(out, Image[i][j]);

	out.close();

	return(true);
}


static void doWrite(ofstream &out, int value) {
	out.write((const char *)&value, sizeof(int));
}
static void doWrite(ofstream &out, short value) {
	out.write((const char *)&value, sizeof(short));
}
static void doWrite(ofstream &out, const Color &color) {
	out.write((const char *)&color.b, sizeof(unsigned char));
	out.write((const char *)&color.g, sizeof(unsigned char));
	out.write((const char *)&color.r, sizeof(unsigned char));
}

#endif