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
free -h                                     #Опция -h Она выводит объём памяти в удобных для чтения единицах измерения: килобайтах (K), мегабайтах (M), гигабайтах (G),
echo ""

# Вывод информации о сетевых интерфейсах и скорости соединения
echo "===== Network Interface Information ====="
ip -o addr show | awk '/inet / {print "Interface: " $2 " IP: " $4}'
ip link show | grep "link/ether" | awk '{print "Interface: " $2 " MAC: " $2}'
DEFAULT_INTERFACE=$(ip route show to default | awk '{print $5}')  #route show to default — выводит маршрут по умолчанию, то есть информацию о сетевом интерфейсе,
                                                                  #который используется для доступа в интернет или к внешним сетям.
                                                                  #Маршрут по умолчанию указывает, через какой интерфейс передаётся трафик, если не указаны другие маршруты.
ethtool $DEFAULT_INTERFACE | grep "Speed"
echo ""

# Вывод информации о системных разделах
echo "===== Disk Partition Information ====="
df -h
echo ""

echo "Script completed successfully."