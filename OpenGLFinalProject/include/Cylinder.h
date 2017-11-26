#ifndef CYLINDER_H
#define CYLINDER_H
#include <vector>
#include <string>
#include "Face.h"

class Cylinder
{
    public:
        Cylinder(int n, int subdivisions);
        void render();
    protected:
    private:
        std::vector<Face> faces;
};

#endif // CYLINDER_H
