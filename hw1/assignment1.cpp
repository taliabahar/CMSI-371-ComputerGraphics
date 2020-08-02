/***
 assignment1.cpp
 Assignment-1: Cartoonify
 
 Name: Bahar, Talia
 
 Collaborators: Maya Pegler-Gordon, Sam Gibson, Masao 

 Project Summary: For this project I used Bezier's algorithm to draw Shrek. 
 This project utilized the functions generate_points(), draw_curve(), 
 and display() to iteratively attempt to recreate an image of shrek given a 
 set of points between 1 and -1. I also created the helper function findMidpoint(), 
 which was utilized in generate_points() to find the midpoint of every set of points given.
 Masao also helped me add a debug method so that I could test the accuracy of my algorithm.
 ***/
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
using namespace std;

class Vertex {
  GLfloat x, y;

public:
  Vertex(GLfloat, GLfloat);
  GLfloat get_y() { return y; };
  GLfloat get_x() { return x; };
};

Vertex::Vertex(GLfloat X, GLfloat Y) {
  x = X;
  y = Y;
}

string debug(vector<Vertex> vertices) {
  string result = "[\n";
  for (int i = 0; i < vertices.size(); i++) {
    // cout << "ITERATION: " << i << endl << flush;
    result += "  (";
    result += to_string(vertices[i].get_x());
    result += ", ";
    result += to_string(vertices[i].get_y());
    result += ")\n";
  }
  result += "]\n";
  return result;
}

void setup() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

Vertex findMidpoint(Vertex vertex1, Vertex vertex2) {
  Vertex midpoint(((vertex1.get_x() + vertex2.get_x()) / 2), ((vertex1.get_y() + vertex2.get_y()) / 2));
  return midpoint;
}

