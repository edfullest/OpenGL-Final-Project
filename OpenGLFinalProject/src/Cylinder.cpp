#include <string>
#include "Cylinder.h"

// We make cylinder a singleton so that there is only one instance running from it
Cylinder * Cylinder::instance = NULL;
Cylinder* Cylinder::getInstance(int n, int subdivisions){
    if (Cylinder::instance == NULL){
        Cylinder::instance = new Cylinder(n, subdivisions);
    }
    return Cylinder::instance;
}

Cylinder::~Cylinder(){
    for (auto &face : faces){
        delete face;
    }
    faces.clear();
}
Cylinder::Cylinder(int n, int subdivisions)
{
    this->subdivisions = subdivisions;
    this->num_faces = n;
    for(int i = 0; i < n; i++)
    {
        Face* face = new Face(subdivisions, false);
        face->setHeader(std::string("Main Face"));
        faces.push_back(face);
    }
}

void Cylinder::resetCylinder(int n, int subdivisions){
    this->subdivisions = subdivisions;
    this->num_faces = n;
    for (auto &face : faces){
        delete face;
    }
    faces.clear();
    for(int i = 0; i < n; i++)
    {
        Face* face = new Face(subdivisions, false);
        face->setHeader(std::string("Main Face"));
        faces.push_back(face);
    }
    
}

void Cylinder::render()
{
    glPushMatrix();
    
    glPushMatrix();
    // GL Line Loop for Bottom
    glBegin(GL_LINE_LOOP);
    int num_faces = this->num_faces;
    float height = -1 * subdivisions;
    for(int i = 0; i < num_faces; i++)
    {
        glVertex3f(sin(M_PI * 2.0f * i / num_faces), cos(M_PI * 2.0f * i / num_faces), 0.0f);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    // GL Line Loop for Top
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_faces; i++)
    {
        glVertex3f(sin(M_PI * 2.0f * i / num_faces), cos(M_PI * 2.0f * i / num_faces), height);
    }
    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
    // GL Line Loop for sides
    for(int i = 0; i < num_faces; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3f(sin(M_PI * 2.0f * i / num_faces), cos(M_PI * 2.0f * i / num_faces), height);
        glVertex3f(sin(M_PI * 2.0f * i / num_faces), cos(M_PI * 2.0f * i / num_faces), 0.0f);
        glEnd();
    }
    glPopMatrix();
    
    glPushMatrix();
    
    // Dynamic face creation
    for (int i = 0; i < num_faces; i++){
        float x_start = sin(M_PI * 2.0f * i / num_faces);
        float y_start = cos(M_PI * 2.0f * i / num_faces);
        float z_start = 0.0f;
        
        float x_end = sin(M_PI * 2.0f * (i + 1) / num_faces);
        float y_end = cos(M_PI * 2.0f * (i + 1) / num_faces);
        float z_end = height;
        faces[i]->render(x_start, y_start, x_end, y_end, z_start, z_end);
    }
    glPopMatrix();
    
    glPopMatrix();
    
}

void Cylinder::exportToObj(std::string file_name){
    std::ofstream output;
    output.open (file_name);
    std::cout << "Printing vertices data to: " << file_name << std::endl;
    // For each face, print the vertices
    int indices[faces.size() * 4];
    int i = 0;
    for (auto &face : faces){
        // Print the bottom vertices
        
        // Bottom left corner
        output << "v " << face->x_start << " "
        << face->y_start << " "
        << face->z_start <<
        std::endl;
        indices[i] = i;
        i++;
        // Bottom right corner
        output << "v " << face->x_end << " "
        << face->y_end << " "
        << face->z_start <<
        std::endl;
        indices[i] = i;
        i++;
        // Print the top vertices
        
        // Top left corner
        output << "v " << face->x_start << " "
        << face->y_start << " "
        << face->z_end <<
        std::endl;
        indices[i] = i;
        i++;
        // Top right corner
        output << "v " << face->x_end << " "
        << face->y_end << " "
        << face->z_end <<
        std::endl;
        indices[i] = i;
        i++;
    }
    // Print faces
    output << "f " << indices[0] + 1 << " "
    << indices[1] + 1 << " "
    << indices[2] + 1 <<
    std::endl;
    
    for(int i = 3; i < faces.size() * 4; i++){
        output << "f " << indices[i - 2] + 1 << " "
        << indices[i - 1] + 1 << " "
        << indices[i] + 1 <<
        std::endl;
    }
    output.close();
}

