// ---------------------------------------------------------
// Segment.h
// Header file for Segment class
//
// Author: J�rgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) J�rgen Vogl, 2019
// ----------------------------------------------------------

#pragma once


class Segment
{
public:
	struct Point
	{
		double x;
		double y;
	};

	Point start;
	Point end;
};
