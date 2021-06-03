# AirWatcher
Projet INSA 3IF 2021 GL - AirWatcher
Par Rahim BELATECHE, Ewen CHAILLAN, Benoit DELEGLISE, Mathieu SAUGIER

## Objectif du projet
Créer une application permettant de suivre la qualité de l’air grâce aux données récoltées par différents capteurs installés sur un large territoire, en s'adaptant à différents jeux de données qui suivent un format prédéfini.

## Environnement de développement
Le projet a été développé en utilisant **Visual Studio 2019** Community Edition v142.
La norme du langage C++ utilisée est **C++ 17**.
Nous conseillons de lancer l'application directement avec le compliateur intégré à Visual Studio.

### Réglages du projet
Nous avons utilisé une macro préprocesseur afin d'avoir l'emplacement du la solution sur le disque. Dans le cas où l'application ne fonctionne pas, aller dans les propriétés du projet
- C/C++ --> préprocesseur --> Définitions de préprocesseur et ajouter l'entrée suivante `SOLUTION_DIR=R"($(SolutionDir))"`



