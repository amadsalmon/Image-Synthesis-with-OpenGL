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

/**
 * Effectue des changements de point de vue d'importance dx grâce à des transformations de la matrice de vue view_matrix selon les touches du clavier pressées.
 * Attention : les touches sont celles du clavier QWERTY.
 * */
void view_control(GLFWwindow *aWindow, mat4 &view_matrix, float dx)
{
  // Translation vers le haut
  if (glfwGetKey(aWindow, GLFW_KEY_UP) == GLFW_PRESS)
  {
    view_matrix = translate(view_matrix, vec3(0.0f, dx, 0.0f));
  }

  // Translation vers le bas
  if (glfwGetKey(aWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    view_matrix = translate(view_matrix, vec3(0.0f, -dx, 0.0f));
  }

  // Translation vers la droite
  if (glfwGetKey(aWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    view_matrix = translate(view_matrix, vec3(dx, 0.0f, 0.0f));
  }

  // Translation vers la gauche
  if (glfwGetKey(aWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
  {
    view_matrix = translate(view_matrix, vec3(-dx, 0.0f, 0.0f));
  }

  // Rotation directe autour de l'axe x - (touche "I")
  if (glfwGetKey(aWindow, GLFW_KEY_I) == GLFW_PRESS)
  {
    view_matrix = rotate(view_matrix, dx, vec3(1.0f, 0.0f, 0.0f));
  }

   // Rotation directe autour de l'axe y - (touche "J")
  if (glfwGetKey(aWindow, GLFW_KEY_J) == GLFW_PRESS)
  {
    view_matrix = rotate(view_matrix, dx, vec3(0.0f, 1.0f, 0.0f));
  }

   // Rotation directe autour de l'axe z - (touche "K")
  if (glfwGetKey(aWindow, GLFW_KEY_K) == GLFW_PRESS)
  {
    view_matrix = rotate(view_matrix, dx, vec3(0.0f, 0.0f, 1.0f));
  }

  // Zoom avant - (touche "Z" du clavier QWERTY, touche "W" du clavier AZERTY) 
  if (glfwGetKey(aWindow, GLFW_KEY_Z) == GLFW_PRESS)
  {
    view_matrix = scale(view_matrix, vec3(1.0f - dx, 1.0f - dx, 1.0f - dx));
  }

  // Zoom avant - (touche "X")
  if (glfwGetKey(aWindow, GLFW_KEY_X) == GLFW_PRESS)
  {
    view_matrix = scale(view_matrix, vec3(1.0f + dx, 1.0f + dx, 1.0f + dx));
  }
}

int main()
{
  GLFWwindow *myWindow;

  cout << " -- Debut du programme." << endl;

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

  //==================================================
  //  Création des matrices de transformation
  //==================================================

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
  // Recuperation des ID des matrices dans le shader program
  GLuint MmatrixID = glGetUniformLocation(programID, "ModelMatrix");
  GLuint VmatrixID = glGetUniformLocation(programID, "ViewMatrix");
  GLuint PmatrixID = glGetUniformLocation(programID, "ProjectionMatrix");

  cout << " -- Debut de la boucle principale..." << endl;
  unsigned int i = 0;

  // Boucle de dessin
  do
  {

    // Nettoyage de la zone de dessin
    glClear(GL_COLOR_BUFFER_BIT);

    //==================================================
    // Modification des matrices de transformation
    //==================================================

    // >***** Changements de point de vue ******<
  
    // Tourne view_matrix d'un angle autour de l'axe z
    //view_matrix = rotate(view_matrix, 50.0f ,vec3(0.0f,0.0f,1.0f));

    // Change l'échelle de view_matrix dans toutes les dimensions
    //view_matrix = scale(view_matrix, vec3(0.5f,0.5f,0.5f));

    // Déplace view_matrix vers la gauche (x négatif), le haut (y positif), et vers nous (z positif).
    //view_matrix = translate(view_matrix, vec3(-0.002f,0.001f,0.004f));

    // Activer la navigation dans la scene par touches du clavier.
    view_control(myWindow, view_matrix, 0.05f);

    // >****************************************<


    //==================================================
    //===================== Dessin =====================
    //==================================================
    glUseProgram(programID); // Definition de programID comme le shader courant

    //==================================================
    // Transmission des matrices au vertex shader
    //==================================================
    glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));
    glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
    glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));

    glBindVertexArray(vaoID); // On active le VAO

    // on dessine le contenu de tous les VBOs (buffers) associés à ce VAO
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0); // On désactive le VAO

    // Echange des zones de dessin buffers
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

  cout << " -- Fin du programme." << endl;

  return EXIT_SUCCESS;
}
