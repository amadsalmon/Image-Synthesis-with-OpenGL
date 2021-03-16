#include <iostream>
#include <vector>
#include <string>
#include "shader.h" // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GLFW/glfw3.h>    // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;

void view_control( GLFWwindow* myWindow, mat4& view_matrix, float dx);

int main() {
  GLFWwindow* myWindow;

  cout << "Debut du programme..." << endl;

  //==================================================
  //============= Creation de la fenetre =============
  //==================================================

  // Initialisation de GLFW
  if(!glfwInit()) {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }
  
  glfwWindowHint(GLFW_SAMPLES, 4); // Anti Aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Ouverture d'une fenêtre
  // et creation d'un contexte OpenGL
   if (!(myWindow = glfwCreateWindow( WIDTH, HEIGHT, "SI_INFO4", NULL, NULL))) {
    cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(myWindow);

  // Autorise GLFW a recevoir les appuis de touche
  glfwSetInputMode( myWindow, GLFW_STICKY_KEYS, GL_TRUE);

  // Initialisation de  GLEW
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    cout << "Echec de l'initialisation de GLEW" << endl;
    exit(EXIT_FAILURE);
  }

  // Verification des donnees du contexte OpenGL
  const GLubyte* renderer = glGetString (GL_RENDERER);
  cout << "Carte Graphique : " << renderer << endl;
  
  const GLubyte* version = glGetString (GL_VERSION);
  cout << "Driver OpenGL : " << version << endl;
  

  //==================================================
  //================= Initialisation =================
  //==================================================
  
  cout << "Initialisations..." << endl;


  // Definition de la couleur du fond
  glClearColor(0.1, 0.1, 0.1, 0.0);

  //-------------------------------------------------
  // Initialisation du shader programm
    
  // Compilation du shader programm
  GLuint programID = LoadShaders( "../shader/vertex.glsl", "../shader/fragment.glsl" );
  cout << "programID = " << programID << endl;

  // Obtention du UniformLocation pour le temps (sert à l'animation)
  GLuint currentTimeID = glGetUniformLocation(programID, "currentTime");

  //-------------------------------------------------
  // Definition des sommets et indices du maillage (on recouvre l'ecran avec 4 sommets/2 triangles)
  vec3 vertices[] = {
      vec3(-1.0, -1.0, 0.0), // 0 (inférieur, gauche)       1-------3
      vec3(-1.0,  1.0, 0.0), // 1 (supérieur, gauche)       |       |
      vec3( 1.0, -1.0, 0.0), // 2 (inférieur, droit)        |       |
      vec3( 1.0,  1.0, 0.0)  // 3 (supérieur, droit)        0-------2
      };

  unsigned int indices[] = {0, 1, 3, 0, 3, 2};

  
  // Creation d'un VAO (c'est l'objet qui encapsule les VBOs et qu'on va manipuler)
  GLuint vaoID;
  glGenVertexArrays(1,&vaoID); 
  glBindVertexArray(vaoID); // rendre ce VAO actif
    
  //==================================================
  // Done : Creation d'un buffer (VBO) pour les positions des sommets
  // avec vertexBufferID pour identifiant
  //==================================================

  GLuint vertexBufferID;
  glGenBuffers(1, &vertexBufferID);
  cout << "vertexBufferID = " << vertexBufferID << endl;

  // Definition de vertexBufferID comme le buffer courant
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

  // Copie des donnees sur la carte graphique (dans vertexBufferID)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Obtention de l'ID de l'attribut "in_position" dans programID
  GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");
  
  // On autorise et indique a OpenGL comment lire les donnees
  glVertexAttribPointer(vertexPositionID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  glEnableVertexAttribArray(vertexPositionID);


  //==================================================
  // Creation d'un nouveau buffer pour les indices des triangles (topologie)
  //==================================================
  GLuint indiceBufferID;
  glGenBuffers(1, &indiceBufferID);

  // Definition de vertexBufferID comme le buffer courant
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);

  // Copie des donnees sur la carte graphique (dans vertexBufferID)
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

  glBindVertexArray(0); // Désactiver le VAO



  //-------------------------------------------------
  // Initialisation des matrices MVP

    
  // Definition des matrices de transformation
  mat4 model_matrix = mat4(1.0);
  mat4 view_matrix = lookAt(
      vec3(0.f, 0.f, 2.f),  // PLACE DE LA CAMERA
      vec3(0.f),            // POINT QUE LA CAMERA REGARDE
      vec3(0.f, 1.f, 0.f)); // VERTICALE DE LA CAMERA
  mat4 projection_matrix = perspective(
      45.0f,          // ANGLE DE VUE
      WIDTH / HEIGHT, // RAPPORT D'ASPECT DE LA FENETRE
      0.1f,           // LIMITE PROCHE DE LA PYRAMIDE DE VUE
      100.f);         //  LIMITE LOINTAINE DE LA PYRAMIDE DE VUE


  GLuint MmatrixID = glGetUniformLocation(programID, "ModelMatrix");
  cout << "MmatrixID = " << MmatrixID << endl;
  
  GLuint VmatrixID = glGetUniformLocation(programID, "ViewMatrix");
  cout << "VmatrixID = " << VmatrixID << endl;

  GLuint PmatrixID = glGetUniformLocation(programID, "ProjectionMatrix");
  cout << "PmatrixID = " << PmatrixID << endl;


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
  do{
    // Nettoyage de la zone de dessin (couleurs+profondeurs)
    int w,h;
    glfwGetWindowSize( myWindow, &w,&h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //==================================================
    //============= Calcul du Point de Vue =============
    //==================================================
      
    prec_time = cur_time;
    cur_time = glfwGetTime() - init_time;
    double delta_time = cur_time - prec_time;
    sprintf(title,"Polytech RICM 4 - TP5 - %2.0f FPS",1.0/ delta_time);
    glfwSetWindowTitle( myWindow, title);

    // TODO: Interaction avec la camera 
    view_control( myWindow, view_matrix, speed * delta_time);

    //==================================================
    //===================== Dessin =====================
    //==================================================

    // Definition de programID comme le shader courant
    glUseProgram(programID);

    /*------ Transmission des variables uniform aux shaders ------*/
    // Transmission des matrices au vertex shader
    glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));
    glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
    glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));
    
    // Transmission du temps au fragment shader pour l'animation
    glUniform1f(currentTimeID, (float) cur_time);

    // set viewport, enable VAO and draw 
    //glViewport(0,0,w,h); // En commentaire car cela cause des problèmes d'affichage sur ma machine (contact par mail à ce propos)
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

      
    // Echange des zones de dessin buffers
    glfwSwapBuffers( myWindow);

    // Traitement des évènements fenêtre, clavier, etc...
    glfwPollEvents();
      
    cout << "Temps ecoule (s) : " << cur_time << "\r";
    cout.flush();
    
    
  } // Execution de la boucle...
  while( glfwGetKey( myWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
	 (!glfwWindowShouldClose( myWindow))        );  // ... ou fermeture de la fenetre

  cout << endl;

  // Ferme GLFW et OpenGL
  glfwTerminate();
    
    
    
  //==================================================
  //============== Nettoyage la memoire ==============
  //==================================================
    
  // Liberation des buffers
  glDeleteBuffers(1, &vaoID);
  glDeleteBuffers(1, &vertexBufferID);
  glDeleteBuffers(1, &indiceBufferID);


  cout << "Fin du programme..." << endl;
    
    
  return EXIT_SUCCESS;
}

/**
 * Effectue des changements de point de vue d'importance dx grâce à des transformations de la matrice de vue view_matrix selon les touches du clavier pressées.
 * Attention : les touches sont celles du clavier QWERTY.
 * */
void view_control(GLFWwindow *aWindow, mat4 &view_matrix, float dx)
{
  // Translation vers le haut
  if (glfwGetKey(aWindow, GLFW_KEY_UP) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  // Translation vers le bas
  if (glfwGetKey(aWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  // Translation vers la droite
  if (glfwGetKey(aWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  // Translation vers la gauche
  if (glfwGetKey(aWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  // Zoom avant - (touche "Z" du clavier QWERTY, touche "W" du clavier AZERTY) 
  if (glfwGetKey(aWindow, GLFW_KEY_Z) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * dx;
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }

  // Zoom avant - (touche "X")
  if (glfwGetKey(aWindow, GLFW_KEY_X) == GLFW_PRESS)
  {
    vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * (-dx);
    axis = inverse(view_matrix) * axis;
    view_matrix = translate(view_matrix, vec3(axis));
  }
}
