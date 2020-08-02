/***
 Assignment-3: Geometric Modeling of a Scene

 Name: Bahar,Talia

 Collaborators: Pegler-Gordon, Maya; 

 Project Summary: 
 In this project I recreated a part of my kitchen using hierarchical modeling of the objects. 
 Using 3D translation and rotation I was able to create planes and combine them into a cube. To build my kitchen scene I created many cubes
 and applied scaling and transformations to them to make them resemble kitchen objects. I created a microwave, oven, fridge, and countertops
 by manipulating these cubes. 
 ***/
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#pragma GCC diagnostic pop

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

// If a float is < EPSILON or > -EPILSON then it should be 0
float EPSILON = 0.000001;
// theta is the angle to rotate the scene
float THETA = 0.0;
// Vector placeholders for the scene and color array
vector<GLfloat> SCENE;
vector<GLfloat> COLOR;

/**************************************************
 *  Rectangular Prisms via Hierarchical Modeling  *
 *                                                *
 *  using planes as building blocks, build a unit *
 *  cube with transformations that will serve as  *
 *  a primitive for modeling objects in the scene *
 *                                                *
 *************************************************/

// Initializes a square plane of unit lengths
vector<GLfloat> init_plane()
{
    vector<GLfloat> vertices{
        +0.5, +0.5, +0.0,
        -0.5, +0.5, +0.0,
        -0.5, -0.5, +0.0,
        +0.5, -0.5, +0.0};
    return vertices;
}

// Converts degrees to radians for rotation
float deg2rad(float d)
{
    return (d * M_PI) / 180.0;
}

