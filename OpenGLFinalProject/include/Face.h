#ifndef FACE_H
#define FACE_H
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iostream>
// OpenGL + GLUT imports
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include FT_FREETYPE_H
class Face
{
    public:
        Face(int subdivisions, bool withText);
        ~Face();
        void render(float x_start, float y_start, float x_end, float y_end, float z_start, float z_end);
        std::string getHeader();
        void setHeader(std::string header);
        std::string getText();
        void setText(std::string text);
        float x_start;
        float x_end;
        float y_start;
        float y_end;
        float z_start;
        float z_end;
    protected:
    private:
        std::vector<FT_Face> ft_faces;
        int subdivisions;
        std::string text;
        std::string header;
        static std::string texts[];
        FT_Library  library;
    
};


#endif // FACE_H
