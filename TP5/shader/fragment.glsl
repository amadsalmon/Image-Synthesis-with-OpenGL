// Version d'OpenGL
#version 330

/* -- Données en entrée -- */
in vec2 coords; 

/* -- Données en sortie -- */
out vec4 frag_color;

/* -- Paramètres -- */
uniform float currentTime;

/**
 * Retourne le module du nombre complexe c = x + iy.
 */
float modulusOfComplexNumber(vec2 c) {
  return sqrt(c.x * c.x + c.y * c.y);
}

/**
 * Retourne un vecteur composé de la partie réelle et de la partie imaginaire 
 * du carré du nombre complexe c.
 * (a + bi)^2 = a^2 - b^2 + 2iab
 */
vec2 raiseComplexNumberToPower2(vec2 c) {
  float real = c.x * c.x - c.y * c.y;
  float imaginary = 2.0 * c.x * c.y;
  return vec2(real, imaginary);
}

/**
 * Retourne un vecteur composé de la partie réelle et de la partie imaginaire 
 * du nombre complexe c élevé à la puissance N.
 *
 * Soit z = a + ib avec a et b réels.
 * On peut noter  z = a + ib = r*(cos(t) + i * sin(t)),
 * où r^2 = a^2 + b^2,
 * et tan(t) = b / a.
 * Alors, z^N = (a+i*b)^N
 *            = r^N * (cos(Nt) + i * sin(Nt))
 *            = r^N * cos(Nt)  +  i * r^N * sin(Nt)
 *            =    Re(z^N)     +  i * Im(z^N)
 */
vec2 raiseComplexNumberToPowerN(vec2 c, int N) {
  if (N < 0 ) {
      return vec2(0, 0);
  } else if (N == 1) {
      return c;
  }
  float r = modulusOfComplexNumber(c);
  float t = atan(c.x , c.y);
  float real = pow(r, N) * cos(N*t);
  float imaginary = pow(r, N) * sin(N*t);
  return vec2(real, imaginary);
}

/**
 * Calcule une couleur selon l'ensemble de Mandelbrot
 * à partir des entiers S (valeur seuil) et N,
 * ainsi que de c, la position du point à colorier .
 */
 vec4 colormap(float k, int modeDeColoration){
  switch (modeDeColoration) {
    case 1:   // coloration en nuances de gris
      return vec4(1-k, 1-k, 1-k, 1.0);
    case 2:   // coloration complexe
      return vec4(cos(k * 10.0), cos(k * 20.0), cos(k * 30.0), 1.0);
    case 3:   // coloration animée en fonction du temps 
      return vec4(cos(currentTime*k)/currentTime, 1-(k*cos(currentTime)), sin(currentTime*k), 1.0);
    default:
      return vec4(k, k, 1-k, 1.0);
  }
}

float mandelbrotSet(int N, int S) {
  vec2 z = vec2(0.0, 0.0);
  int i;
  for(i = 0 ; i < N ; i++){
    z = raiseComplexNumberToPower2(z) + coords.xy;
    if(modulusOfComplexNumber(z) > S) break;
  }

  return 1.0 * i / N;
}

float mandelbrotSetAnimated(int N, int S) {
  vec2 z = vec2(currentTime/50,currentTime/50);
  int i;
  for(i = 0 ; i < N ; i++){
    z = raiseComplexNumberToPower2(z) + coords.xy;
    if(modulusOfComplexNumber(z) > S) break;
  }
  return 1.0 * i / N;
}

float juliaSet(int N, int S) {
  vec2 z = coords;
  int i;
  for(i = 0 ; i < N ; i++){
    z = raiseComplexNumberToPower2(z) + vec2(0.5, 0.5);
    if(modulusOfComplexNumber(z) > S) break;
  }

  return 1.0 * i / N;
}

// Fonction appellee pour chaque fragment
void main() {

  int N = 100;  // Nombre maximum d'itérations
  int S = 2;    // Valeur seuil

  // float res = mandelbrotSet(N, S);
  // float res = juliaSet(N, S);
  float res = mandelbrotSetAnimated(N, S);

  // Affichage de la coordonnee du fragment/pixel
  frag_color = colormap(res, 2);
}
