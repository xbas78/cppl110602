/*------------------------------------------------------------------------------
    Задача (11.6.) 2. Проверка корректности email-адреса
--------------------------------------------------------------------------------
  Что нужно сделать
  Напишите программу, которая проверяет корректность email-адреса, введённого
пользователем.
  Согласно международным требованиям, корректный email-адрес должен состоять из
двух частей, разделённых знаком @. Первая часть должна иметь длину не менее
одного и не более 64 символов, вторая часть — не менее одного и не более 63
символов. Из символов допускаются только английские буквы, цифры и знак «-»
(дефис), а также точка. Точка не может быть первым или последним символом, а
кроме того, две точки не могут идти подряд. В первой части (которая предшествует
символу @), кроме вышеперечисленных, разрешены ещё следующие символы:

                                            !#$%&'*+-/=?^_`{|}~

  Пользователь вводит строку, задающую email-адрес. Программа должна вывести
слово Yes, если адрес корректен, а в противном случае — слово No.

  Примеры

  Корректные адреса:

simple@example.com
very.common@example.com
disposable.style.email.with+symbol@example.com
other.email-with-hyphen@example.com
fully-qualified-domain@example.com
user.name+tag+sorting@example.com
x@example.com (one-letter local-part)
example-indeed@strange-example.com
admin@mailserver1
example@s.example
mailhost!username@example.org
user%example.com@example.org

  Некорректные адреса:

John..Doe@example.com (две точки не могут идти подряд)
Abc.example.com (нет символа @)
A@b@c@example.com (символ @ должен быть только один)
a"b(c)d,e:f;g<h>i[j\k]l@example.com
1234567890123456789012345678901234567890123456789012345678901234+x@example.com
i_like_underscore@but_its_not_allow_in _this_part.example.com

  Советы и рекомендации
  Активно используйте оператор индексации строки str[i], но помните что индексы
начинаются с нуля, а не с единицы.
  Создайте отдельные функции, которые выдают первую и вторую части адреса для их
последующего анализа.
  Для валидации отдельных символов внутри части используйте дополнительные
строки-словари, состоящие из всех корректных символов для соответствующей части.

  Что оценивается
  Корректные результаты валидации адресов электронной почты. Должны
устанавливаться как валидные адреса, так и невалидные.

  Как отправить задание на проверку:
  Прислать ссылку на repl.it или файл *.срр с решением. Также вы можете создать
открытый репозиторий в GitHub с содержимым проекта.
------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>

bool checkEmail(const std::string& email) {
  std::string lib = "!#$%&'*+-/=?^_`{|}~";

  unsigned short len = email.length();
  int partLen = 0;
  bool firstPart = true;

  for (int i = 0; i < len; i++) {

    if (email[i] == '@') {
      if (!firstPart) return false;
      if (partLen < 1 || partLen > 63) return false;
      partLen = 0;
      firstPart = false;
      continue;
    }

    partLen++;

    if (email[i] == '.') {
      if ((i == 0) || (i == len - 1)) return false;
      if (email[i - 1] == '.') return false;
      continue;
    }

    if ((email[i] >= '0' && email[i] <= '9') ||
        (email[i] >= 'a' && email[i] <= 'z') ||
        (email[i] >= 'A' && email[i] <= 'Z') || email[i] == '-') continue;

    if (firstPart && lib.find_first_of(email[i]) != std::string::npos) continue;

    return false;
  }

  return !(firstPart || partLen < 1 || partLen > 64);
}

int main() {

  {
    std::cout << "Check correct emails" << std::endl;
    std::ifstream ifs ("data_good.txt");

    std::string line;
    while (std::getline(ifs, line)) std::cout << checkEmail(line) << std::endl;
  }

  {
    std::cout << "Check incorrect emails" << std::endl;
    std::ifstream ifs("data_bad.txt");

    std::string line;
    while (std::getline(ifs, line)) std::cout << checkEmail(line) << std::endl;
  }

  return 0;
}