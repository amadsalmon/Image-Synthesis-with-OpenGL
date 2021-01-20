#include <iostream>
#include "shader.hpp" // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/
#include <GLFW/glfw3.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html

using namespace glm;
using namespace std;

int main()
{
  cout << "Debut du programme..." << endl;

  GLFWwindow *myWindow;

  // Initialisation de GLFW
  if (!glfwInit())
  {
    cout << "Echec de l'initialisation de GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);               // Anti Aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // OpenGL 2.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Ouverture d'une fenêtre en 1024x768
  // et creation d'un contexte OpenGL
  if (!(myWindow = glfwCreateWindow(1024, 768, "SI_INFO4", NULL, NULL)))
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

  // Compilation du shader program et generation de l ’ID du Shader
  GLuint programID = LoadShaders("../shader/vertex.glsl", "../shader/fragment.glsl");

  //==================================================
  // ToDo : Initialiser
  //==================================================

  cout << "Initialisations..." << endl;

  // Definition de la couleur du fond
  glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

  cout << "Debut de la boucle principale..." << endl;
  unsigned int i = 0;

  // Boucle de dessin
  do
  {

    // Nettoyage de la zone de dessin
    glClear(GL_COLOR_BUFFER_BIT);

    //==================================================
    // ToDo : Dessiner
    //==================================================

    glColor3f(0, 125, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    // Echange des zones de dessin buffers
    glfwSwapBuffers(myWindow);

    cout << "Compteur : " << i++ << "\r";
    cout.flush();
    glfwWaitEvents();

  }                                                             // Execution de la boucle...
  while (glfwGetKey(myWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && // ... jusqu'a appui sur la touche ESC
         (!glfwWindowShouldClose(myWindow)));                   // ... ou fermeture de la fenetre

  cout << endl;

  // Ferme GLFW et OpenGL
  glfwTerminate();

  //==================================================
  // ToDo : Nettoyer la memoire
  //==================================================

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}
