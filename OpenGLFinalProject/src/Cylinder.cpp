#include <string>
#include "Cylinder.h"

Cylinder::Cylinder(int n, int subdivisions)
{
    Face* face;
    for(int i = 0; i < n; i++)
    {
        face = new Face(subdivisions, false);
        face->setHeader(std::string("Main Face"));
        faces.push_back(*face);
    }
}

void Cylinder::render()
{
    for(int i = 0; i < faces.size(); i++)
    {
        faces[i].render();
    }
}
