#include <iostream>
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/
#include <GLFW/glfw3.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp>  // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h" // Help to load shaders from files

using namespace glm;
using namespace std;

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

void view_control(GLFWwindow *aWindow, mat4 &view_matrix, float dx)
{
  // exemple de controle clavier
  if (glfwGetKey(aWindow, GLFW_KEY_UP) == GLFW_PRESS)
  {
    // appliquer une transformation (dx) à la matrice view
  }

  // ...
}

int main()
{
  GLFWwindow *myWindow;

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

  glfwWindowHint(GLFW_SAMPLES, 4);               // Anti Aliasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 2.1
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
  glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

  GLuint programID = LoadShaders("../shader/vertex.glsl", "../shader/fragment.glsl");

  // Definition d'un tableau de vecteurs définissant la geometrie
  vec3 vertex[] = {
      vec3(-0.5, -0.5, -0.5),
      vec3(0.5, -0.5, -0.5),
      vec3(-0.5, 0.5, -0.5),
      vec3(-0.5, 0.5, -0.5),
      vec3(0.5, -0.5, -0.5),
      vec3(0.5, 0.5, -0.5)};

  // Creation d'un VAO (c'est l'objet qu'on va manipuler)
  GLuint vaoID;
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID); // rendre ce VAO actif

  // Creation d'un buffer (VBO) avec vboID pour identifiant
  GLuint vboID;
  glGenBuffers(1, &vboID); // créer le VBO associé aux sommets

  // Definition de vboID comme le buffer courant
  // et lie automatiquement ce VBO au VAO actif
  glBindBuffer(GL_ARRAY_BUFFER, vboID);

  // Copie des donnees sur la carte graphique (dans vboID)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

  // Obtention de l'ID de l'attribut "vertex_position" dans programID
  GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");

  // On indique a OpenGL comment lire les donnees
  glEnableVertexAttribArray(vertexPositionID);
  glVertexAttribPointer(
      vertexPositionID, // ID de l'attribut à configurer
      3,                // nombre de composante par position (x, y, z)
      GL_FLOAT,         // type des composantes
      GL_FALSE,         // normalisation des composantes
      0,                // decalage des composantes
      (void *)0         // offset des composantes
  );

  glBindVertexArray(0); // Désactiver le VAO

  

  cout << "Debut de la boucle principale..." << endl;
  unsigned int i = 0;

  // Boucle de dessin
  do
  {

    // Nettoyage de la zone de dessin
    glClear(GL_COLOR_BUFFER_BIT);

    //==================================================
    // ToDo : Modifier les matrices de transformation
    //==================================================

    //==================================================
    //===================== Dessin =====================
    //==================================================
    glUseProgram(programID); // Definition de programID comme le shader courant

    //==================================================
    // ToDo : Transmettre les matrices au vertex shader
    //==================================================
    
    
    
    glBindVertexArray(vaoID); // On active le VAO

    // on dessine le contenu de tous les VBOs (buffers) associés à ce VAO
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0); // On désactive le VAO

    // Echange des zones de dessin buffers
    glfwSwapBuffers(myWindow);
    glfwSwapBuffers(myWindow);
    glfwPollEvents();

    cout << "Compteur : " << i++ << "\r";
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
  glDeleteBuffers(1, &vboID);
  glDeleteBuffers(1, &vaoID);

  cout << "Fin du programme..." << endl;

  return EXIT_SUCCESS;
}
