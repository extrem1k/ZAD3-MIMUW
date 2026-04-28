Wprowadzenie
Liczbą kolosalną nazwiemy reprezentację nieujemnej liczby całkowitej za pomocą listy cyfr, które również są liczbami kolosalnymi. Reprezentacja ta, opisana w inny, ale równoważny sposób, była rozważana przez Donalda Knutha.

Wartością liczby kolosalnej jest suma potęg dwójki o wykładnikach będących wartościami cyfr tej liczby.

Powiemy, że liczba kolosalna jest znormalizowana, jeśli jej cyfry są znormalizowane, i są one uporządkowane (ściśle) malejąco według wartości. Każda nieujemna liczba całkowita ma dokładnie jedną reprezentację w postaci znormalizowanej liczby kolosalnej.


Tekstowym zapisem liczby kolosalnej jest słowo języka z poniższą gramatyką w rozszerzonej notacji BNF:


<kolosalna> ::= { "1" <cyfra> } "0"


<cyfra> ::= <kolosalna>


Można udowodnić, że jest to język słów powstałych przez dopisanie symbolu 0 na koniec wyrażenia nawiasowego, w którym 1 pełni rolę nawiasu otwierającego, a 0 to nawias zamykający.


Tekstowy zapis liczby kolosalnej można przekształcić na niepozycyjny zapis binarny. W tym celu:



symbole 0, 1, zamieniamy na bity 0, 1;


na końcu dopisujemy tyle bitów 0, ile potrzeba, by długość ciągu była podzielna przez osiem;


ciąg bitów dzielimy na porcje po osiem i umieszczamy je w kolejnych bajtach;


w danym bajcie bity zapisujemy, zaczynając od pozycji najbardziej znaczących.


Wszystkie liczby kolosalne, których zapisem są poniższe słowa:


101010101010101010100

110010110011001010100

1100101110001010100

1100101010101110000

1100110010101110000

11100010101110000

10101110001110000

11100011100011000

1101100011000

1110010011000

mają wartość dziesięć. Ostatnia z nich jest znormalizowana.

Inne przykłady znormalizowanych liczb kolosalnych są poniżej:

0 to 0

1 to 100

2 to 11000

3 to 1100100

4 to 1110000

5 to 111000100

6 to 11100011000

7 to 1110001100100

8 to 111001000

9 to 11100100100

10 to 1110010011000

11 to 111001001100100

12 to 111001001110000

13 to 11100100111000100

14 to 1110010011100011000

15 to 111001001110001100100

16 to 111100000

17 to 11110000100

18 to 1111000011000

19 to 111100001100100

20 to 111100001110000

50 to 11110001001111000011000

64 to 1111000110000

100 to 11110001100011110001001110000

127 to 111100011000111100010011110000111001001110001100100

128 to 111100011001000

144 to 11110001100100111100000

199 to 111100011001001111000110001110001100100

256 to 11110010000

1000 to 1111001001001111001000111100011001001111000110001111000100111001000

1009 to 111100100100111100100011110001100100111100011000111100010011110000100

1024 to 111100100110000

10000 to 111100100111000100111100100110001111001001001111001000111100000

65536 to 11111000000

200791 to 11111000010011111000001111001001110000111100011000111100001110001100100

2^65536 to 1111110000000

2^65537 to 111111000001000

2^(2^65536) to 111111100000000

2^(2^(2^65536)) to 11111111000000000

5+2^(2^(2^65536)) to 1111111100000000111000100

Pozycyjny zapis binarny trzech ostatnich wymienionych wartości miałby więcej bitów, niż jest atomów na Ziemi. Niepozycyjny zapis binarny liczb kolosalnych ma, odpowiednio, 2, 3 i 4 bajty.

Polecenie
Zaimplementuj kalkulator umożliwiający wykonywanie obliczeń na liczbach kolosalnych.

Kalkulator ma pamięć, która jest stosem. Na początku stos jest pusty.

Program czyta z wejścia polecenia i wykonuje je. Kończy pracę, gdy polecenia się skończą.

Postać danych
Dane to ciąg wierszy. W każdym wierszu jest jedno polecenie.

Program rozpoznaje polecenia i wykonuje odpowiednie akcje:

tekstowy zapis liczby kolosalnej, niekoniecznie znormalizowanej:

włóż na stos wczytaną liczbę;

kropka '.':

zdejmij liczbę ze stosu i wypisz ją na wyjście;

dwukropek ':':

zduplikuj liczbę, czyli zdejmij ją ze stosu i włóż ją na stos dwukrotnie;

daszek '^':

zdejmij liczbę ze stosu i włóż na stos potęgę 2, w której ta liczba jest wykładnikiem;

plus '+':

zdejmij ze stosu dwie liczby i włóż na stos ich sumę;

razy '*':

zdejmij ze stosu dwie liczby i włóż na stos ich iloczyn.

Oprócz znaków wymienionych powyżej, na wejściu nie ma żadnych innych.

Zakładamy, że zawsze, gdy program będzie zdejmował wartość ze stosu, stos będzie niepusty.

Nie zakładamy, że po wykonaniu ostatniego polecenia stos będzie pusty.

Postać wyniku
Wynikiem programu jest ciąg wierszy, po jednym dla każdego wykonanego polecenia kropka '.'. W wierszu jest tekstowa reprezentacja znormalizowanej liczby kolosalnej.
