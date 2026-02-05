# 🕵️ Incognito - Jeu de Stratégie en C

**Incognito** est un jeu de plateau tactique développé en **langage C**. Ce projet simule un duel stratégique alliant logique de déplacement et mécanique de déduction pour démasquer l'adversaire.

## 🎮 Concept du Jeu
Le jeu oppose deux joueurs sur un plateau de 5x5 cases. L'objectif est double :
* **Infiltration** : Faire entrer son pion "Espion" dans le château adverse.
* **Interrogation** : Identifier et révéler l'espion de l'adversaire en interrogeant les pions adjacents.

## 🛠️ Points Techniques
Ce projet démontre la maîtrise de concepts fondamentaux de la programmation système :
* **Modélisation de données** : Utilisation de structures (`struct`) et d'énumérations (`enum`) pour gérer les types de pions (Chevalier/Espion) et l'état du jeu.
* **Algorithmique de déplacement** : Implémentation de règles de mouvement orthogonales et diagonales avec détection d'obstacles et gestion des zones restrictives (châteaux).
* **Persistance des données** : Système de sauvegarde et de chargement via des fichiers `.inco`, permettant d'enregistrer l'historique des coups et de reprendre une partie.
* **Gestion d'interface CLI** : Affichage dynamique du plateau en mode ASCII dans le terminal.

## 💻 Installation et Compilation
Le programme se compile avec `clang` ou `gcc` :
```bash
clang -std=c17 -Wall -Wfatal-errors main.c -o incognito
