# 🕵️ Incognito - Jeu de Stratégie en C

**Incognito** est un jeu de plateau tactique développé en **langage C**. [cite_start]Ce projet simule un duel stratégique alliant logique de déplacement et mécanique de déduction pour démasquer l'adversaire[cite: 2070, 2072].

## 🎮 Concept du Jeu
[cite_start]Le jeu oppose deux joueurs sur un plateau de 5x5 cases[cite: 2071]. L'objectif est double :
* [cite_start]**Infiltration** : Faire entrer son pion "Espion" dans le château adverse[cite: 2084, 2088].
* [cite_start]**Interrogation** : Identifier et révéler l'espion de l'adversaire en interrogeant les pions adjacents[cite: 2086, 2103].

## 🛠️ Points Techniques
Ce projet démontre la maîtrise de concepts fondamentaux de la programmation système :
* [cite_start]**Modélisation de données** : Utilisation de structures (`struct`) et d'énumérations (`enum`) pour gérer les types de pions (Chevalier/Espion) et l'état du jeu[cite: 2092, 2094, 2096].
* [cite_start]**Algorithmique de déplacement** : Implémentation de règles de mouvement orthogonales et diagonales avec détection d'obstacles et gestion des zones restrictives (châteaux)[cite: 2085, 2100, 2121].
* [cite_start]**Persistance des données** : Système de sauvegarde et de chargement via des fichiers `.inco`, permettant d'enregistrer l'historique des coups et de reprendre une partie[cite: 2081, 2104, 2110, 2113].
* [cite_start]**Gestion d'interface CLI** : Affichage dynamique du plateau en mode ASCII dans le terminal[cite: 2080, 2099].

## 💻 Installation et Compilation
Le programme se compile avec `clang` ou `gcc` :
```bash
clang -std=c17 -Wall -Wfatal-errors main.c -o incognito
