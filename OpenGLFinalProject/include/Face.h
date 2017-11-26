#ifndef FACE_H
#define FACE_H
#include <vector>
#include <string>

class Face
{
    public:
        Face(int subdivisions, bool withText);
        void render();
        std::string getHeader();
        void setHeader(std::string header);
        std::string getText();
        void setText(std::string text);
    protected:
    private:
        std::vector<Face> faces;
        int subdivisions;
        std::string text;
        std::string header;
        static std::string texts[];
};

#endif // FACE_H
