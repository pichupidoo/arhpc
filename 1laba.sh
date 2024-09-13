#!/bin/bash

# Вывод информации об ОС и ядре
echo "===== OS and Kernel Information ====="
uname -a                                      #команда uname выводит информацию о системе. Ключ -a (от слова "all") указывает, что нужно вывести всю доступную информацию
cat /etc/os-release                           #Файл /etc/os-release содержит информацию о версии операционной системы. Команда cat выводит содержимое этого файла
echo ""

# Вывод информации о процессоре
echo "===== CPU Information ====="
lscpu
echo ""

# Вывод информации об оперативной памяти
echo "===== Memory Information ====="
free -h                                                    #Опция -h Она выводит объём памяти в удобных для чтения единицах измерения: килобайтах (K), мегабайтах (M), гигабайтах (G),
echo ""

# Вывод информации о сетевых интерфейсах и скорости соединения
echo "===== Network Interface Information ====="
ip -o addr show | awk '/inet / {print "Interface: " $2 " IP: " $4}'
ip -o link show | awk '{print "Interface: " $2 " MAC: " $17}' #выводит информацию об интерфейсах в формате одной строки для каждого интерфейса.       /link\/ether/: фильтрует строки, содержащие MAC-адрес (по шаблону link/ether).
DEFAULT_INTERFACE=$(ip route show to default | awk '{print $5}')
ethtool $DEFAULT_INTERFACE | grep "Speed"
echo ""

# Вывод информации о системных разделах
echo "===== Disk Partition Information ====="
df -h
echo ""

echo "Script completed successfully."
