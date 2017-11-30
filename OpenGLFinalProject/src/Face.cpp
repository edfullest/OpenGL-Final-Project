#include "Face.h"
struct color{
    float R;
    float G;
    float B;
    float A;
    color(float _R,float _G,float _B,float _A) : R(_R), G(_G), B(_B), A(_A) {};
};

std::string Face::texts[] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "X",
    "E",
    "A",
    "D"
};

color colors[] = {
    color(0.4f,0.4f,1.0f,1.0),
    color(0.0f,0.4f,0.2f,1.0),
    color(0.4f,0.4f,0.4f,1.0),
    color(0.4f,0.4f,0.0f,1.0),
    color(0.0f,0.0f,0.4f,1.0),
    color(0.4f,0.0f,0.4f,1.0),
    color(0.4f,0.4f,0.0f,1.0)
};

Face::Face(int subdivisions, bool withText)
{
    this->subdivisions = subdivisions;
    FT_Library  library;   /* handle to library     */
    auto error = FT_Init_FreeType( &library );
    for(int i = 0; i < this->subdivisions; ++i){
        FT_Face face;
        
        //        if ( error ) {
        //            std::cout << "Error free type library" << std::endl;
        //
        //        }
        //
        //        error = FT_New_Face( library,
        //                            "/Library/Fonts/Verdana.ttf",
        //                            0,
        //                            &face );
        //        auto err = FT_Set_Char_Size(
        //                                    face,    /* handle to face object           */
        //                                    512,       /* char_width in 1/64th of points  */
        //                                    512,   /* char_height in 1/64th of points */
        //                                    500,     /* horizontal device resolution    */
        //                                    500 );   /* vertical device resolution      */
        //
        //        if(err){printf("FAIL1");}
        //        err = FT_Set_Pixel_Sizes(
        //                                 face,   /* handle to face object */
        //                                 256,      /* pixel_width           */
        //                                 256);   /* pixel_height          */
        //        if(err){printf("FAIL2");}
        ft_faces.push_back(face);
    }
}

GLuint glInitTexture(FT_Face &face)
{
    GLuint t = 1;
    
    glGenTextures( 1, &t );
    glBindTexture(GL_TEXTURE_2D, t);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer );
    return t;
}

void Face::render(float x_start, float y_start, float x_end, float y_end, float z_start, float z_end)
{
    this->x_start = x_start;
    this->y_start = y_start;
    this->x_end = x_end;
    this->y_end = y_end;
    this->z_start = z_start;
    this->z_end = z_end;
    
    glPushMatrix();
    float start = z_start;
    float offset = z_end * 1.0f / (float)subdivisions;
    int i = 0;
    for (FT_Face &face : ft_faces){
        //        FT_Load_Char(face, texts[i % 13][0], FT_LOAD_RENDER);
        if (i == 0){
            start = z_start;
        }
        else{
            // The new start will be the past offset
            start = offset;
        }
        offset = (z_end * 1.0f / (float) subdivisions) * (i + 1);
        
        //        glInitTexture(face);
        glBegin(GL_QUAD_STRIP);
        color color = colors[i % 7];
        glNormal3f(0.0f, 0.0f, 1.0f);
        glColor3f(color.R, color.G, color.B);
        /*
         glTexCoord2f(3.0, 3.0);
         glTexCoord2f(0.0, 3.0);
         glTexCoord2f(0.0, 0.0);
         glTexCoord2f(3.0, 0.0);
         */
        glVertex3f(x_start, y_start, start );
        glVertex3f(x_end, y_end, start);
        glVertex3f(x_start, y_start, offset);
        glVertex3f(x_end, y_end, offset);
        glEnd();
        i++;
    }
    glPopMatrix();
    
    
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

