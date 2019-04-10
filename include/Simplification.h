#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <string>
#include "PointSet.h"
#include "PairHeap.h"
#include "Point.h"
#include "Face.h"

using std::string;
class Simplification
{
	string inputFile;
	string outputFile;
	double ratio;
	int faceCount;

	PointSet pointSet;
	PairHeap pairHeap;

	bool readFile();//read data from file
	void updateData(Pair toDel);
	

public:
	void saveFile(vector<Point> &vert, vector<Face> &face);
	Simplification();
	void setInput(string _input);
	void setOutput(string _output);
	void setRatio(double _ratio);
	void execute();
	void outMat();
};

#endif