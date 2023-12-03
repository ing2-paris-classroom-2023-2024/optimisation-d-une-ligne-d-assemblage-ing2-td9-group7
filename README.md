# Optimisation d'une ligne d'assemblage

Repository du Projet de théorie des graphes ING2

Ce projet répond à un problème d'optimisation dans le contexte de la planification d'une ligne d'assemblage pour la fabrication d'un produit. Les contraintes à prendre en compte sont les contraintes d'exclusion, de précédence et de temps de cycle.

1. Contraintes d'exclusion :
   - Certaines opérations ne peuvent pas être effectuées par la même station.
   - Représenté par un ensemble de paires d'opérations interdites à affecter à la même station.

2. Contraintes de précédence :
   - Certains opérations doivent être effectuées avant d'autres.
   - Représenté par un ensemble de paires d'opérations modélisant un arc du graphe de précédence.

3. Contrainte de temps de cycle :
   - Le temps total des opérations affectées à une station ne doit pas dépasser le temps de cycle.
   - Exemple : Si le temps de cycle vaut 10s, alors la somme des temps des opérations affectées à une station ne doit pas dépasser 10s.

4. Optimisation :
   - L'objectif principal est de minimiser le nombre de stations.
   - Chaque station a un coût non négligeable, donc minimiser le nombre de stations contribue à réduire le coût de production.

Données d'entrée :
   - Les différentes contraintes sont stockées dans plusieurs fichiers texte.

Interface utilisateur :
   - Le programme s'exécute entièrement en console.
   - L'affichage en console est clair et compréhensible.

**Sources :**
   - Le recours à des algorithmes de la littérature scientifique est autorisé, et les sources doivent être citées le cas échéant.

L'objectif global est d'obtenir une répartition optimisée des opérations entre les différentes stations de la ligne d'assemblage, en respectant les contraintes spécifiées, et en minimisant le nombre de stations pour réduire les coûts de production.
