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
Le dossier Dataset contient les données fictives qui nous ont été fournies pour le  développement et les tests du projet et se situe dans un dossier éponyme à la racine de l'application.  
Si le dossier est déplacé, que vous voulez importer d'autres données ou que vous souhaitez lancer l'application avec un autre environnement que Visual Studio, vous pourriez rencontrer des erreurs lors de l'exécution des tests. Nous vous conseillons de ne pas modifier ce dossier ni le supprimer, mais d'en créer un nouveau avec les nouvelles données.
Vous pouvez modifier le code source du fichier `ReaderConfig.h` de telle sorte que l'attribut `string DIRECTORYPATH` ait pour valeur le chemin absolu vers votre dossier Dataset. Il ne faudra néanmoins pas oublier de remettre le chemin d'accès par défaut pour utiliser le dataset fictif dans le cas où vous voudriez lancer les tests. 

## Exécution de l'application et réalisation de tests
Nous conseillons de lancer l'application directement avec le compilateur intégré à Visual Studio. Lors de la première exécution, l'application devrait se build.   
Pour effectuer les tests, il suffit d'ouvrir l'explorateur de tests (`Ctrl+E,T`), puis d'exécuter tous les tests (`Ctrl+R,V`).
Si vous rencontrez des erreurs vous empêchant d'exécuter les tests, vérifiez votre version de Google Test. Pour le projet, nous avons utilisé :
"Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn" version="1.8.1.4"
