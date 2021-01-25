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

  //==================================================
  // ToDo : Initialiser
  //==================================================

  cout << "Initialisations..." << endl;

  // Compilation du shader program et génération de l'ID du Shader
  GLuint programID = LoadShaders("../shader/vao_vertex_shader.glsl", "../shader/fragment.glsl");
  // Demande d'utiliser le program créé juste au-dessus.
  glUseProgram(programID);

  // Définition d'un vecteur
  vec3 v(-1.0f, -1.0f, 0.0f);

  // Définition d'un tableau de vecteurs
  vec3 vertex[3] = {
      vec3(-0.5f, -0.5f, 0.0f),
      vec3(0.5f, -0.0f, 0.0f),
      vec3(-0.5f, 0.5f, 0.0f),
  };

  // Obtention de l'ID de l'attribut 'vertex_position' dans programID
  GLuint vertexPositionID = glGetAttribLocation(programID, "vertex_position");

  /* Création d'un VAO et récupération de son ID */
  GLuint vaoID;
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID); // Définition de notre VAO comme objet courant

  /* Création d'un BO et récupération de son ID */
  GLuint vboID;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID); // Définition de notre VBO comme buffer courant

  // Copie des données du CPU (dans vertex) vers le GPU (dans vboID).
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

  // On indique à OpenGL comment interpréter les données du VBO.
  glEnableVertexAttribArray(vertexPositionID);
  glVertexAttribPointer(
      vertexPositionID, // ID de l'attribut à configurer
      3,                // nombre de composantes par position (x,y,z)
      GL_FLOAT,         // types des composantes
      GL_FALSE,         // normalisation des composantes
      0,                // décalage des composantes
      (void *)0         // offset des composantes
  );

  // On désactive le VAO.
  glBindVertexArray(0);

  // Definition de la couleur du fond
  glClearColor(0.3f, 0.0f, 0.1f, 0.0f);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

    // On active le VAO.
    glBindVertexArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // On désactive le VAO.
    glBindVertexArray(0);

    // Echange des zones de dessin buffers
    glfwSwapBuffers(myWindow);

    cout << "Compteur : " << i++ << "\r";
    cout.flush();
    glfwWaitEvents();

  }                                                             // Execution de la boucle...
  while (glfwGetKey(myWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && // ... jusqu'a appui sur la touche ESC
         (!glfwWindowShouldClose(myWindow)));                   // ... ou fermeture de la fenetre

  cout << endl;

  /* On libère les buffers et objets */
  glDeleteBuffers(1, &vboID);
  glDeleteBuffers(1, &vaoID);

  // Ferme GLFW et OpenGL
  glfwTerminate();

  //==================================================
  // ToDo : Nettoyer la memoire
  //==================================================

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}
