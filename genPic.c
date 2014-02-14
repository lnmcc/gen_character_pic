#include "saveBmp.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#include <getopt.h>

int width;
int height;
int frames;
char *path;
int dur;

void my_reshape(int w, int h) {
    GLdouble size;
    GLdouble aspect;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    size = (GLdouble)((w >= h) ? w : h) / 2.0;
    if(w <= h) {
        aspect = (GLdouble)h / (GLdouble)w;
        glOrtho(-size, size, -size * aspect, size * aspect, -1000000.0, 1000000.0);
    } else {
        aspect = (GLdouble)w / (GLdouble)h;
        glOrtho(-size * aspect, size * aspect, -size, size, -1000000.0, 1000000.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void print_bitmap_string(char *s) {
    if(s && strlen(s)) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        //glRasterPos2f(1000.0, 1000.0);
        glTranslatef(-width / 2, 0.0, 0.0);
        glScalef(5.0, 5.0, 0.0);
        while(*s) {
           // glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
            s++;
        }
        glPopMatrix();
    }   
}

void draw_stuff(char *string) {
    glColor4f(0.0, 1.0, 0.0, 0.0);
    print_bitmap_string(string);
}

void getBmp(int height, int width, char *fileName) {
    BYTE *bits = NULL;

    DWORD size = 4 * ((height * 24 + 31) / 32) * width; 
    bits = (BYTE*)malloc(size) ;
    glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);
    Snapshot(bits, width, height, fileName, size);
    free(bits);
}

void my_display(void) {
    char string[128] = { 0 };
    char fn[128] = { 0 };

    for(int i = 0; i < frames; i++) {
        for(int j = 0; j < dur; j++) {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            if(dur == 1) {
                snprintf(string, sizeof(string), "%d", i + 1);
                snprintf(fn, sizeof(fn), "%s/%d.bmp", path, i + 1);
            } else {
                snprintf(string, sizeof(string), "%d.%d", i + 1, j + 1);
                snprintf(fn, sizeof(fn), "%s/%d.%d.bmp", path, i + 1, j + 1);
            }
            draw_stuff(string);
            glutSwapBuffers();
            getBmp(height, width, fn);
            memset(string, 0, sizeof(string));
        }
    }
    exit(0);
}

void printHelp() {
    fprintf(stderr, "Usage: genPic -n 10 -d 1 -w 1920 -h 1080 -p /tmp\n");
}

int main(int argc, char **argv) {
    if(argc < 6) {
        printHelp();
        exit(1);
    }
    int opt;
    while((opt = getopt(argc, argv, "n:w:h:p:d:")) != -1) {
        switch(opt) {
        case 'n':
            frames = atoi(optarg);
            fprintf(stderr, "frames = %d\n", frames);
            break;
        case 'w':
            width = atoi(optarg);
            fprintf(stderr, "width = %d\n", width);
            break;
        case 'h':
            height = atoi(optarg);
            fprintf(stderr, "height = %d\n", height);
            break;
        case 'p':
            path = optarg;
            fprintf(stderr, "path = %s\n", path);
            break;
        case 'd':
            dur = atoi(optarg);
            fprintf(stderr, "dur = %d\n", dur);
            break;
        default:
            break;
        }
    }

    glutInitWindowSize(width, height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("GLUT fonts");
    glutDisplayFunc(my_display);
    glutReshapeFunc(my_reshape);
    glutMainLoop();

    return 0;
}
