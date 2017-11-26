#include <stdlib.h>
#include <iostream>
#include "Face.h"

std::string Face::texts[] = {
            "File",
            "Edit",
            "View",
            "Search",
            "Project",
            "Build",
            "Debug",
            "Tools",
            "Plugins",
            "Settings",
            "Window",
            "Preferences",
            "Help"
        };

Face::Face(int subdivisions, bool withText)
{
    this->subdivisions = subdivisions;

    Face* face;
    for(int i = 0; i < (subdivisions * subdivisions); i++)
    {
        face = new Face(0, true);
        faces.push_back(*face);
    }

    if(withText)
    {
        header = "Default Header";
        text = texts[rand() % 13];
    }
}

void Face::render()
{
    std::cout << this->header << " : " << this->text << " : " << this->subdivisions << std::endl;
    for(int i = 0; i < faces.size(); i++)
    {
        std::cout << "Child " << i << " : " << std::endl;
        faces[i].render();
    }
}

void Face::setHeader(std::string header)
{
    this->header = header;
}

void Face::setText(std::string text)
{
    this->text = text;
}

std::string Face::getHeader()
{
    return this->header;
}

std::string Face::getText()
{
    return this->text;
}
