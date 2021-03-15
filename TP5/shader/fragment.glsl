// Version d'OpenGL
#version 330

in vec2 coords; 

out vec4 frag_color;

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
 *            =    Re(z^N)     +      Im(z^N)
 */
vec2 raiseComplexNumberToPowerN(vec2 c, int N) {
  float r = sqrt(c.x * c.x + c.y * c.y);
  float t = atan(c.x / c.y);
  float real = pow(r, N) * cos(N*t);
  float imaginary = pow(r, N) * sin(N*t);
  // return vec2(real, imaginary);
  return vec2(c);
}

/**
 * Retourne le module du nombre complexe c.
 */
float modulusOfComplexNumber(vec2 c) {
  return sqrt(c.x * c.x + c.y * c.y);
}

/**
 * Calcule une couleur selon l'ensemble de Mandelbrot
 * à partir des entiers S (valeur seuil) et N,
 * ainsi que de c, la position du point à colorier .
 */
vec4 colormap(float K) {
  return vec4(1.0-K, 1.0-K, 1.0-K, 1.0);
}

// Fonction appellee pour chaque fragment
void main() {

  int N = 100;
  int S = 2;

  vec2 z = vec2(0,0);
  int i;
  for(i = 0 ; i < N ; i++){
    z = raiseComplexNumberToPower2(z) + coords.xy;
    if(modulusOfComplexNumber(z) > S) break;
  }

  float res = 1.0 * i / N;

  // Affichage de la coordonnee du fragment/pixel
  // frag_color = vec4(coords, 0.5, 1.0);
  frag_color = colormap(res);
}
