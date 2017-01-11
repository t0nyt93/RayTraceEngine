// Student.Color.h
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "myMath.h"

namespace COLOR {

	struct Color {
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a);
		Color(int r, int g, int b, int a);
		Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		void Clamp();
		// Operator Overloads
		Color operator* (const Color &c) const;
		Color operator* (float f) const;
		Color operator+ (const Color &c) const;
		void operator+= (const Color &c);
		Color operator/ (float f) const;
	};

	float ClampZeroOne(float n);
	int ClampTwoFiveFive(int n);
	void Clamp(float &v);

	// Color Functions
	Color ConvertColor(unsigned int pixel);
	Color ConvertColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	void ConvertColor(Color color, unsigned int& r, unsigned int& g, unsigned int& b, unsigned int& a);
	unsigned int ConvertColor (Color color);
	void ExtractColor(unsigned int pixel, unsigned int& r, unsigned int& g, unsigned int& b, unsigned int& a);
	unsigned int CreateColor(int r, int g, int b, int a);

	// Pixel Functions
	unsigned int GetPixel (int* video, int x, int y, int w, int h);

	// Operator Overloads
	Color operator* (float f, const Color &c);

	void ToonRamp(float &z);
}

