#include "main.h"

int POS_X, POS_Y;

//loading the OBJ model file
std::string model_name = "Models/Sample1.obj";

//fixed position of the luminating light
GLfloat lightingPosition[] = { -10.0f, 10.0f, 100.00f, 1.0f };

//coordinates
float pos_x, pos_y, pos_z;
//angular coordinates
float angle_x = 30.0f, angle_y = 0.0f;

int x_old = 0, y_old = 0;
int current_scroll = 5;

//zoom speed
float zoom_per_scroll;

//boolean to check if the mouseButtom is held
bool mouseHold = false;
bool is_updated = false;

Model model;

void timer(int value) {
    if (is_updated) {
        is_updated = false;
        glutPostRedisplay();
    }
    glutTimerFunc(INTERVAL, timer, 0);
}

void init() {
    //enable lighting 
    glEnable(GL_LIGHTING);

    //primary light
    glEnable(GL_LIGHT0);

    //setting the values of light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightingPosition);

    //background color
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glMatrixMode(GL_PROJECTION);

    //loading the identity matrix
    glLoadIdentity();

    //specify the far clipping plane
    gluPerspective(20.0, 1.0, 1.0, 2000.0);

    glMatrixMode(GL_MODELVIEW);

    //merge with the model in contact
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    model.load(model_name.c_str());

    pos_x = model.pos_x;
    pos_y = model.pos_y;
    pos_z = model.pos_z - 1.0f;

    zoom_per_scroll = -model.pos_z / 10.0f;
}

void displayModel() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(pos_x, pos_y, pos_z);
    glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    model.draw();
    glutSwapBuffers();
}


void mouseSensor(int button, int state, int x, int y) {
    is_updated = true;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            x_old = x;
            y_old = y;
            mouseHold = true;
        }
        else
            mouseHold = false;
    }
    else if (state == GLUT_UP) {
        switch (button) {
        case 3:
            if (current_scroll > 0) {
                current_scroll--;
                pos_z += zoom_per_scroll;
            }
            break;
        case 4:
            if (current_scroll < 15) {
                current_scroll++;
                pos_z -= zoom_per_scroll;
            }
            break;
        }
    }
}

void motionUpdater(int x, int y) {
    if (mouseHold) {
        is_updated = true;

        angle_y += (x - x_old);
        x_old = x;
        if (angle_y > 360.0f)
            angle_y -= 360.0f;
        else if (angle_y < 0.0f)
            angle_y += 360.0f;

        angle_x += (y - y_old);
        y_old = y;
        if (angle_x > 90.0f)
            angle_x = 90.0f;
        else if (angle_x < -90.0f)
            angle_x = -90.0f;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("TriDimeX");
    init();
    glutDisplayFunc(displayModel);
    glutMouseFunc(mouseSensor);
    glutMotionFunc(motionUpdater);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
