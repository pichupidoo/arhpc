#!/bin/bash

# Функция для чтения клавиш
read_key() {
    local REPLY
    # Включаем режим чтения одного символа
    read -n 1 -s REPLY
    echo -n "$REPLY"
}

# Чтение клавиш и вывод их кодов
echo "Нажмите на клавиши, чтобы увидеть их коды (для выхода нажмите 'q'):"
while true; do
    key=$(read_key)
    case "$key" in
        $'\e') # ESC
            echo "ESC"
            ;;
        $'\x0a') # ENTER
            echo "ENTER"
            ;;
        "q")
            echo "Выход"
            exit 0
            ;;
        *)
            echo "Клавиша: '$key'"
            ;;
    esac
done