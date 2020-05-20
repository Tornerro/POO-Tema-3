# POO-Tema-3

Firma X are un domeniu de business unde este necesar să se urmărească modul în care clienții plătesc (numerar, cec sau card de credit). Indiferent de modul de plata, firma X știe în ce data s-a efectuat plata și ce sumă a fost primită. Dacă se plătește cu cardul, atunci se cunoaște și numărul cardului de credit. Pentru cash, nu e necesara identificarea clientului care a făcut plata.
Structura de date: unordered_map sau unordered_set <id_plata, structura care reține datele plății>

Cerința suplimentară: 
- Să se adauge toate campurile relevante pentru modelarea acestei probleme.
- Să se construiască clasa template Gestiune care sa conțină numărul total de plăți de un anumit tip (incrementat  automat la adaugarea unei noi chitanțe) și structura de obiecte de tipul plății, alocat dinamic. Sa se supraincarce operatorul += pentru inserarea unei plăti în vector. 
- Să se construiască o specializare aferent tipul de plata prin card, care sa stocheze si numărul
de clienți, împreuna cu numele acestora. Specializarea va adapta operatorii menționați în
cerințe și operatorul la acest tip de plata.

Cerințe comune tuturor temelor:

- utilizarea sabloanelor
- utilizarea STL
- utilizarea variabilelor, funcțiilor statice, constantelor și a unei functii const
- utilizarea conceptelor de RTTI raportat la template-uri
- tratarea excepțiilor
- citirea informațiilor complete a n obiecte, memorarea și afișarea acestora

Cerințe generale aplicate fiecărei teme din acest fișier:
- să se identifice și să se implementeze ierarhia de clase;
- clasele să conțină constructori, destructori, =, funcție prietena de citire a datelor;
- clasa de baza sa conțină funcție virtuala de afisare, rescrisa în clasele derivate, iar operatorul de citire să fie implementat ca funcție prieten (în clasele derivate să se facă referire la implementarea acestuia în clasa de baza).
