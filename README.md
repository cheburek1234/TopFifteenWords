# TopFifteenWords

Логика работы: 
1. WordReader считывает слова из файла, подсчитывает количество вхождений слов ( исключаются из подсчета элементы которые не подходят под regExp([а-яa-z-]) или же входят в множество элементов notWords.
2. Каждая пара отправляется в модель WordModel на изменение или вставку.
3. WordProxyModelTopWords выполняет роль прокси-модели между исходной моделью и представлением. 
   Этот класс последовательно выполняет операции: сортировка по количеству вхождений, фильтрация ко количеству, сортировка по слову.
   Прокси-модель изменяется всякий раз, когда количество вхождений у нового ( или обновленного ) элемента больше или равно минимальному из максимальных элементов.
   
Для примера можно использовать файл "voyna-i-mir-tom-1.txt"
