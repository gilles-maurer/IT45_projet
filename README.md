# IT45_projet


## Description du projet

Ce projet est un projet pour le cours d'IT45. Il a pour but d'optimiser la répartition de missions à différents employés. 

L'algorithme est décomposé en deux parties :

    - La première partie consiste à répartir les missions à des centres en fonction de la proximité de ces derniers avec les missions.

    - La deuxième partie consiste à répartir les missions à des employés. Cette partie est effectuée par un algorithme génétique. Les solutions initiales sont issues des résultats de la première partie.

Ce projet est réalisé en c++.

Ce projet a été réalisé par Augustin ATHANE et Gilles MAURER

## Lancement 

Pour lancer le projet, il faut faire la commande make. 

Ensuite il a plusieurs possibilité pour lancer le projet : 

    - ./algo_sessad : lance l'algorithme avec les paramètres par défaut.

    - ./algo_sessad %d :
        -> %d est un entier compris entre 1 et 6 qui correspond à l'instance à utiliser.

    - ./algo_sessad %d %d %d :
        -> %d est un entier compris entre 1 et 6 qui correspond à l'instance à utiliser. 
        -> %d est un entier qui correspond au nombre de génération. 
        -> %d est un entier qui correspond à la taille de la population initiale. 

    - ./algo_sessad %d %d %d %f %f : 
        -> %d est un entier compris entre 1 et 6 qui correspond à l'instance à utiliser. 
        -> %d est un entier qui correspond au nombre de génération. 
        -> %d est un entier qui correspond à la taille de la population initiale. 
        -> %f est un double qui correspond à la probabilité de croisement. 
        -> %f est un double qui correspond à la probabilité de mutation.

    - ./algo_sessad %d %d %d %f %f %f %f %f 
        -> %d est un entier compris entre 1 et 6 qui correspond à l'instance à utiliser.
        -> %d est un entier qui correspond au nombre de génération.
        -> %d est un entier qui correspond à la taille de la population initiale.
        -> %f est un double qui correspond à la probabilité de croisement.
        -> %f est un double qui correspond à la probabilité de mutation.
        -> %f est un double qui correspond au coefficient du nombre de missions affecté pour la fitness.
        -> %f est un double qui correspond au coefficient de la distance parcourue pour la fitness.
        -> %f est un double qui correspond au coefficient du nombre de spécialité respectée pour la fitness.



