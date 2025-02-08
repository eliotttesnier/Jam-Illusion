#!/bin/bash

# Vérifie si ffmpeg est installé
if ! command -v ffmpeg &> /dev/null
then
    echo "ffmpeg n'est pas installé. Veuillez l'installer et réessayer."
    exit 1
fi

# Dossier contenant les fichiers MP3 (le dossier actuel)
INPUT_DIR="assets/sounds/"

# Crée un sous-dossier pour les fichiers WAV convertis
OUTPUT_DIR="./assets/sounds/wav"
mkdir -p "$OUTPUT_DIR"

# Parcourt tous les fichiers .mp3 dans le dossier
for file in "$INPUT_DIR"/*.mp3; do
    if [[ -f "$file" ]]; then
        # Récupère le nom de fichier sans extension
        filename=$(basename "$file" .mp3)
        
        # Convertit le fichier MP3 en WAV
        ffmpeg -i "$file" "$OUTPUT_DIR/$filename.wav" -y
        
        echo "Converti : $file -> $OUTPUT_DIR/$filename.wav"
    fi
done

echo "Conversion terminée ! Tous les fichiers WAV sont dans le dossier $OUTPUT_DIR"
