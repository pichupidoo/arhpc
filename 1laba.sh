#!/bin/bash

echo "===== OS and Kernel Information ====="
hostnamectl | grep "Operating System\|Kernel"                                                              
echo ""


echo "===== CPU Information ====="
lscpu | grep "Имя модели\|CPU"
lscpu | grep "L1i cache\|L2 cache\|L3 cache"
echo ""


echo "===== Memory Information ====="
free -h | awk '/Память:/   {print "Всего:" $2}'
free -h | awk '/Память:/   {print "Использовано:" $3}'
free -h | awk '/Память:/   {print "Доступно:" $4}'                                                 
echo ""


echo "===== Network Interface Information ====="
ip -o addr show | awk '/inet / {print "Interface: " $2 " IP: " $4}'
ip -o link show | awk '{print "Interface: " $2 " MAC: " $17}' 
iwconfig | grep "Bit Rate"
echo ""


echo "===== Disk Partition Information ====="
df -h
echo ""