// Converts a vector to an array
GLfloat *vector2array(vector<GLfloat> vec)
{
    GLfloat *arr = new GLfloat[vec.size()];
    for (int i = 0; i < vec.size(); i++)
    {
        arr[i] = vec[i];
    }
    return arr;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_homogeneous_coord(vector<GLfloat> cartesian_coords)
{
    vector<GLfloat> result;
    for (int i = 0; i < cartesian_coords.size(); i++)
    {
        result.push_back(cartesian_coords[i]);
        if ((i + 1) % 3 == 0)
        {
            result.push_back(1.0);
        }
    }
    return result;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_cartesian_coord(vector<GLfloat> homogeneous_coords)
{
    vector<GLfloat> result;
    for (int i = 0; i < homogeneous_coords.size(); i++)
    {
        if ((i + 1) % 4 == 0)
        {
            continue;
        }
        else
        {
            result.push_back(homogeneous_coords[i]);
        }
    }
    return result;
}

// Definition of a translation matrix
vector<GLfloat> translation_matrix(float dx, float dy, float dz)
{
    vector<GLfloat> translate_mat{1, 0, 0, dx,
                                  0, 1, 0, dy,
                                  0, 0, 1, dz,
                                  0, 0, 0, 1};
    return translate_mat;
}

// Definition of a scaling matrix
vector<GLfloat> scaling_matrix(float sx, float sy, float sz)
{
    vector<GLfloat> scale_mat{sx, 0, 0, 0,
                              0, sy, 0, 0,
                              0, 0, sz, 0,
                              0, 0, 0, 1};
    return scale_mat;
}

// Definition of a rotation matrix about the x-axis theta degrees
vector<GLfloat> rotation_matrix_x(float theta)
{
    theta = deg2rad(theta);
    vector<GLfloat> rotate_mat_x{1, 0, 0, 0,
                                 0, cos(theta), -sin(theta), 0,
                                 0, sin(theta), cos(theta), 0,
                                 0, 0, 0, 1};
    return rotate_mat_x;
}

// Definition of a rotation matrix about the y-axis by theta degrees
vector<GLfloat> rotation_matrix_y(float theta)
{
    theta = deg2rad(theta);
    vector<GLfloat> rotate_mat_y{cos(theta), 0, sin(theta), 0,
                                 0, 1, 0, 0,
                                 -sin(theta), 0, cos(theta), 0,
                                 0, 0, 0, 1};
    return rotate_mat_y;
}

// Definition of a rotation matrix about the z-axis by theta degrees
vector<GLfloat> rotation_matrix_z(float theta)
{
    theta = deg2rad(theta);
    vector<GLfloat> rotate_mat_z{cos(theta), -sin(theta), 0, 0,
                                 sin(theta), cos(theta), 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};
    return rotate_mat_z;
}

// Perform matrix multiplication for A B
vector<GLfloat> mat_mult(vector<GLfloat> A, vector<GLfloat> B)
{
    vector<GLfloat> result;
    for (int i = 0; i < B.size(); i += 4)
    {
        for (int j = 0; j < A.size(); j += 4)
        {
            GLfloat dot_product = 0.0;
            for (int k = 0; k < 4; k++)
            {
                GLfloat value = A[j + k] * B[i + k];
                if (value < EPSILON && value > -1.0 * EPSILON)
                {
                    value = 0.0;
                }
                dot_product += value;
            }
            result.push_back(dot_product);
        }
    }
    return result;
}

// Builds a unit cube centered at the origin
vector<GLfloat> build_cube()
{
    vector<GLfloat> result;
    vector<GLfloat> A1_front = mat_mult(translation_matrix(0, 0, 0.5), to_homogeneous_coord(init_plane()));
    vector<GLfloat> A2_back = mat_mult(translation_matrix(0, 0, -0.5), mat_mult(rotation_matrix_y(180), to_homogeneous_coord(init_plane())));
    vector<GLfloat> A3_right = mat_mult(translation_matrix(0.5, 0, 0), mat_mult(rotation_matrix_y(90), to_homogeneous_coord(init_plane())));
    vector<GLfloat> A4_left = mat_mult(translation_matrix(-0.5, 0, 0), mat_mult(rotation_matrix_y(-90), to_homogeneous_coord(init_plane())));
    vector<GLfloat> A5_top = mat_mult(translation_matrix(0, 0.5, 0), mat_mult(rotation_matrix_x(-90), to_homogeneous_coord(init_plane())));
    vector<GLfloat> A6_bottom = mat_mult(translation_matrix(0, -0.5, 0), mat_mult(rotation_matrix_x(-90), to_homogeneous_coord(init_plane())));

    result.reserve(A1_front.size() + A2_back.size() + A3_right.size() + A4_left.size() + A5_top.size() + A6_bottom.size() );
    result.insert( result.end(), A1_front.begin(), A1_front.end() );
    result.insert( result.end(), A2_back.begin(), A2_back.end() );
    result.insert( result.end(), A3_right.begin(), A3_right.end() );
    result.insert( result.end(), A4_left.begin(), A4_left.end() );
    result.insert( result.end(), A5_top.begin(), A5_top.end() );
    result.insert( result.end(), A6_bottom.begin(), A6_bottom.end() );

    return result;
}

/**************************************************
 *            Camera and World Modeling           *
 *                                                *
 *  create a scene by applying transformations to *
 *  the objects built from planes and position    *
 *  the camera to view the scene by setting       *
 *  the projection/viewing matrices               *
 *                                                *
 *************************************************/

void setup()
{
    // Enable the vertex array functionality
    glEnableClientState(GL_VERTEX_ARRAY);
    // Enable the color array functionality (so we can specify a color for each vertex)
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Set up some default base color
    glColor3f(0.5, 0.5, 0.5);
    // Set up white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init_camera()
{
   // Camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a 50 degree field of view, 1:1 aspect ratio, near and far planes at 3 and 7
    gluPerspective(50.0, 1.0, 2.0, 10.0);
    // Position camera at (2, 3, 5), attention at (0, 0, 0), up at (0, 1, 0)
    gluLookAt(2.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Construct the scene using objects built from cubes/prisms
vector<GLfloat> init_scene()
{
    vector<GLfloat> scene;

    vector<GLfloat> microwave = mat_mult( scaling_matrix(1, .7, 1),mat_mult(translation_matrix(0, 2.5, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> oven = mat_mult(translation_matrix(0, -0.5, 0), mat_mult(rotation_matrix_x(-90), build_cube()));
    vector<GLfloat> test = mat_mult( scaling_matrix(1, .7, 1), mat_mult(translation_matrix(0, 3.5, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> burner1 = mat_mult( scaling_matrix(.28, .28, .28), mat_mult(translation_matrix(-1.1, .00001, .8), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> burner2 = mat_mult( scaling_matrix(.28, .28, .28), mat_mult(translation_matrix(1.1, .00001, -.8), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> burner3 = mat_mult( scaling_matrix(.28, .28, .28), mat_mult(translation_matrix(1.1, .00001, .79999), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> burner4 = mat_mult( scaling_matrix(.28, .28, .28), mat_mult(translation_matrix(-1.1, .00001, -.79999), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> microwaveHandle = mat_mult( scaling_matrix(.08, .5,.05), mat_mult(translation_matrix(-5, 3.5, 10.5), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> microwaveController = mat_mult( scaling_matrix(.2, .6,.05), mat_mult(translation_matrix(1.7, 3, 11), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> ovenBack = mat_mult( scaling_matrix(1, .6,.05), mat_mult(translation_matrix(.001, .5, -10), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> ovenHandle = mat_mult( scaling_matrix(.5, .1,.05), mat_mult(translation_matrix(.001, -.99991, 11), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> counter1 = mat_mult( scaling_matrix(.7, 1, 1),mat_mult(translation_matrix(1.22, -0.5, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> counter2= mat_mult( scaling_matrix(.7, .1, 1.1),mat_mult(translation_matrix(1.22, -0.2, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> fridgeBottom= mat_mult( scaling_matrix(.8, 1.4, 1),mat_mult(translation_matrix(2, -.25, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> fridgeTop= mat_mult( scaling_matrix(.8, .8, 1),mat_mult(translation_matrix(2, .9, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> topFridgeHandle = mat_mult( scaling_matrix(.07, .5,.05), mat_mult(translation_matrix(18, 1.5, 10), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> bottomFridgeHandle = mat_mult( scaling_matrix(.07, .7,.05), mat_mult(translation_matrix(18, -.2, 10), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> counter3 = mat_mult( scaling_matrix(.9, 1, 1),mat_mult(translation_matrix(-1.068, -0.5, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> counter4= mat_mult( scaling_matrix(.9, .1, 1.1),mat_mult(translation_matrix(-1.08, -0.2, 0), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> counter5 = mat_mult( scaling_matrix(.9, 1, 2),mat_mult(translation_matrix(-2, -0.5, .24), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> counter6= mat_mult( scaling_matrix(.9, .1, 2.1),mat_mult(translation_matrix(-2, .2, .23), mat_mult(rotation_matrix_x(-90), build_cube())));
    vector<GLfloat> salt = mat_mult( scaling_matrix(.09, .3,.08), mat_mult(translation_matrix(8.5, .5, -6.5), mat_mult(rotation_matrix_y(90), build_cube())));
    vector<GLfloat> pepper = mat_mult( scaling_matrix(.09, .3,.1), mat_mult(translation_matrix(10, .5, -5.2), mat_mult(rotation_matrix_y(90), build_cube())));


    scene.reserve(test.size() + burner1.size()  + burner2.size() + burner3.size() + burner4.size() + oven.size() + ovenBack.size()  + ovenHandle.size());
    scene.insert( scene.end(), microwave.begin(), microwave.end());
    scene.insert( scene.end(), burner1.begin(), burner1.end());
    scene.insert( scene.end(), burner2.begin(), burner2.end());
    scene.insert( scene.end(), burner3.begin(), burner3.end());
    scene.insert( scene.end(), burner4.begin(), burner4.end());
    scene.insert( scene.end(), oven.begin(), oven.end());
    scene.insert( scene.end(), ovenBack.begin(), ovenBack.end());
    scene.insert( scene.end(), ovenHandle.begin(), ovenHandle.end());

    scene.reserve(microwaveHandle.size() + microwaveController.size());
    scene.insert( scene.end(), microwaveHandle.begin(), microwaveHandle.end());
    scene.insert( scene.end(), microwaveController.begin(), microwaveController.end());

    scene.reserve(counter1.size() + counter2.size());
    scene.insert( scene.end(), counter1.begin(), counter1.end());
    scene.insert( scene.end(), counter2.begin(), counter2.end());

    scene.reserve(fridgeBottom.size() + fridgeTop.size() + topFridgeHandle.size() + bottomFridgeHandle.size() );
    scene.insert( scene.end(), fridgeBottom.begin(), fridgeBottom.end());
    scene.insert( scene.end(), fridgeTop.begin(), fridgeTop.end());
    scene.insert( scene.end(), topFridgeHandle.begin(), topFridgeHandle.end());
    scene.insert( scene.end(), bottomFridgeHandle.begin(), bottomFridgeHandle.end());

    scene.reserve(counter3.size() + counter4.size());
    scene.insert( scene.end(), counter3.begin(), counter3.end());
    scene.insert( scene.end(), counter4.begin(), counter4.end());

    scene.reserve(counter5.size() + counter6.size());
    scene.insert( scene.end(), counter5.begin(), counter5.end());
    scene.insert( scene.end(), counter6.begin(), counter6.end());

    scene.reserve(salt.size() + pepper.size());
    scene.insert( scene.end(), salt.begin(), salt.end());
    scene.insert( scene.end(), pepper.begin(), pepper.end());

    return scene;
}

// Construct the color mapping of the scene
vector<GLfloat> init_color(vector<GLfloat> scene)
{
    vector<GLfloat> colors;
    for (int i = 0; i < scene.size(); i++)
    {
        colors.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }
    return colors;
}

void display_func()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Rotate the scene using the scene vector
    vector<GLfloat> scene = SCENE;
    scene = mat_mult(rotation_matrix_y(THETA), scene);
    scene = to_cartesian_coord(scene);  

    GLfloat *scene_vertices = vector2array(scene);
    GLfloat *color_vertices = vector2array(COLOR);
    // Pass the scene vertex pointer
    glVertexPointer(3,               // 3 components (x, y, z)
                    GL_FLOAT,        // Vertex type is GL_FLOAT
                    0,               // Start position in referenced memory
                    scene_vertices); // Pointer to memory location to read from

    // Pass the color vertex pointer
    glColorPointer(3,               // 3 components (r, g, b)
                   GL_FLOAT,        // Vertex type is GL_FLOAT
                   0,               // Start position in referenced memory
                   color_vertices); // Pointer to memory location to read from

    // Draw quad point planes: each 4 vertices
    glDrawArrays(GL_QUADS, 0, scene.size() / 3.0);
    glFlush(); //Finish rendering
    glutSwapBuffers();

    delete [] scene_vertices;
    delete [] color_vertices;
}

void idle_func()
{
    THETA = THETA + 0.3;
    display_func();
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // Create a window with rendering context and everything else we need
    glutCreateWindow("Assignment 3");

    setup();
    init_camera();
    // Setting global variables SCENE and COLOR with actual values
    SCENE = init_scene();
    COLOR = init_color(SCENE);

    // Set up our display function
    glutDisplayFunc(display_func);
    glutIdleFunc(idle_func);
    // Render our world
    glutMainLoop();

    // Remember to call "delete" on your dynmically allocated arrays
    // such that you don't suffer from memory leaks. e.g.
    // delete arr;

    return 0;
}
