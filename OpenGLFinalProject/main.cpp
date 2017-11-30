//
//  main.cpp
//  OpenGLFinalProject
//
//  Created by Eduardo Jesus Serna L on 11/24/17.
//  Copyright © 2017 Eduardo Jesus Serna L. All rights reserved.
//

#include <math.h>       /* sin */
#include <iostream>
#include <string>
#include "Cylinder.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f;
float lz=-3.0f;
float ly = 0.0f;
// XZ position of the camera
float angleYZ = 0.0f;
float rollAngle = M_PI / 2;
float x=0.0f,z=7.0f, y = 1.0f;
float roll = 1.0;
static float fraction = 0.1f;
Cylinder *cylinder;
std::string menu[10] = {
    "Flecha Der - Rotar Menu a la Derecha",
    "Flecha Izq - Rotar Menu a la Izquierda",
    "Click Izq + girar - Rotar camara",
    "Flecha Arriba - Mover Camara adelante",
    "Flecha Abajo - Mover Camara abajo",
    "Tecla 1 - Aumentar Caras en Menu",
    "Tecla 2 - Aumentar Subdivisiones en Menu",
    "Tecla 3 - Decrementar Caras en Menu",
    "Tecla 4 - Decrementar Subdivisiones en Menu",
    "B - Exportar a Wavefront OBJ"
};
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaAngleY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

int number_faces = 5;
int number_subdivisions = 2;
bool isMenuOn = false;
float cylinderAngle = 0.0f;


void drawString(std::string const &s, float x, float y){
    glPushMatrix();
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(x, y, -1.0f);
    glRasterPos3f(1.0, 1.0,1.0);
    for (auto &c : s) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    glPopMatrix();
}

void changeSize(int w, int h) {
    
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    
    float ratio =  w * 1.0 / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    
}

// ROTATIONS
void tiltUp(float delta){
    angleYZ += delta;
    ly = sin(angleYZ);
    lz = -cos(angleYZ);
}
void tiltDown(float delta){
    angleYZ -= delta;
    ly = sin(angleYZ);
    lz = -cos(angleYZ);
}

void panRight(float delta){
    angle += delta;
    lx = sin(angle);
    lz = -cos(angle);
}

void panLeft(float delta){
    angle -= 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    
}

void rollRight(float delta){
    rollAngle += 0.1f;
}

void rollLeft(float delta){
    roll += 0.5f;
    rollAngle -= 0.1f;
}

// MOVEMENTS
void boomUp(float delta){
    y += ly * fraction + delta;
}

void boomDown(float delta){
    y -= ly * fraction + delta;
}

void dollyLeft(float delta){
    x -= lx * fraction + delta;
}

void dollyRight(float delta){
    x += lx * fraction + delta;
}

static void processNormalKeys(unsigned char key, int e, int l) {
    if (key == 'w'){
        tiltUp(0.01f);
    }
    else if (key == 's'){
        tiltDown(0.01f);
    }
    else if (key == 'a'){
        rollLeft(0.5f);
    }
    else if (key == 'd'){
        rollRight(0.5f);
    }
    
    else if (key == 'r'){
        boomUp(0.1f);
    }
    else if (key == 'f'){
        boomDown(0.1f);
    }
    else if (key == 'z'){
        dollyLeft(0.1f);
    }
    else if (key == 'x'){
        dollyRight(0.1f);
    }
    else if (key == 'm'){
        isMenuOn = !isMenuOn;
    }
    else if (key == 'b'){
        cylinder->exportToObj("infinite_menu.obj");
    }
    else if ((int)key == 49){
        number_faces++;
        cylinder->resetCylinder(number_faces,number_subdivisions);
    }
    else if ((int)key == 50){
        number_subdivisions++;
        cylinder->resetCylinder(number_faces,number_subdivisions);
    }
    else if ((int)key == 51){
        number_faces--;
        cylinder->resetCylinder(number_faces,number_subdivisions);
    }
    else if ((int)key == 52){
        number_subdivisions--;
        cylinder->resetCylinder(number_faces,number_subdivisions);
    }
    else if ((int)key == 27 ){
        exit(0);
    }
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT :
            //            dollyLeft(1.1f);
            cylinderAngle -= 0.8f;
            break;
        case GLUT_KEY_RIGHT :
            //            dollyRight(1.1f);
            cylinderAngle += 0.8f;
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}


void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        
        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;
        
        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
    if (yOrigin >= 0){
        deltaAngleY = (y - yOrigin) * 0.001f;
        ly = sin(angleYZ + deltaAngleY);
        lz = -cos(angleYZ + deltaAngleY);
    }
    
}

void mouseButton(int button, int state, int x, int y) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        
        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            angleYZ += deltaAngleY;
            xOrigin = -1;
            yOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}
void renderScene(void) {
    
    // Clear Color and Depth Buffers
    glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(x, y, z,
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);
    
    //    Cylinder *cylinder = Cylinder::getInstance(number_faces, number_subdivisions);
    if (!isMenuOn){
        
        glPushMatrix();
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        
        glTranslatef(0, 0.3, 0.1);
        glRotatef(cylinderAngle, 0.0f, 0.0f, 1.0f);
        
        glScalef(2.9f, 2.9f, 1.5f);
        cylinder->render();
        
        glPopMatrix();
        glPushMatrix();
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        drawString("Presiona M para ver Menu ", -3.0f, -2.7f);
        drawString("Numero de Caras : " + (std::to_string(number_faces)) + " ", -3.0f, -2.2f);
        drawString("Numero de Subdivisiones : " + (std::to_string(number_subdivisions)) + " ", -3.0f, -2.5f);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        float x = -3.0f;
        float y = 2.5f;
        int i = 0;
        for (std::string &m : menu){
            drawString(m, x, y);
            y -= 0.4;
            i++;
        }
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        drawString("Numero de Caras : " + (std::to_string(number_faces)) + " ", x - 0.4f, y);
        drawString("Numero de Caras : " + (std::to_string(number_faces)) + " ", x - 0.4f, y);
        y -= 0.5;
        drawString("Numero de Subdivisiones : " + (std::to_string(number_subdivisions)) + " ", x - 0.4f, y);
        drawString("Numero de Subdivisiones : " + (std::to_string(number_subdivisions)) + " ", x - 0.4f, y);
        glPopMatrix();
        
        
    }
    
    
    
    glutSwapBuffers();
}


int main(int argc, char **argv) {
    // init GLUT and create window
    cylinder = Cylinder::getInstance(number_faces, number_subdivisions);
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    glutCreateWindow("Infinite Menu");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    
    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLoadIdentity();
    
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}

