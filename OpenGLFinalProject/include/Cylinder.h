#ifndef CYLINDER_H
#define CYLINDER_H
#ifdef __APPLE__
// OpenGL + GLUT imports
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include "Face.h"

class Cylinder
{
    public:
        void render();
        static Cylinder* getInstance(int n, int subdivisions);
        Cylinder(int n, int subdivisions);
        void exportToObj(std::string file_name);
    protected:
    private:
        static Cylinder* instance;
        std::vector<Face *> faces;
        int subdivisions;
        int num_faces;
        void resetCylinder(int n, int subdivisions);
};

#endif // CYLINDER_H
