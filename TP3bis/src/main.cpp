#include <iostream>
#include <vector>
#include <string>
#include "shader.h" // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/
#include <GLFW/glfw3.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;

void view_control(GLFWwindow *myWindow, mat4 &view_matrix, float dx);

int main()
{
  GLFWwindow *myWindow;
  int currentWindowHeight, currentWindowWidth;

  cout << "Debut du programme..." << endl;

  //==================================================
  //============= Creation de la fenetre =============
  //==================================================

  // Initialisation de GLFW
  if (!glfwInit())
  {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 16);              // Anti Aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if (!(myWindow = glfwCreateWindow(WIDTH, HEIGHT, "SI_INFO4", NULL, NULL)))
  {
    cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(myWindow);

  // Autorise GLFW a recevoir les appuis de touche
  glfwSetInputMode(myWindow, GLFW_STICKY_KEYS, GL_TRUE);

  // Initialisation de  GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    cout << "Echec de l'initialisation de GLEW" << endl;
    exit(EXIT_FAILURE);
  }

  // Verification des donnees du contexte OpenGL
  const GLubyte *renderer = glGetString(GL_RENDERER);
  cout << "Carte Graphique : " << renderer << endl;

  const GLubyte *version = glGetString(GL_VERSION);
  cout << "Driver OpenGL : " << version << endl;

  //==================================================
  //================= Initialisation =================
  //==================================================

  cout << "Initialisations..." << endl;

  // Definition de la couleur du fond
  glClearColor(0.1, 0.1, 0.1, 0.0);

  // Activation du test de profondeur
  glEnable(GL_DEPTH_TEST);

  // Activation du culling
  glEnable(GL_CULL_FACE);

  //-------------------------------------------------
  // Initialisation du shader programm

  // Compilation du shader programm
  GLuint programID = LoadShaders("../shader/vertex.glsl", "../shader/fragment.glsl");
  cout << "programID = " << programID << endl;

  
  //==================================================
  // Creation des buffers avec le chargement d'un maillage
  //==================================================
  Mesh m("../models/dragon.off"); // Lecture du maillage
  m.normalize();      // Met à l'échelle pour que le maillage remplisse la sphère unité
  m.colorize();       // Calcule une couleur en chaque sommet


  // Creation d'un VAO (c'est l'objet qui encapsule les VBOs et qu'on va manipuler)
  GLuint vaoID;
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID); // rendre ce VAO actif

  //==================================================
  // Création d'un buffer (VBO) pour les positions des sommets
  // avec vertexBufferID pour identifiant
  //==================================================

  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  cout << "vertexBufferID = " << vertexBufferID << endl;

  // Definition de vertexBufferID comme le buffer courant
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

  // Copie des donnees sur la carte graphique (dans vertexBufferID)
  // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

  // Version avec maillage
  //glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(vec3), m.vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(uint), m.vertices.data(), GL_STATIC_DRAW);


  // Obtention de l'ID de l'attribut "in_position" dans programID
  GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");

  // On autorise et indique a OpenGL comment lire les donnees
  glVertexAttribPointer(vertexPositionID, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(vertexPositionID);

  
  // Creation d'un buffer des couleurs
  GLuint colorBufferID;
  glGenBuffers(1, &colorBufferID);
  cout << "colorBufferID = " << colorBufferID << endl;

  // Definition de colorBufferID comme le buffer courant
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);

  // Copie des donnees sur la carte graphique (dans colorBufferID)
  glBufferData(GL_ARRAY_BUFFER, m.colors.size() * sizeof(uint), m.colors.data(), GL_STATIC_DRAW);

  // Obtention de l'ID de l'attribut "in_color" dans programID
  GLuint vertexColorID = glGetAttribLocation(programID, "in_color");

  // On autorise et indique a OpenGL comment lire les donnees
  glVertexAttribPointer(vertexColorID, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(vertexColorID);


  //==================================================
  // Creation d'un nouveau buffer pour les indices
  //==================================================

  GLuint indiceBufferID;
  glGenBuffers(1, &indiceBufferID);
  cout << "indiceBufferID = " << indiceBufferID << endl;
  
  // Definition de indiceBufferID comme le buffer courant de GL_ELEMENT_ARRAY_BUFFER
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);

  // Copie des donnees sur la carte graphique (dans indiceBufferID)
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vec3), indices.data(), GL_STATIC_DRAW);
  

  // Version avec maillage
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.faces.size() * sizeof(uint), m.faces.data(), GL_STATIC_DRAW);

  //==================================================
  // Creation d'un nouveau buffer pour les normales
  //==================================================

  // Creation d'un buffer des normales
  GLuint normalBufferID;
  glGenBuffers(1, &normalBufferID);
  cout << "normalBufferID = " << normalBufferID << endl;

  // Definition de normalBufferID comme le buffer courant
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);

  // Copie des donnees sur la carte graphique (dans normalBufferID)
  glBufferData(GL_ARRAY_BUFFER, m.normals.size() * sizeof(vec3), m.normals.data(), GL_STATIC_DRAW);

  // Obtention de l'ID de l'attribut "in_normal" dans programID
  GLuint vertexNormalID = glGetAttribLocation(programID, "in_normal");

  // On autorise et indique a OpenGL comment lire les donnees
  glVertexAttribPointer(vertexNormalID, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(vertexNormalID);

  glBindVertexArray(0); // Désactiver le VAO

  //------------------------------------------------
  // Initialisation des matrices MVP

  // Definition des matrices de transformation
  mat4 projection_matrix = perspective(45.0f, WIDTH / HEIGHT, 0.1f, 100.0f);
  mat4 view_matrix = lookAt(vec3(0.0, 0.0, 2), vec3(0.0), vec3(0.0, 1.0, 0.0));
  mat4 model_matrix = scale(mat4(1.0f), vec3(0.5));

  GLuint PmatrixID = glGetUniformLocation(programID, "ProjectionMatrix");
  cout << "PmatrixID = " << PmatrixID << endl;

  GLuint VmatrixID = glGetUniformLocation(programID, "ViewMatrix");
  cout << "VmatrixID = " << VmatrixID << endl;

  GLuint MmatrixID = glGetUniformLocation(programID, "ModelMatrix");
  cout << "MmatrixID = " << MmatrixID << endl;

  GLuint ToDrawID = glGetUniformLocation(programID, "ToDraw");
  cout << "ToDrawID = " << ToDrawID << endl;

  GLuint CurrentTimeID = glGetUniformLocation(programID, "CurrentTime");
  cout << "CurrentTimeID = " << CurrentTimeID << endl;

  //==================================================
  //=========== Debut des choses serieuses ===========
  //==================================================

  cout << "Debut de la boucle principale..." << endl;

  double init_time = glfwGetTime();
  double prec_time = init_time;
  double cur_time = init_time;
  double speed = 0.5;

  char title[100];
  // Boucle de dessin
  do
  {
    // Nettoyage de la zone de dessin (couleurs+profondeurs)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //==================================================
    //============= Calcul du Point de Vue =============
    //==================================================

    prec_time = cur_time;
    cur_time = glfwGetTime() - init_time;
    double delta_time = cur_time - prec_time;
    double fps = 1.0 / delta_time;
    sprintf(title, "INFO4 - SI - TP3 - %2.0f FPS", fps);
    glfwSetWindowTitle(myWindow, title);

    view_control(myWindow, view_matrix, speed * delta_time);

    //==================================================
    //===================== Dessin =====================
    //==================================================

    // Definition de programID comme le shader courant
    glUseProgram(programID);

    // Transmission des matrices au vertex shader
    glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));
    glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
    glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));

    
    cout.flush();

    glBindVertexArray(vaoID); // On active le VAO
    //glDrawElements(GL_TRIANGLES, m.faces.size(), GL_UNSIGNED_INT, 0);


    // Récupération de la taille actuelle de la fenêtre
    glfwGetWindowSize(myWindow, &currentWindowWidth, &currentWindowHeight);
    cout << "\rcurrentWindowWidth= " << currentWindowWidth << ", currentWindowHeight=" << currentWindowHeight << "\r";


    // Envoi du temps courant au vertex shader
    glUniform1f(CurrentTimeID, cur_time);


    // Dessin en haut à droite --------
    glViewport(currentWindowWidth/2, currentWindowHeight/2, currentWindowWidth/2, currentWindowHeight/2);
    glUniform1i(ToDrawID, 1); // Modification de la valeur de dessin
    glDrawElements(GL_TRIANGLES, m.faces.size(), GL_UNSIGNED_INT, 0);

    // Dessin en haut à gauche --------
    glViewport(0, currentWindowHeight/2, currentWindowWidth/2, currentWindowHeight/2);
    glUniform1i(ToDrawID, 2); // Modification de la valeur de dessin
    glDrawElements(GL_TRIANGLES, m.faces.size(), GL_UNSIGNED_INT, 0);

    // Dessin en bas à gauche --------
    glViewport(0, 0, currentWindowWidth/2, currentWindowHeight/2);
    glUniform1i(ToDrawID, 3); // Modification de la valeur de dessin
    glDrawElements(GL_TRIANGLES, m.faces.size(), GL_UNSIGNED_INT, 0);

    // Dessin en bas à droite --------
    glViewport(currentWindowWidth/2, 0, currentWindowWidth/2, currentWindowHeight/2);
    glUniform1i(ToDrawID, 4); // Modification de la valeur de dessin
    glDrawElements(GL_TRIANGLES, m.faces.size(), GL_UNSIGNED_INT, 0);
    
    
    glBindVertexArray(0); // On désactive le VAO

    // Echange des zones de dessin buffers
    glfwSwapBuffers(myWindow);

    // Traitement des évènements fenêtre, clavier, etc...
    glfwPollEvents();

    cout << "Temps ecoule (s) : " << cur_time << "\r";
    cout.flush();

  }                                                             // Execution de la boucle...
  while (glfwGetKey(myWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && // ... jusqu'a appui sur la touche ESC
         (!glfwWindowShouldClose(myWindow)));                   // ... ou fermeture de la fenetre

  cout << endl;

  // Ferme GLFW et OpenGL
  glfwTerminate();

  //==================================================
  //============== Nettoyage la memoire ==============
  //==================================================

  // Liberation des buffers
  glDeleteBuffers(1, &vaoID);
  glDeleteBuffers(1, &vertexBufferID);
  glDeleteBuffers(1, &colorBufferID);
  glDeleteBuffers(1, &indiceBufferID);
  glDeleteBuffers(1, &normalBufferID);

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}

void view_control(GLFWwindow *myWindow, mat4 &view_matrix, float dx)
{
  if (glfwGetKey(myWindow, GLFW_KEY_UP) == GLFW_PRESS)
  {
    vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, +dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, -dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
    axis = inverse(view_matrix) * axis;
    view_matrix = rotate(view_matrix, +dx, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_Z) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_S) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_Q) == GLFW_PRESS)
  {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_D) == GLFW_PRESS)
  {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_A) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  if (glfwGetKey(myWindow, GLFW_KEY_E) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }
}
