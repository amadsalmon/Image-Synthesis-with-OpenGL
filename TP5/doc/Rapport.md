# TP4 - Fragment shader et fractales

**Amad Salmon | Synthèse d’Image - Polytech Grenoble, INFO4, 2020-2021**

## Introduction  
Sans avoir modifié le code initial, on obtient le rendu suivant :
<img src="./Rapport.assets/rendu-initial_1.png" alt="Rendu initial original avec composante bleue à 50%" style="text-align:center;zoom:20%;" />

Explication : Le vertex shader exporte pour chaque sommet une variable `coords=(x,y)`, qui correspond aux coordonnées $(x,y)$ de ce sommet dans la fenêtre d'affichage mais dans l'intervalle $[0,1]$. Ensuite, le fragment shader récupère en entrée cette variable `coords=(x,y)`, et s'en sert pour générer les couleurs de chaque sommet. Ainsi, pour le sommet ayant pour coordonnées $(x,y)$ _(dans l'intervalle $[0,1]$)_ aura comme couleur RGB $(x,y,b)$, où $b$ est une constante arbitrairement fixée (ici $b=0.5$).  
Si l'on abaisse $b$ à $0$, autrement dit si on annule la composante bleue, le rendu devient le suivant :
<img src="./Rapport.assets/rendu-initial_3.png" alt="Rendu initial original avec composante bleue à 0%" style="text-align:center;zoom:20%;" />





<div style="page-break-after: always; break-after: page;"></div>