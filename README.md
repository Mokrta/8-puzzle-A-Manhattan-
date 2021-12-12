# 8-puzzle-Astar-Manhattan-
### Файл 8pfuncs.h містить оголошення класів та визначення їх методів.
  1. Клас Stan містить масив розміром 9, що відповідає певному стану (розмішенню клітинок) поля.
    1. 3 перевантажені конструктори: для автоматичного створення, для введення стану і для копіювання стану з іншого;
    2. Перевантажений оператор присвоювання;
    3. Переванажені оператори перевірки однаковості (==, !=);
    4. Метод index_of() приймає значення клітинки, вектор, в якому шукати, і повертає індекс шуканого значення;
    5. Метод distManhattan() - еврістична функція, повертає "відстань" до елемента за манхеттенським шляхом;
    6. Метод print() - виводить стан у консоль.
  
  2. Клас Neighbour створений для швидкого визначення "сусідів" певного стану - тобто, які стани можна отримати з поточного за одне переміщення "нуля" (пустої клітинки).
    Містить контейнер - словник для швидкого пошуку "сусідніх" клітинок до обраної клітинки (тобто, з якими клітинками може помінятись місцями "нуль");
    1. Конструктор заповнює словник значенням;
    2. Метод indexNeighbours() - приймає індекс клітинки, і повертає вектор - всі сусіні клітинки, з якими введений може помінятись
  
  3. Клас Node відповідає одному вузлу дерева, містить стан, вказівник на попередній (батьківський) вузол і рівень, на якому знаходиться у дереві.
    1. Конструктор - приймає і присвоює значення всім полям классу;
    2. Сеттери і геттери - назви кажуть самі за себе, методи для зміни і доступу прихованих полів;
    3. Метод print() - виводить стан, який відповідає даному вузлу і його рівень у дереві.
 
