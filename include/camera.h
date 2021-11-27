#ifndef CAMERA_H
#define CAMERA_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "actor.h"

class Camera : public Actor {
public:
    void applyTransform(void);
private:

}; // End of class

#endif // CAMERA_H