vector<Vertex> generate_points(vector<Vertex> control_points) {
  vector<Vertex> M;
  vector<Vertex> firstHalf;
  vector<Vertex> secondHalf;
  int startingPointsSize = control_points.size();
  for (int i = 0; i < startingPointsSize; i++) {
    int midpointLength = control_points.size();
    for (int j = 0; j < midpointLength - 1; j++) {
      Vertex m = findMidpoint(control_points.at(j), control_points.at(j + 1));
      M.push_back(m);
    }
    if (control_points.size() == 1) {
      firstHalf.push_back(control_points.front());
    } else {
      firstHalf.push_back(control_points.front());
      secondHalf.insert(secondHalf.begin(), control_points.back());
    }
    control_points = M;
    M.clear();
  }
  firstHalf.insert(firstHalf.end(), secondHalf.begin(), secondHalf.end());
  return firstHalf;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {
  vector<Vertex> points = control_points;

  while (n_iter != 0) {
    points = generate_points(points);
    // cout << "POINTS: " << debug(points) << endl << flush;
    n_iter--;
  }

  glPointSize(5.0f);
  glColor3ub(176, 196, 0);
  glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); i++) {
      glVertex2f(
        points[i].get_x(),
        points[i].get_y()
      );
    }
  glEnd();

  glColor3ub(101, 131, 0);
  glBegin(GL_LINES);
    for (int i = 0; i < points.size() - 1; i++) {
      glVertex2f(
        points[i].get_x(),
        points[i].get_y()
      );
      glVertex2f(
        points[i+1].get_x(),
        points[i+1].get_y()
      );
    }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 0.0f);

  // cout << "TEST: " << debug(control_points_test) << endl << flush;
  vector<Vertex> control_points_topHead;
  control_points_topHead.push_back(Vertex(0.0f,.775f));
  control_points_topHead.push_back(Vertex(.101f,.764f));
  control_points_topHead.push_back(Vertex(.202f,.726f));
  control_points_topHead.push_back(Vertex(.3003f,.656f));
  control_points_topHead.push_back(Vertex(.3513f,.602f));
  control_points_topHead.push_back(Vertex(.405f,.518f));
  control_points_topHead.push_back(Vertex(.447f,.457f));
  control_points_topHead.push_back(Vertex(.4744f,.41f));
  control_points_topHead.push_back(Vertex(.4865f,.3545f));
  control_points_topHead.push_back(Vertex(.494f,.336f));
  control_points_topHead.push_back(Vertex(.478f,.382f));

  vector<Vertex> control_points_rightEar;
  control_points_rightEar.push_back(Vertex(.478f,.382f));
  control_points_rightEar.push_back(Vertex(.494f,.336f));
  control_points_rightEar.push_back(Vertex(.526,.3656));
  control_points_rightEar.push_back(Vertex(.5595,.38));
  control_points_rightEar.push_back(Vertex(.5805,.392));
  control_points_rightEar.push_back(Vertex(.6,.401));
  control_points_rightEar.push_back(Vertex(.623,.42));
  control_points_rightEar.push_back(Vertex(.6404,.439));
  control_points_rightEar.push_back(Vertex(.656,.4564));
  control_points_rightEar.push_back(Vertex(.675,.478));
  control_points_rightEar.push_back(Vertex(.691,.706));
  control_points_rightEar.push_back(Vertex(.706,.5094));
  control_points_rightEar.push_back(Vertex(.722,.5196));

  vector<Vertex> control_points_rightEarSide;
  control_points_rightEarSide.push_back(Vertex(.722,.5196));
  control_points_rightEarSide.push_back(Vertex(.7343,.524));
  control_points_rightEarSide.push_back(Vertex(.7455,.521));
  control_points_rightEarSide.push_back(Vertex(.756,.515));
  control_points_rightEarSide.push_back(Vertex(.7636,.5068));
  control_points_rightEarSide.push_back(Vertex(.7744,.495));
  control_points_rightEarSide.push_back(Vertex(.7797,.485));
  control_points_rightEarSide.push_back(Vertex(.786,.473));
  control_points_rightEarSide.push_back(Vertex(.7912,.4603));
  control_points_rightEarSide.push_back(Vertex(.793,.4483));
  control_points_rightEarSide.push_back(Vertex(.796,.436));
  control_points_rightEarSide.push_back(Vertex(.7988,.4215));
  control_points_rightEarSide.push_back(Vertex(.8003,.407));
  control_points_rightEarSide.push_back(Vertex(.8017,.3916));
  control_points_rightEarSide.push_back(Vertex(.802,.375));
  control_points_rightEarSide.push_back(Vertex(.8,.3573));
  control_points_rightEarSide.push_back(Vertex(.794,.3436));

  vector<Vertex> control_points_rightEarBottom;
  control_points_rightEarBottom.push_back(Vertex(.794,.3436));
  control_points_rightEarBottom.push_back(Vertex(.7872,.331));
  control_points_rightEarBottom.push_back(Vertex(.772,.325));
  control_points_rightEarBottom.push_back(Vertex(.751,.323));
  control_points_rightEarBottom.push_back(Vertex(.7243,.3234));
  control_points_rightEarBottom.push_back(Vertex(.7,.323));
  control_points_rightEarBottom.push_back(Vertex(.6665,.3244));
  control_points_rightEarBottom.push_back(Vertex(.6445,.324));
  control_points_rightEarBottom.push_back(Vertex(.607,.315));
  control_points_rightEarBottom.push_back(Vertex(.5805,.3025));
  control_points_rightEarBottom.push_back(Vertex(.56,.292));
  control_points_rightEarBottom.push_back(Vertex(.543,.28));
  control_points_rightEarBottom.push_back(Vertex(.527,.2655));
  control_points_rightEarBottom.push_back(Vertex(.51,.254));

  vector<Vertex> control_points_rightSideOfFace;
  control_points_rightSideOfFace.push_back(Vertex(.51,.254));
  control_points_rightSideOfFace.push_back(Vertex(.509,.2406));
  control_points_rightSideOfFace.push_back(Vertex(.526,.215));
  control_points_rightSideOfFace.push_back(Vertex(.552,.1595));
  control_points_rightSideOfFace.push_back(Vertex(.565,.122));
  control_points_rightSideOfFace.push_back(Vertex(.5714,.0824));
  control_points_rightSideOfFace.push_back(Vertex(.58,.035));
  control_points_rightSideOfFace.push_back(Vertex(.567,.0054));
  control_points_rightSideOfFace.push_back(Vertex(.5606,-.04));
  control_points_rightSideOfFace.push_back(Vertex(.556,-.078));
  control_points_rightSideOfFace.push_back(Vertex(.536,-.211));
  control_points_rightSideOfFace.push_back(Vertex(.483,-.309));
  control_points_rightSideOfFace.push_back(Vertex(.412,-.392));
  control_points_rightSideOfFace.push_back(Vertex(.324,-.473));
  control_points_rightSideOfFace.push_back(Vertex(.212,-.527));
  control_points_rightSideOfFace.push_back(Vertex(.019,-.55));

  vector<Vertex> control_points_leftSideOfFace;
  control_points_leftSideOfFace.push_back(Vertex(.019,-.55));
  control_points_leftSideOfFace.push_back(Vertex(-.13,-.52));
  control_points_leftSideOfFace.push_back(Vertex(-.253,-.455));
  control_points_leftSideOfFace.push_back(Vertex(-.37,-.36));
  control_points_leftSideOfFace.push_back(Vertex(-.462,-.243));
  control_points_leftSideOfFace.push_back(Vertex(-.503,-.117));
  control_points_leftSideOfFace.push_back(Vertex(-.55,.047));
  control_points_leftSideOfFace.push_back(Vertex(-.559,.175));
  control_points_leftSideOfFace.push_back(Vertex(-.533,.259));
  control_points_leftSideOfFace.push_back(Vertex(-.476,.362));

  vector<Vertex> control_points_leftEarBottom;
  control_points_leftEarBottom.push_back(Vertex(-.476,.362));
  control_points_leftEarBottom.push_back(Vertex(-.533,.259));
  control_points_leftEarBottom.push_back(Vertex(-.482,.39));
  control_points_leftEarBottom.push_back(Vertex(-.506,.448));
  control_points_leftEarBottom.push_back(Vertex(-.547,.487));
  control_points_leftEarBottom.push_back(Vertex(-.596,.518));
  control_points_leftEarBottom.push_back(Vertex(-.66,.537));
  control_points_leftEarBottom.push_back(Vertex(-.714,.559));

  vector<Vertex> control_points_leftEarSide;
  control_points_leftEarSide.push_back(Vertex(-.714,.559));
  control_points_leftEarSide.push_back(Vertex(-.74,.607));
  control_points_leftEarSide.push_back(Vertex(-.723,.662));
  control_points_leftEarSide.push_back(Vertex(-.691,.704));
  control_points_leftEarSide.push_back(Vertex(-.642,.735));

  vector<Vertex> control_points_leftEarTop;
  control_points_leftEarTop.push_back(Vertex(-.642,.735));
  control_points_leftEarTop.push_back(Vertex(-.614,.736));
  control_points_leftEarTop.push_back(Vertex(-.59,.708));
  control_points_leftEarTop.push_back(Vertex(-.571,.674));
  control_points_leftEarTop.push_back(Vertex(-.562,.65));
  control_points_leftEarTop.push_back(Vertex(-.56,.627));
  control_points_leftEarTop.push_back(Vertex(-.528,.582));
  control_points_leftEarTop.push_back(Vertex(-.489,.538));
  control_points_leftEarTop.push_back(Vertex(-.46,.514));
  control_points_leftEarTop.push_back(Vertex(-.429,.492));

  vector<Vertex> control_points_leftTopOfHead;
  control_points_leftTopOfHead.push_back(Vertex(-.429,.492));
  control_points_leftTopOfHead.push_back(Vertex(-.404,.505));
  control_points_leftTopOfHead.push_back(Vertex(-.37,.562));
  control_points_leftTopOfHead.push_back(Vertex(-.317,.626));
  control_points_leftTopOfHead.push_back(Vertex(-.23,.704));
  control_points_leftTopOfHead.push_back(Vertex(-.148,.748));
  control_points_leftTopOfHead.push_back(Vertex(-.078,.767));
  control_points_leftTopOfHead.push_back(Vertex(0.0f,.775f));
    
  vector<Vertex> control_points_leftDimple;
  control_points_leftDimple.push_back(Vertex(-.247,.202));
  control_points_leftDimple.push_back(Vertex(-.338,.174));
  control_points_leftDimple.push_back(Vertex(-.356,.13));
  control_points_leftDimple.push_back(Vertex(-.372,.058));
  control_points_leftDimple.push_back(Vertex(-.37,.006));
  control_points_leftDimple.push_back(Vertex(-.363,-.062));
  control_points_leftDimple.push_back(Vertex(-.34,-.011));
  control_points_leftDimple.push_back(Vertex(-.31,-.164));

  vector<Vertex> control_points_rightDimple;
  control_points_rightDimple.push_back(Vertex(.404,.103));
  control_points_rightDimple.push_back(Vertex(.466,.04));
  control_points_rightDimple.push_back(Vertex(.47,-.048));
  control_points_rightDimple.push_back(Vertex(.453,-.0116));
  control_points_rightDimple.push_back(Vertex(.39,-.21));

  vector<Vertex> control_points_smile;
  control_points_smile.push_back(Vertex(.398,-.005));
  control_points_smile.push_back(Vertex(.312,-.03));
  control_points_smile.push_back(Vertex(.213,-.033));
  control_points_smile.push_back(Vertex(.007,.023));
  control_points_smile.push_back(Vertex(-.147,.06));
  control_points_smile.push_back(Vertex(-.283,.127));

  vector<Vertex> control_points_chin;
  control_points_chin.push_back(Vertex(.27,-.354));
  control_points_chin.push_back(Vertex(.146,-.302));
  control_points_chin.push_back(Vertex(.017,-.276));
  control_points_chin.push_back(Vertex(-.124,-.317));
  control_points_chin.push_back(Vertex(-.19,-.36));
  
  vector<Vertex> control_points_leftEyebrowTop;
  control_points_leftEyebrowTop.push_back(Vertex(.036,.572));
  control_points_leftEyebrowTop.push_back(Vertex(-.079,.606));
  control_points_leftEyebrowTop.push_back(Vertex(-.156,.617));
  control_points_leftEyebrowTop.push_back(Vertex(-.19,.612));
  control_points_leftEyebrowTop.push_back(Vertex(-.232,.594));
  control_points_leftEyebrowTop.push_back(Vertex(-.269,.536));
  control_points_leftEyebrowTop.push_back(Vertex(-.275,.53));

  vector<Vertex> control_points_leftEyebrowBottom;
  control_points_leftEyebrowBottom.push_back(Vertex(-.275,.53));
  control_points_leftEyebrowBottom.push_back(Vertex(-.226,.551));
  control_points_leftEyebrowBottom.push_back(Vertex(-.163,.562));
  control_points_leftEyebrowBottom.push_back(Vertex(-.113,.565));
  control_points_leftEyebrowBottom.push_back(Vertex(-.57,.556));
  control_points_leftEyebrowBottom.push_back(Vertex(-.275,.53));
  control_points_leftEyebrowBottom.push_back(Vertex(.005,.53));

  vector<Vertex> control_points_leftEyebrow;
  control_points_leftEyebrow.push_back(Vertex(.005,.53));
  control_points_leftEyebrow.push_back(Vertex(.036,.572));

  vector<Vertex> control_points_rightEyebrowTop;
  control_points_rightEyebrowTop.push_back(Vertex(.232,.526));
  control_points_rightEyebrowTop.push_back(Vertex(.288,.521));
  control_points_rightEyebrowTop.push_back(Vertex(.36,.507));
  control_points_rightEyebrowTop.push_back(Vertex(.404,.494));
  control_points_rightEyebrowTop.push_back(Vertex(.438,.47));
  control_points_topHead.push_back(Vertex(.447f,.457f));
  control_points_topHead.push_back(Vertex(.4744f,.41f));

  vector<Vertex> control_points_rightEyebrowBottom;
  control_points_rightEyebrowBottom.push_back(Vertex(.4744f,.41f));
  control_points_rightEyebrowBottom.push_back(Vertex(.422,.438));
  control_points_rightEyebrowBottom.push_back(Vertex(.376,.454));
  control_points_rightEyebrowBottom.push_back(Vertex(.323,.465));
  control_points_rightEyebrowBottom.push_back(Vertex(.266,.478));
  control_points_rightEyebrowBottom.push_back(Vertex(.22,.484));

  vector<Vertex> control_points_rightEyebrow;
  control_points_rightEyebrow.push_back(Vertex(.22,.484));
  control_points_rightEyebrow.push_back(Vertex(.232,.526));

  vector<Vertex> control_points_leftEyeTop;
  control_points_leftEyeTop.push_back(Vertex(-.23,.406));
  control_points_leftEyeTop.push_back(Vertex(-.183,.433));
  control_points_leftEyeTop.push_back(Vertex(-.127,.4445));
  control_points_leftEyeTop.push_back(Vertex(-.081,.425));
  control_points_leftEyeTop.push_back(Vertex(-.041,.368));

  vector<Vertex> control_points_leftEyeBottom;
  control_points_leftEyeBottom.push_back(Vertex(-.041,.368));
  control_points_leftEyeBottom.push_back(Vertex(-.09,.359));
  control_points_leftEyeBottom.push_back(Vertex(-.153,.359));
  control_points_leftEyeBottom.push_back(Vertex(-.1975,.374));
  control_points_leftEyeBottom.push_back(Vertex(-.23,.406));

  vector<Vertex> control_points_leftEyePupil;
  control_points_leftEyePupil.push_back(Vertex(-.184,.384));
  control_points_leftEyePupil.push_back(Vertex(-.17,.407));
  control_points_leftEyePupil.push_back(Vertex(-.144,.418));
  control_points_leftEyePupil.push_back(Vertex(-.112,.401));
  control_points_leftEyePupil.push_back(Vertex(-.1045,.37));

  vector<Vertex> control_points_rightEyePupil;
  control_points_rightEyePupil.push_back(Vertex(.258,.315));
  control_points_rightEyePupil.push_back(Vertex(.266,.3375));
  control_points_rightEyePupil.push_back(Vertex(.293,.349));
  control_points_rightEyePupil.push_back(Vertex(.3206,.34));
  control_points_rightEyePupil.push_back(Vertex(.3323,.3125));

  vector<Vertex> control_points_rightEyeTop;
  control_points_rightEyeTop.push_back(Vertex(.221,.324));
  control_points_rightEyeTop.push_back(Vertex(.25,.355));
  control_points_rightEyeTop.push_back(Vertex(.31,.371));
  control_points_rightEyeTop.push_back(Vertex(.361,.355));
  control_points_rightEyeTop.push_back(Vertex(.404,.309));

  vector<Vertex> control_points_rightEyeBottom;
  control_points_rightEyeBottom.push_back(Vertex(.404,.309));
  control_points_rightEyeBottom.push_back(Vertex(.358,.299));
  control_points_rightEyeBottom.push_back(Vertex(.307,.297));
  control_points_rightEyeBottom.push_back(Vertex(.266,.306));
  control_points_rightEyeBottom.push_back(Vertex(.221,.324));

  vector<Vertex> control_points_noseCurve;
  control_points_noseCurve.push_back(Vertex(.015,.2));
  control_points_noseCurve.push_back(Vertex(.1,.16));
  control_points_noseCurve.push_back(Vertex(.174,.2));

  vector<Vertex> control_points_noseCurveTop;
  control_points_noseCurveTop.push_back(Vertex(-.102,.186));
  control_points_noseCurveTop.push_back(Vertex(-.133,.25));
  control_points_noseCurveTop.push_back(Vertex(-.079,.274));
  control_points_noseCurveTop.push_back(Vertex(-.022,.3));
  control_points_noseCurveTop.push_back(Vertex(.04,.353));
  control_points_noseCurveTop.push_back(Vertex(.11,.364));
  control_points_noseCurveTop.push_back(Vertex(.167,.348));
  control_points_noseCurveTop.push_back(Vertex(.222,.29));
  control_points_noseCurveTop.push_back(Vertex(.273,.248));
  control_points_noseCurveTop.push_back(Vertex(.304,.204));

  control_points_noseCurveTop.push_back(Vertex(.307,.163));
  control_points_noseCurveTop.push_back(Vertex(.29,.13));

  vector<Vertex> control_points_noseLeftHole;
  control_points_noseLeftHole.push_back(Vertex(.025,.145));
  control_points_noseLeftHole.push_back(Vertex(.0,.178));
  control_points_noseLeftHole.push_back(Vertex(-.037,.196));
  control_points_noseLeftHole.push_back(Vertex(-.08,.18));
  control_points_noseLeftHole.push_back(Vertex(-.045,.16));
  control_points_noseLeftHole.push_back(Vertex(-.02,.152));
  control_points_noseLeftHole.push_back(Vertex(.025,.145));

  vector<Vertex> control_points_noseRightHole;
  control_points_noseRightHole.push_back(Vertex(.186,.122));
  control_points_noseRightHole.push_back(Vertex(.208,.142));
  control_points_noseRightHole.push_back(Vertex(.233,.149));
  control_points_noseRightHole.push_back(Vertex(.264,.155));
  control_points_noseRightHole.push_back(Vertex(.282,.148));
  control_points_noseRightHole.push_back(Vertex(.273,.129));
  control_points_noseRightHole.push_back(Vertex(.238,.126));
  control_points_noseRightHole.push_back(Vertex(.186,.122));

  draw_curve(control_points_topHead, 10);
  draw_curve(control_points_rightEar, 10);
  draw_curve(control_points_rightEarSide, 10);
  draw_curve(control_points_rightEarBottom, 10);
  draw_curve(control_points_rightSideOfFace, 10);
  draw_curve(control_points_leftSideOfFace, 10);
  draw_curve(control_points_leftEarBottom, 10);
  draw_curve(control_points_leftEarSide, 10);
  draw_curve(control_points_leftEarTop, 10);
  draw_curve(control_points_leftTopOfHead, 10);

  draw_curve(control_points_leftDimple, 10);
  draw_curve(control_points_rightDimple, 10);

  draw_curve(control_points_smile, 10);
  draw_curve(control_points_chin, 10);

  draw_curve(control_points_leftEyebrowTop, 10);
  draw_curve(control_points_leftEyebrowBottom, 10);
  draw_curve(control_points_leftEyebrow, 10);
  draw_curve(control_points_rightEyebrowTop, 10);
  draw_curve(control_points_rightEyebrowBottom, 10);
  draw_curve(control_points_rightEyebrow, 10);

  draw_curve(control_points_rightEyeTop, 10);
  draw_curve(control_points_leftEyeTop, 10);
  draw_curve(control_points_rightEyeBottom, 10);
  draw_curve(control_points_leftEyeBottom, 10);
  draw_curve(control_points_leftEyePupil, 10);
  draw_curve(control_points_rightEyePupil, 10);

  draw_curve(control_points_noseCurve, 10);
  draw_curve(control_points_noseCurveTop, 3);
  draw_curve(control_points_noseLeftHole, 10);
  draw_curve(control_points_noseRightHole, 10);

  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);  // Set your own window size
  glutCreateWindow("Assignment 1");
  setup();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
