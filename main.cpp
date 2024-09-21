#include <iostream>
#include "./include/Six.h"

int main() {
    size_t lengthNumber;
    std::cout << "Введите длину первого числа: ";
    std::cin >> lengthNumber;

    unsigned char defaultValue;
    std::cout << "Введите значение по умолчанию для первого числа (0-5): ";
    std::cin >> defaultValue;

    Six number1; 

    try {
        number1 = Six(lengthNumber, defaultValue);
        std::cout << "Первое число: ";
        for (size_t i = 0; i < number1.getSize(); ++i) {
            std::cout << number1.getData()[i];
        }
        std::cout << std::endl;
    } catch (const InvalidDigitException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Введите 3 цифры для второго числа (от 0 до 5): ";
    unsigned char arrayNumbers[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> arrayNumbers[i];
    }

    Six number2;
    try {
        number2 = Six({arrayNumbers[0], arrayNumbers[1], arrayNumbers[2]});
        std::cout << "Второе число: ";
        for (size_t i = 0; i < number2.getSize(); ++i) {
            std::cout << number2.getData()[i];
        }
        std::cout << std::endl;
    } catch (const InvalidDigitException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::string stringNumber;
    std::cout << "Введите строку из цифр для третьего числа (от 0 до 5): ";
    std::cin >> stringNumber;

    Six number3;
    try {
        number3 = Six(stringNumber);
        std::cout << "Третье число: ";
        for (size_t i = 0; i < number3.getSize(); ++i) {
            std::cout << number3.getData()[i];
        }
        std::cout << std::endl;
    } catch (const InvalidDigitException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    Six sumResult = number1;
    sumResult += number2;
    std::cout << "Сумма Число 1 + Число 2: ";
    for (size_t i = 0; i < sumResult.getSize(); ++i) {
        std::cout << sumResult.getData()[i];
    }
    std::cout << std::endl;

    Six subResult = number3;
    try {
        subResult -= number2;
        std::cout << "Разность Число 3 - Число 2: ";
        for (size_t i = 0; i < subResult.getSize(); ++i) {
            std::cout << subResult.getData()[i];
        }
        std::cout << std::endl;
    } catch (const SubtractionUnderflowException& e) {
        std::cerr << e.what() << std::endl;
    }

    Six mulResult = number1;
    mulResult *= number2;
    std::cout << "Произведение Число 1 * Число 2: ";
    for (size_t i = 0; i < mulResult.getSize(); ++i) {
        std::cout << mulResult.getData()[i];
    }
    std::cout << std::endl;

    Six copyOfNumber1 = number1;
    std::cout << "Копия Числа 1: ";
    for (size_t i = 0; i < copyOfNumber1.getSize(); ++i) {
        std::cout << copyOfNumber1.getData()[i];
    }
    std::cout << std::endl;

    Six movedNumber = std::move(number2);
    std::cout << "Перемещенное Число 2: ";
    for (size_t i = 0; i < movedNumber.getSize(); ++i) {
        std::cout << movedNumber.getData()[i];
    }
    std::cout << std::endl;

    std::cout << "Сравнение: " << std::endl;
    std::cout << "Число 1 == Копия Числа 1: " << (number1 == copyOfNumber1) << std::endl;
    std::cout << "Число 1 < Число 3: " << (number1 < number3) << std::endl;
    std::cout << "Число 3 > Число 1: " << (number3 > number1) << std::endl;

    return 0;
}
