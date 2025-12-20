# 🎮 Minesweeper with SFML

Un jeu de démineur (Minesweeper) moderne implémenté en C++ avec la bibliothèque SFML, utilisant une architecture propre et modulaire.

![Minesweeper](https://img.shields.io/badge/Game-Minesweeper-blue)
![C++](https://img.shields.io/badge/C++-17-orange)
![SFML](https://img.shields.io/badge/SFML-2.5-green)
![CMake](https://img.shields.io/badge/CMake-3.16+-brightgreen)
![License](https://img.shields.io/badge/License-MIT-yellow)

## ✨ Fonctionnalités

- 🎯 **Jeu de démineur classique** avec toutes les règles originales
- 🎨 **Interface graphique moderne** générée dynamiquement (pas d'images externes nécessaires)
- 🏗️ **Architecture modulaire** séparant la logique, le rendu et les entrées
- ⚙️ **Configuration flexible** (taille de grille, nombre de mines)
- 🎮 **Contrôles intuitifs** (clic gauche/droit, raccourcis clavier)
- 📊 **Interface utilisateur riche** avec compteurs et indications
- 💾 **Système d'états de jeu** extensible

## 📋 Prérequis

### Dépendences système (Linux/Ubuntu)
```bash
# Installer les dépendances SFML
sudo apt-get update
sudo apt-get install libsfml-dev libsfml-graphics2.5 libsfml-window2.5 libsfml-system2.5

# Installer les outils de développement
sudo apt-get install build-essential cmake
```

### Dépendences système (Windows)
1. Télécharger SFML depuis [sfml-dev.org](https://www.sfml-dev.org/download.php)
2. Installer CMake depuis [cmake.org](https://cmake.org/download/)
3. Installer MinGW ou Visual Studio

### Dépendences système (macOS)
```bash
# Avec Homebrew
brew install sfml cmake
```

## 🚀 Installation et compilation

### Méthode 1 : Avec CMake (recommandée)
```bash
# Cloner le projet
git clone https://github.com/votre-username/minesweeper-sfml.git
cd minesweeper-sfml

# Créer le dossier de build
mkdir build
cd build

# Configurer avec CMake
cmake ..

# Compiler
make

# Lancer le jeu
./Minesweeper
```

### Méthode 2 : Compilation manuelle
```bash
g++ -std=c++17 -I./include source/*.cpp source/**/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o Minesweeper
```

## 🎮 Comment jouer

### Contrôles
- **Clic gauche** : Révéler une case
- **Clic droit** : Placer/enlever un drapeau
- **Clic sur le bouton visage** : Recommencer une partie
- **Touche R** : Recommencer une partie
- **Touche Échap** : Quitter le jeu (à implémenter)

### Règles du jeu
1. Le but est de révéler toutes les cases sans mines
2. Les nombres indiquent combien de mines sont adjacentes
3. Les drapeaux marquent les cases suspectées de contenir une mine
4. Le premier clic est toujours sûr (pas de mine)
5. Les cases vides se révèlent automatiquement avec leurs voisines

## 🏗️ Architecture du projet

```
Minesweeper/
├── CMakeLists.txt          # Configuration CMake
├── .gitignore             # Fichiers à ignorer par git
├── assets/                # Ressources
│   └── fonts/            # Polices de caractères
├── include/               # Fichiers d'en-tête
│   ├── Game/             # Configuration et boucle principale
│   ├── Logic/            # Logique du jeu (grille, cases)
│   ├── Renderer/         # Rendu graphique
│   ├── Input/            # Gestion des entrées
│   ├── UI/               # Interface utilisateur
│   └── States/           # Gestion des états du jeu
├── source/               # Fichiers source
│   ├── main.cpp          # Point d'entrée
│   └── (structure similaire à include)
└── README.md             # Ce fichier
```

### Modules principaux

1. **Game** : Boucle principale et gestion de la fenêtre
2. **Logic** : 
   - `Board` : Gestion de la grille de jeu
   - `Cell` : Représentation d'une case
   - `GameLogic` : Règles et état du jeu
3. **Renderer** :
   - `AssetManager` : Génération dynamique des textures
   - `Renderer` : Rendu de la scène
4. **Input** : Gestion des événements souris/clavier
5. **UI** : Éléments d'interface utilisateur
6. **States** : Machine à états pour le jeu

## ⚙️ Configuration

Modifiez `include/Game/Config.hpp` pour personnaliser :
```cpp
// Dimensions de la grille
static constexpr int BOARD_WIDTH = 16;
static constexpr int BOARD_HEIGHT = 16;

// Nombre de mines
static constexpr int MINES_COUNT = 40;

// Taille des cases
static constexpr int TILE_SIZE = 32;

// Hauteur de l'interface
static constexpr int UI_HEIGHT = 140;
```

## 📁 Structure des fichiers

### Fichiers principaux
- `source/main.cpp` : Point d'entrée du programme
- `source/Game/Game.cpp` : Classe principale du jeu
- `source/Logic/Board.cpp` : Implémentation de la grille
- `source/Renderer/Renderer.cpp` : Rendu graphique

### Assets requis
- `assets/fonts/` : Contient les polices de caractères
  - `arial.ttf` ou toute police TrueType (.ttf)

## 🛠️ Développement

### Ajouter une nouvelle fonctionnalité
1. Ajouter les fichiers d'en-tête dans `include/`
2. Implémenter dans `source/`
3. Mettre à jour `CMakeLists.txt` si nécessaire
4. Recompiler avec `make`

### Débogage
```bash
# Compiler avec symboles de debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Utiliser gdb
gdb ./Minesweeper
```

### Tests
Pour ajouter des tests unitaires :
```cpp
// Exemple de test pour la classe Cell
void testCell() {
    Cell cell;
    assert(!cell.hasMine());
    assert(!cell.isRevealed());
    
    cell.setMine(true);
    assert(cell.hasMine());
}
```

## 🔧 Problèmes courants et solutions

### Erreur : "SFML not found"
```bash
# Vérifier l'installation de SFML
sudo apt-get install libsfml-dev
# Ou spécifier le chemin SFML à CMake
cmake -DSFML_DIR=/chemin/vers/sfml ..
```

### Erreur : "Font not found"
```bash
# Copier une police dans assets/fonts/
cp /usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf assets/fonts/arial.ttf
```

### Performance lente
- Vérifier que le jeu tourne en release : `cmake -DCMAKE_BUILD_TYPE=Release ..`
- Réduire la taille de la grille dans `Config.hpp`

## 📚 Documentation

### Ressources SFML
- [Documentation officielle SFML](https://www.sfml-dev.org/documentation/2.5.1/)
- [Tutoriels SFML](https://www.sfml-dev.org/tutorials/2.5/)

### Ressources C++
- [C++ Reference](https://en.cppreference.com/)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)

### Architecture
- [Game Programming Patterns](http://gameprogrammingpatterns.com/)
- [SFML Game Development](https://github.com/SFML/SFML-Game-Development-Book)

## 🤝 Contribution

Les contributions sont les bienvenues ! Voici comment contribuer :

1. Fork le projet
2. Créer une branche (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

### Améliorations possibles
- [ ] Ajouter différents niveaux de difficulté
- [ ] Implémenter un système de scores/highscores
- [ ] Ajouter des effets sonores
- [ ] Créer un menu principal
- [ ] Ajouter un chronomètre
- [ ] Implémenter la sauvegarde/chargement
- [ ] Ajouter des animations
- [ ] Support multijoueur/local

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 🙏 Remerciements

- [SFML](https://www.sfml-dev.org/) pour l'excellente bibliothèque multimédia
- [CMake](https://cmake.org/) pour le système de build
- La communauté C++ pour les ressources et le support

## 📞 Contact

Votre Nom - [@votretwitter](https://twitter.com/votretwitter) - email@example.com

Lien du projet : [https://github.com/ToavinaJr/Minesweeper-SFML](https://github.com/ToavinaJr/Minesweeper-SFML)

---

**Enjoy playing Minesweeper!** 💣🚩🎯

*Si vous appréciez ce projet, n'hésitez pas à lui donner une ⭐ sur GitHub !*