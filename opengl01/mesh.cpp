#include "mesh.h"

using namespace std;


Mesh::Mesh() {
	init();
}

Mesh::Mesh(string file) {
	init();
	parseOBJ(file);
	createArrays();
}

void Mesh::init() {
	lastNorm = 1;
	lastVertex = 1;
	vertsVec.push_back(vec3("0 0 0"));
}

void Mesh::addVert(vec3 v) {
	vertsVec.push_back(v);
}

void Mesh::addNorm(vec3 v) {
	normsVec.push_back(v);
}

vec3 Mesh::getVert(int i) {
	if (i>=0)
		return vertsVec[i];
	else
		return vertsVec[lastVertex+i];
}

vec3 Mesh::getNorm(int i) {
	if (i>=0)
		return normsVec[i];
	else
		return normsVec[normsVec.size()-i];
}

void Mesh::createArrays() {

	int size = vertsVec.size()*3;
	verts = new GLfloat[size];
	//norms = new GLfloat[size];
	for (size_t b=0; b<vertsVec.size(); b++) {
		int i = b*3;
		verts[i] = vertsVec[b][0];
		verts[i+1] = vertsVec[b][1];
		verts[i+2] = vertsVec[b][2];
		//norms[i] = normsVec[b][0];
		//norms[i+1] = normsVec[b][1];
		//norms[i+2] = normsVec[b][2];
	}
	
	
	
	n_poly = tris.size();
	indices = new unsigned int[n_poly*3];
	
	for (int i=0; i<n_poly; i++) {
		int q = i*3;
		indices[q] = tris[i][0];
		indices[q+1] = tris[i][1];
		indices[q+2] = tris[i][2];
	}
}

bool Mesh::parseLine(string line) {
	

	string op;
	
	if (line.empty())
		return true;
	stringstream ss(stringstream::in | stringstream::out);
	ss.str(line);
	ss >> op;
	if (op.compare("")==0) {
		return true;
	}
	else if (op[0] == '#') {
		return true;
	}
	//VERTEX
	else if (op.compare("v") == 0) {
		double v[3];
		ss >> v[0] >> v[1] >> v[2];
		vec3 p = vec3(v);		
		lastVertex++;
		vertsVec.push_back(p);
	} 
	//VERTEX NORMAL
	else if (op.compare("vn") == 0) {
		double n[3];
		ss >> n[0] >> n[1] >> n[2];
		vec3 p = vec3(n);
		lastNorm++;
		normsVec.push_back(p);
	}
	//FACE
	else if (op.compare("f") == 0) {
		vector<int> f;
		int q;
		while(ss.good()) {
			ss >> q;
			f.push_back(q);
		}
		if (f.size() < 3) {
			Warning("Malformed polygon on line: " + line);
		} else if (f.size() == 3) {
			vec3u p;
			p[0] = f[0];
			p[1] = f[1];
			p[2] = f[2];
			tris.push_back(p);
		} else {
			if (DBMESH) cout << "Found >3 vertex poly." << endl;
		}
	} else {
		cout << "Warning: unrecognized command " << op << endl;
	}
	if (ss.fail())
		return false;
	return true;
}

void Mesh::parseOBJ(string filename) {
	ifstream inFile(filename.c_str(), ifstream::in);
	char line[1024];

	if (!inFile) {
		Error("Could not open file " + filename);
	}

	while (inFile.good()) {
		inFile.getline(line, 1023);
		if(!parseLine(string(line))) {
			Error("Bad line in input file.");
		}
	}
	inFile.close();
}
