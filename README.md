# ft_vector

**ft_vector** est une bibliothèque en C permettant de manipuler des tableaux dynamiques génériques.

Elle permet de stocker des éléments de différents types, d'ajouter ou de supprimer des éléments, d'insérer des valeurs à un indice donné et de gérer automatiquement la capacité du tableau.

L'objectif est de proposer une interface simple, proche de celle des `std::vector` en C++, tout en conservant les possibilités offertes par le langage C.

## Fonctionnalités

- Gestion de tableaux dynamiques génériques.
- Allocation et réservation de mémoire.
- Initialisation à partir d'un tableau existant.
- Ajout et suppression d'éléments.
- Insertion à un indice donné.
- Réduction de la capacité inutilisée.
- Accès aux informations de taille et de capacité.
- Libération de la mémoire.

## Principe de fonctionnement

### 1. Organisation en mémoire

Un vecteur est constitué de deux parties :

- Une structure `t_vector` contenant les métadonnées.
- Une zone mémoire contenant les éléments du tableau.

La structure `t_vector` est définie ainsi :

```c
typedef struct {
    size_t size;
    size_t capacity;
    size_t elsize;
} t_vector;
```

| Champ      | Description                                               |
| ---------- | --------------------------------------------------------- |
| `size`     | Nombre d'éléments actuellement stockés.                   |
| `capacity` | Nombre d'éléments pouvant être stockés sans réallocation. |
| `elsize`   | Taille, en octets, d'un élément.                          |

Le pointeur retourné par les fonctions d'initialisation désigne directement le premier élément du tableau, et non la structure `t_vector`.

Cela permet d'utiliser le vecteur comme un tableau classique en C.

### 2. Gestion de la capacité

La taille et la capacité sont deux notions différentes.

Lorsqu'un ajout nécessite davantage de capacité, la bibliothèque peut réallouer le bloc mémoire afin de permettre l'ajout de nouveaux éléments.

Cette organisation évite de devoir effectuer une allocation mémoire pour chaque élément ajouté.

### 3. Gestion des types

La bibliothèque utilise des macros pour fournir une interface générique.

Le type des éléments est déterminé lors de l'initialisation :

```c
vector(int);
vector(double);
vector(char);
```

Chaque vecteur conserve la taille de son type d'élément dans le champ `elsize`.

Les opérations internes utilisent cette information pour effectuer les copies mémoire et déplacer les éléments.

## Installation

Clone le dépôt :

```bash
git clone 
```

Inclure le fichier d'en-tête dans ton programme :

```c
#include "vector.h"
```

Compiler ton programme avec les fichiers sources de la bibliothèque.

Exemple :

```bash
gcc main.c vector.c -o main
```

Adapte le nom du fichier source à l'organisation réelle du projet.

## API

### Initialisation

#### `vector(T)`

Crée un vecteur vide dont les éléments sont de type `T`.

```c
int *numbers = vector(int);
```

Le vecteur est initialisé avec une taille nulle et une capacité par défaut de 10.

#### `vector_reserve(T, capacity)`

Crée un vecteur avec une capacité initiale spécifiée.

```c
int *numbers = vector_reserve(int, 25);
```

La capacité initiale est de 25 éléments.

#### `vector_init_from(T, src, size)`

Initialise un vecteur à partir d'une zone mémoire existante.

```c
int values[] = {10, 20, 30};

int *numbers = vector_init_from(int, values, 3);
```

Le vecteur est initialisé avec les éléments de `values`.

### Ajout d'éléments

#### `vector_push(vec, value)`

Ajoute un élément à la fin du vecteur.

```c
int *numbers = vector(int);

int a = 10,
vector_push(numbers, &a);
a = 20;
vector_push(numbers, &a);
a = 30
vector_push(numbers, &a);
```

L'ajout copie la valeur et non l'adresse, donc ce sera la valeur qui copiée et persistera même si la variable change de valeur ou est détruite.

#### `vector_push_back(vec, value)`

Effectue la même opération que `vector_push`.

```c
a = 40;
vector_push_back(numbers, &a);
```

Les deux macros utilisent la même fonction interne.

### Insertion

#### `vector_insert(vec, value, index)`

Insère un élément à un indice donné.

```c
a = 15;
vector_insert(numbers, &a, 1);
```

L'élément est inséré à l'indice 1, et les éléments suivants sont décalés.

La fonction retourne un booléen indiquant le résultat de l'opération.

### Suppression

#### `vector_pop(vec, out)`

Supprime le dernier élément du vecteur et copie sa valeur dans la variable désignée par `out`.

```c
int value;

if (vector_pop(numbers, &value)) {
    /* value contient l'élément supprimé */
}
vector_pop(numbers, NULL); // possibilité de retirer un élément sans stocker sa valeur
```

La fonction retourne `true` si l'opération réussit, et `false` si elle échoue.

Le paramètre `out` doit désigner une zone mémoire suffisamment grande pour recevoir un élément du vecteur si il est renseigné.

#### `vector_pop_back(vec, out)`

Cette macro est un alias de `vector_pop`.

```c
vector_pop_back(numbers, &value);
```

### Informations sur le vecteur

#### `vector_size(vec)`

Retourne le nombre d'éléments présents.

```c
size_t size = vector_size(numbers);
```

#### `vector_capacity(vec)`

Retourne la capacité actuelle du vecteur.

```c
size_t capacity = vector_capacity(numbers);
```

#### `vector_empty(vec)`

Vérifie si le vecteur est vide.

```c
if (vector_empty(numbers)) {
    /* Le vecteur ne contient aucun élément */
}
```

### Gestion de la mémoire

#### `vector_clear(vec)`

Vide le vecteur en sans réinitialiser la capacité.

```c
vector_clear(numbers);
```

#### `vector_shrink_to_fit(vec)`

Réduit la capacité du vecteur afin qu'elle corresponde à sa taille actuelle.

```c
vector_shrink_to_fit(numbers);
```

#### `vector_free(vec)`

Libère la mémoire utilisée par le vecteur et met son pointeur à `NULL`.

```c
vector_free(numbers);
```

Après cette opération, le vecteur ne doit plus être utilisé.

## Exemple d'utilisation

```c
#include <stdio.h>
#include "ft_vector.h"

int main(void)
{
    int *numbers = vector(int);

    if (numbers == NULL)
        return 1;

    int a = 10;
    vector_push(numbers, &a);
    a = 20;
    vector_push(numbers, &a);
    a = 30;
    vector_push(numbers, &a);

    printf("Taille : %zu\n", vector_size(numbers));
    printf("Capacité : %zu\n", vector_capacity(numbers));

    int value;

    if (vector_pop(numbers, &value))
        printf("Élément supprimé : %d\n", value);
    vector_pop(numbers, NULL);

    vector_free(numbers);

    return 0;
}
```
