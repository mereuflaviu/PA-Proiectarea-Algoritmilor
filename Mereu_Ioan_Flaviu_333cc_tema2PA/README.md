Problema 1 Numarare

Am abordat problema Numarare astfel: identificând muchiile comune și construind un nou graf pe baza acestora. Ulterior, am calculat numărul de căi de la nodul 1 la nodul n în graful rezultat.
Am sortat topologic pentru a număra căile de la nodul src la nodul dest folosind programare dinamică.

Problema 2 Trenuri

Am mapat numele oraselor la indici pentru rapiditate. Am sortat topologic nodurile. Am folosit programarea dinamica pentru a itera prin fiecare oras in ordine topologica si am actualizat maxCities pentru fiecare nod vecin.

Problema 3 Drumuri

Am luat o functie init pentru a inițializa un vector de distanțe cu o valoare specificată. Am folosit  dijkstra pentru a calcula cea mai scurta distanta de la un nod la celelalte. Am folosit  dijkstra e 3 ori. Pentru x si y pe graful normal, iar pentru Z pe graful transpus.

Problema 4 Scandal

Am creat o structura Node pentru a stoca informatii despre fiecare nod din graf, cum ar fi conexiunile (vecinii), timpii de descoperire si cei mai mici timpi (pentru algoritmul Tarjan), si câteva variabile booleene pentru starea nodului. ExtractComponent extrage o componentă tare conexa din graf. In functia TarjanSCC implementez algoritmul Tarjan pentru a gasi SCC-urile dintr-un graf. Apoi sortez topologic cu tarjan. 
