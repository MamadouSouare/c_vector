# CHEATSHEET - c_vector

Cette page répertorie les opérations disponibles dans la bibliothèque c`_vector`.

Les macros constituent l'interface principale de la bibliothèque. Elles simplifient l'utilisation des fonctions internes et permettent de manipuler des vecteurs génériques.

## Tableau de l'API

| Macro / Fonction                   | Paramètres                  | Description                                                                             | Retour        |
| ---------------------------------- | --------------------------- | --------------------------------------------------------------------------------------- | ------------- |
| `vector(T)`                        | Type `T`                    | Crée un vecteur vide.                                                                   | Pointeur typé |
| `vector_reserve(T, capacity)`      | Type, capacité              | Crée un vecteur avec une capacité initiale spécifiée.                                   | Pointeur typé |
| `vector_init_from(T, src, size)`   | Type, source, taille        | Initialise un vecteur à partir d'une zone mémoire existante.                            | Pointeur typé |
| `vector_push(vec, value)`          | Vecteur, valeur             | Ajoute un élément à la fin du vecteur.                                                  | `bool`        |
| `vector_push_back(vec, value)`     | Vecteur, valeur             | Alias de `vector_push`.                                                                 | `bool`        |
| `vector_insert(vec, value, index)` | Vecteur, valeur, indice     | Insère un élément à l'indice spécifié.                                                  | `bool`        |
| `vector_pop(vec, out)`             | Vecteur, pointeur de sortie | Supprime le dernier élément et copie sa valeur dans `out` si celui-ci n'est pas `NULL`. | `bool`        |
| `vector_pop_back(vec, out)`        | Vecteur, pointeur de sortie | Alias de `vector_pop`.                                                                  | `bool`        |
| `vector_empty(vec)`                | Vecteur                     | Vérifie si le vecteur est vide.                                                         | `bool`        |
| `vector_size(vec)`                 | Vecteur                     | Retourne le nombre d'éléments présents.                                                 | `size_t`      |
| `vector_capacity(vec)`             | Vecteur                     | Retourne la capacité actuelle.                                                          | `size_t`      |
| `vector_clear(vec)`                | Vecteur                     | Supprime tous les éléments sans libérer la capacité.                                    | Aucune        |
| `vector_shrink_to_fit(vec)`        | Vecteur                     | Réduit la capacité à la taille actuelle.                                                | `bool`        |
| `vector_free(vec)`                 | Vecteur                     | Libère la mémoire et met le pointeur à `NULL`.                                          | Aucune        |

## Remarques

- Les macros `vector_push` et `vector_push_back` attendent une valeur compatible avec le paramètre `const void *` de la fonction interne. Pour ajouter une variable, il faut donc lui transmettre son adresse.
- Les opérations d'ajout et d'insertion effectuent une copie de la valeur en mémoire.
- `vector_pop` est une fonction accessible directement, contrairement aux autres opérations qui sont principalement exposées sous forme de macros.
- Pour la fonction vector_pop, le second argument peut être NULL si vous ne voulez pas recupérer la valeur à suprimer.

