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

int main() {

  // A loop to enter a user string and parse it to validate it as an email
  // address
  while (true) {

    // String input
    std::string email;
    std::cout << "Input email address (or exit): ";
    std::getline (std::cin, email);

    // Exit on user demand
    if (email == "exit") return 0;

    // String parsing
    bool invalidEmail = false;
    unsigned short len = email.length();
    // Determining the position of the @ character in the string
    unsigned short aPos = 0;
    for (unsigned short i = 0; i < len; i++) {
      if (email[i] == '@') {
        aPos = i;
        break;
      }
    }
    // Checking the string by the lengths of its first and second parts
    unsigned short len1 = aPos;
    unsigned short len2 = len - aPos;
    if (len1 < 1 || len1 > 63 || len2 < 2 || len2 > 65) invalidEmail = true;
    // Checking the string for dots ('.') at the beginning and end of both parts
    if (email[0] == '.' ||
        email[aPos - 1] == '.' ||
        email[aPos + 1] == '.' ||
        email[len - 1] == '.') {
      invalidEmail = true;
    }
    // Checking the string for the presence of two dots in a row
    // and invalid characters
    std::string lib = "-.!#$%&'*+-/=?^_`{|}~"; // Dictionary of valid characters
    if (!invalidEmail) {
      unsigned short libLength = lib.length();
      for (unsigned short i = 0; i < len && !invalidEmail; i++) {
        // When the @ character is reached, it is skipped
        // and the dictionary length is changed
        if (i == aPos) {
          i++;
          libLength = 2;
        }
        // Checks
        bool match = false;
        // Dictionary check
        for (unsigned short j = 0; j < libLength; j++) {
          if (email[i] == lib[j]) match = true;
        }
        // Checking by ASCII codes
        if ((email[i] >= '0' && email[i] <= '9') ||
            (email[i] >= 'a' && email[i] <= 'z') ||
            (email[i] >= 'A' && email[i] <= 'Z')) match = true;
        // Summarizing the results of the checking by dictionary and ASCII codes
        if (!match) invalidEmail = true;
        // Checking for the presence of two dots in a row.
        // The last character is definitely no longer a dot!
        if (email[i] == '.' && email [i + 1] == '.') invalidEmail = true;
      }
    }

    // Result output
    std::cout << (invalidEmail ? "No" : "Yes") << std::endl;
  }
}