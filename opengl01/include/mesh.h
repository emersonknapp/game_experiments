#ifndef _MESH_H
#define _MESH_H

#include "common.h"


struct tri {
	int a,b,c;
} ;

struct quad {
	int a,b,c,d;
} ;

struct LocalGeo {
	vec3 pos;
	vec3 dir;
};


class Mesh {
public:
	
	Mesh();
	Mesh(string);
	void init();
	
	vector<vec3> vertsVec;
	vector<vec3> normsVec;
	vector<vec3u> tris;
	int n_poly;
	int lastVertex, lastNorm;
	
	GLfloat* verts;
	GLfloat* norms;
	unsigned int* indices;
	
	string material;
	
	void createArrays();
	void addVert(vec3);
	void addNorm(vec3);
	vec3 getVert(int);
	vec3 getNorm(int);
	
	void parseOBJ(string);
	bool parseLine(string);
	
};

#endif