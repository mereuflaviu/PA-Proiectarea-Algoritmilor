Problema 2  COLORARE
Pentru rezolvarea problemei am folosit o constantă MOD cu ajutorul căreia făceam modulo pentru a obține rezultatul final. Am utilizat o funcție powMod pentru a eficientiza ridicarea la putere și pentru a nu depăși limita de timp. Inițial am încercat în main cu pow() și modulo dar primeam erori deoarece trebuia să fac cast. În funcția powMod, cu doi parametri, baza și exponent, verific mai întâi ca bază e mai mică decât mod. Apoi mă asigur ca exponentul este mai mare decât 0. Verific dacă este impar și dacă este impar înmulțesc restul cu baza, iar dacă nu am baza la pătrat și împart exponentul la 2. 
În main citesc X si T. Dacă T primește V verific ultimul tip reținut prin intermediul variabilei lastType. Am făcut desenul pe foaie pentru variantele posibile pentru a înțelege mai ușor în cate moduri se pot lua culorile.

Problema 3  COMPRESIE
Fie urmatoarea operatie asupra unui sir de numere: se alege o subsecventa din sir si se înlocuieste cu suma elementelor din subsecventa. De exemplu daca avem sirul [1, 6, 2, 4, 5] si alegem subsecventa [6, 2, 4], obtinem [1, 12, 5]. Pentru un sir A de lungime n si un sir B de lungime m, determinati daca putem obtine doua siruri egale prin 0 sau mai multe aplicari ale operatiei definite mai sus, asupra lui A sau B, si aflati care e lungimea maxima pe care o poate avea sirul obtinut. 
Pentru rezolvarea problemei 3 am stocat datele în doi vectori A și B. Am parcurs simultan elementele vectorilor și i-am comparat. Dacă elementele de pe aceeași poziție erau egale mergeam la poziția următoare. Dacă elementele erau diferite, îl adunăm pe cel mai mic la poziția următoare din vectorul său. Dacă unul dintre vectori se termină înaintea celuilalt returnez -1 deoarece vectorii nu au cum să fie egali.