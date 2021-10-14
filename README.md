# Laboratoire 2 - Architecture des logiciels

Le laboratoire a pour but de réutiliser le [laboratoire 1](https://github.com/jovil210/lab1_logiciel) de ce même cours afin de se créer un module python qui utilisera le lecteur vidéo qui a été créer en C++ et qui permet les actions suivantes:
* P: Play/Pause
* A: Accélérer
* R: Retour au début
* Q: Quitter

## Installation

* Installer [Visual Studio](https://visualstudio.microsoft.com/fr/downloads/)
* Installer [Python 3.7+](https://www.python.org/downloads/)
* Dans le répertoire Playback, ouvrir Playback.sln avec Visual Studio
* À partir de Visual Studio, faire les modifications suivantes:
* Mettre en mode Release et sur plateforme 64 bits (x64)
* Aller dans *Projet -> Propriétés -> Propriétés de configuration -> Type de configuration* et changer pour __Bibliothèque dynamique (dll)__
* Puis, toujours dans les propriétés, aller dans *Paramètres avancés* et modifier *Extension du fichier cible* pour __.pyd__
* Finalement, toujours dans les propriétés, aller dans *Répertoires VC++* et modifier *Répertoires Include* et *Répertoires de bibliothèques* afin d'ajouter les répertoires propres à Python. Ceux-ci se trouvent habituellement dans le répertoire suivant avec les noms **libs** et **include**:

__```C:\Users\<nom de l'utilisateur>\AppData\Local\Programs\Python\PythonXX\```__

Le programme devrait fonctionner et créer un fichier compilé __Playback.pyd__.



## Usage
Pour que le programme fonctionne, il faut importer le module __Playback.pyd__:
```python
from path.to.Release import Playback
```
Puis, il faut appeler la méthode **play_video** avec comme argument l'emplacement du fichier à jouer.

```python
Playback.play_video("path\\to\\video.avi");
```
Il est important d'écrire le nom du fichier avec le bon emplacement de dossier. L'exemple VideoExample.py devrait fonctionner car il est dans le repo.
***
Finalement, la bibliothèque dynamique créée en language C++ s'occupera de faire jouer la vidéo et l'utilisateur pourra effectuer les 4 fonctions nommés plus haut:
* P: Play/Pause
* A: Accélérer
* R: Retour au début
* Q: Quitter

Il est important d'appuyer sur la console lorsqu'on veut effectuer les actions car c'est là que les lettre sont enregistrés.


## License
[MIT](https://choosealicense.com/licenses/mit/)