#!/bin/bash

if [ ! -f /etc/bash.bashrc ]; then
    echo "Le fichier /etc/bash.bashrc n'existe pas."
    exit 1
fi

count=$(grep -c -E '^if.*n$' /etc/bash.bashrc)

echo "Le nombre de lignes qui commencent par 'if' et qui se terminent par 'n' est: $count"
