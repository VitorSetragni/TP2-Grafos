# Criar um venv: python -m venv venv
# Ativar venv: source venv/bin/activate
# Instalar dependecias: pip install pillow

from PIL import Image
import os
import sys


def converter_para_ppm(caminho_imagem, caminho_saida=None):
    # Abre a imagem em qualquer formato
    img = Image.open(caminho_imagem)


    # Define o nome de saída
    if caminho_saida is None:
        nome_base, _ = os.path.splitext(caminho_imagem)
        caminho_saida = nome_base + ".ppm"
    
    # Converte para RGB (PPM não suporta RGBA)
    if img.mode != "RGB":
        img = img.convert("RGB")

    # Salva como PPM
    img.save(caminho_saida, format="PPM")
    print(f"Imagem convertida com sucesso para: {caminho_saida}")

def main():
    if len(sys.argv) < 2:
        print("Uso: python3 img_converter.py <caminho_da_imagem>")
        sys.exit(1)

    caminho_imagem = sys.argv[1]
    converter_para_ppm(caminho_imagem)

if __name__ == "__main__":
    main()

