# Philosophers

## 🍝 Description

`Philosophers` est un projet du cursus 42 visant à explorer les problématiques de **threading**, de **synchronisation** et de **gestion des ressources partagées**, à travers l'exercice classique des *Philosophes mangeurs*.

Le but est de simuler un ensemble de philosophes assis autour d’une table, qui doivent alterner entre **manger**, **penser**, et **dormir**, tout en partageant des fourchettes de manière sécurisée.

---

## 🧠 Objectifs pédagogiques

- Comprendre les **conditions de compétition (race conditions)**
- Apprendre à gérer des **verrous (mutex)** pour synchroniser l'accès à des ressources partagées
- Utiliser des **threads** pour créer une simulation parallèle cohérente
- Maîtriser les notions de **deadlock**, **starvation** et **livelock**

---

## 🔧 Compilation

```bash
make
```

---

## 🚀 Exécution

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

Exemple :

./philo 5 800 200 200

Cela lance une simulation avec :

    5 philosophes

    Temps de mort : 800ms

    Temps pour manger : 200ms

    Temps pour dormir : 200ms


---

## 🗃️ Structure du projet
``` bash
Philosophers/
├── src/             # Fichiers source principaux
├── lib/
├── Makefile
└── README.md
```

👤 Auteur

Projet réalisé par :

    👤 @Dadou1910

📄 Licence

Projet réalisé dans le cadre du cursus 42.
À usage pédagogique uniquement.
