# AirWatcher
Projet INSA 3IF 2021 GL - AirWatcher  
_Créé par Rahim BELATECHE, Ewen CHAILLAN, Benoit DELEGLISE, Mathieu SAUGIER_

## Objectif du projet
Créer une application permettant de suivre la qualité de l’air grâce aux données récoltées par différents capteurs installés sur un large territoire, en s'adaptant à différents jeux de données qui suivent un format prédéfini.

## Environnement de développement
Le projet a été développé en utilisant **Visual Studio 2019** Community Edition v142.
La norme du langage C++ utilisée est **C++ 17**.


### Réglages du projet
Nous avons utilisé une macro préprocesseur afin d'avoir l'emplacement du la solution sur le disque. Dans le cas où l'application ne fonctionne pas, aller dans les propriétés du projet, puis  
C/C++ --> préprocesseur --> Définitions de préprocesseur et ajouter l'entrée suivante  
`SOLUTION_DIR=R"($(SolutionDir))"`

### Modification du Dataset
Le dataset contient les données qui nous ont été fournies pour le projet et se situe dans un dossier éponyme à la racine de l'application.  
Si le dossier est déplacé, que vous voulez importer d'autres données ou que vous souhaitez lancer l'application avec un autre environnement que Visual Studio, vous pourriez rencontrer des erreurs.
Vous pouvez modifier le code source du fichier `ReaderConfig.h` de telle sorte que l'attribut `string DIRECTORYPATH` ait pour valeur le chemin absolu vers le dossier Dataset. Cela permet que à la fois l'application et les tests puissent bien se dérouler.

## Exécution de l'application et réalisation de tests
Nous conseillons de lancer l'application directement avec le compliateur intégré à Visual Studio.  
Pour effectuer les tests, il suffit d'ouvrir l'explorateur de tests (`Ctrl+E,T`), puis d'exécuter tous les tests (`Ctrl+R,V`)

