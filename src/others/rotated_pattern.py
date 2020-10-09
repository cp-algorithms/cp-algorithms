from __future__ import division
from __future__ import print_function

import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
from math import floor, sin, cos


def key_callback(window, key, scancode, action, mode):
    if key == glfw.KEY_ESCAPE and action == glfw.PRESS:
        print("closed window for pressing Escape key")
        glfw.set_window_should_close(window, True)
def reshape_callback(window, width, height):
    glViewport(0,0,width, height)


def setpixel(x,y,color):
    glColor3fv(color)
    glBegin(GL_POINTS)
    glVertex2f(x,y)
    glEnd()


def drawAxes():
    glColor3f(1.0,1.0,1.0)
    glBegin(GL_LINES)
    glVertex2f(-200,0)
    glVertex2f(200,0)
    glVertex2f(0,-200)
    glVertex2f(0,200)
    glEnd()

def rotationOrigin2D(point, angle):
    angle = np.deg2rad(angle)
    #print(angle)
    x_new = point[0]* cos(angle)   - point[1] * sin(angle)
    y_new = point[0]* sin(angle)   + point[1] * cos(angle)
    return (x_new, y_new)

def main():
    if not glfw.init():
        raise Exception("glfw cannot be initialised.......")

    window=glfw.create_window(700,700, "rotation 2D pattern - b117049",None,None)

    if not window:
        glfw.terminate()
        raise Exception("glfw window not created")

    w,h = glfw.get_framebuffer_size(window)
    print("width: {}, height:{}".format(w,h))

    glfw.set_window_pos(window, 400,40)
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)

    glfw.set_window_size_callback(window, reshape_callback)

    gluOrtho2D(-200.0, 200.0,-200.0,200.0)
    setpixel(0,0,[1,0,1])

    while not glfw.window_should_close(window):

        glClear(GL_COLOR_BUFFER_BIT)
        #glClearColor(0.0,0.76,0.56,1.0)
        glClearColor(0,0,0,1.0)

        #drawAxes()

        a =(40,40) #yellow
        b = (40, 100) #green
        c=(100,100) #red
        d=(100,40) #blue
        i=8

        while i!=0:
            

            glBegin(GL_QUADS)
            glColor3f(1,1,0) #yellow vertex
            glVertex2fv(a)
            glColor3f(0,1,0)
            glVertex2fv(b)
            glColor3f(1,0,0)
            glVertex2fv(c)
            glColor3f(0,0,1)#blue vertex
            glVertex2fv(d)
            glEnd()

        #print("rotate square vertices by 45 degrees anti clockwise x-dir")


        #rotate square vertices by 45 degrees anti clockwise x-dir
            angle = 45
            a = rotationOrigin2D(a, angle)
            b = rotationOrigin2D(b, angle)
            c = rotationOrigin2D(c,angle)
            d = rotationOrigin2D(d,angle)
            i=i-1
        #print(A_new,"||", B_new,"||", C_new,"||", D_new)


    
        glfw.swap_buffers(window)

        glfw.poll_events()

    glfw.terminate()


if __name__ == "__main__":
    main()
        
        
        


    
