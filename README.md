# yoloCounter: Contagem de Objetos com YOLO e OpenCV

O **yoloCounter** é um projeto que utiliza inteligência artificial para detectar e contar objetos em tempo real a partir de uma câmera ou vídeo. Ele é ideal para aplicações como controle de qualidade em linhas de produção, monitoramento de estoque, contagem de pessoas em espaços públicos e muito mais.

<div style="display: inline_block"><br>
    <img src="media/webcam.gif" alt="Projeto 1"  width="28%">
</div>

---

## O que é o yoloCounter?

O yoloCounter é um programa que combina duas tecnologias poderosas:
1. **YOLO (You Only Look Once)**: Um algoritmo de detecção de objetos que identifica e localiza objetos em imagens ou vídeos com alta precisão e velocidade.
2. **OpenCV**: Uma biblioteca de visão computacional que facilita o processamento de imagens e vídeos.

Com o yoloCounter, você pode:
- **Detectar objetos** em tempo real.
- **Contar quantos objetos** atravessam uma região de interesse (ROI) na tela.
- **Monitorar** o número de objetos atualmente dentro da ROI.

---

## Como Funciona?

O yoloCounter funciona em três etapas principais:

1. **Captura de Imagens**:
   - O programa captura imagens de uma câmera ou vídeo.
   - Você pode usar uma webcam, uma câmera IP ou um arquivo de vídeo.

2. **Detecção de Objetos**:
   - O YOLO analisa cada frame e identifica os objetos presentes.
   - Ele desenha caixas ao redor dos objetos detectados e exibe o nome da classe (por exemplo, "pessoa", "carro", "garrafa").

3. **Contagem de Objetos**:
   - O programa define uma região de interesse (ROI) na tela.
   - Ele conta quantos objetos já passaram pela ROI e quantos estão atualmente dentro dela.

---

## Como Usar?

### Pré-requisitos
Para usar o yoloCounter, você precisa ter instalado:
- **OpenCV**: Biblioteca de visão computacional.
- **Compilador C++**: Como `g++` ou `clang`.
- **MSYS2** (no Windows): Para compilar e executar o código.

### Passos para Executar

1. **Clone o Repositório**:
   ```bash
   git clone https://github.com/vitorshaft/yoloCounter.git
   cd yoloCounter
   ```

2. **Baixe os Arquivos do YOLO**:
   - Baixe os arquivos `yolov4-tiny.cfg`, `yolov4-tiny.weights` e `classes.txt` e coloque-os na pasta `config_files`.

3. **Compile o Código**:
   ```bash
   g++ -O3 src/yoloCounter.cpp -o yoloCounter -I"C:/msys64/mingw64/include/opencv4" -L"C:/msys64/mingw64/lib" -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_dnn -lopencv_videoio
   ```

4. **Execute o Programa**:
   - Para usar a webcam:
     ```bash
     ./yoloCounter
     ```
   - Para usar um vídeo:
     ```bash
     ./yoloCounter --video=caminho/para/video.mp4
     ```

5. **Ajuste a ROI**:
   - A região de interesse (ROI) é definida no código. Você pode ajustar as coordenadas no arquivo `yoloCounter.cpp` para adaptá-la ao seu cenário.

---

## Aplicações do yoloCounter

O yoloCounter pode ser usado em diversas áreas, como:

### 1. **Controle de Qualidade em Linhas de Produção**
   - Conte quantos produtos passam por uma esteira.
   - Detecte produtos defeituosos ou fora do padrão.

### 2. **Controle de Estoque**
   - Monitore a quantidade de itens em prateleiras ou depósitos.
   - Acompanhe a movimentação de mercadorias.

### 3. **Monitoramento de Tráfego**
   - Conte veículos em estradas ou cruzamentos.
   - Analise o fluxo de tráfego em tempo real.

### 4. **Segurança e Monitoramento**
   - Conte pessoas em espaços públicos ou privados.
   - Detecte objetos suspeitos em áreas monitoradas.

### 5. **Agricultura de Precisão**
   - Conte frutas ou vegetais em esteiras de classificação.
   - Monitore a movimentação de animais em fazendas.

---

## Exemplo de Uso

Aqui está um exemplo de como o yoloCounter pode ser usado em uma linha de produção:

1. **Configuração**:
   - Aponte a câmera para a esteira onde os produtos passam.
   - Defina a ROI na área onde os produtos devem ser contados.

2. **Execução**:
   - O programa detecta e conta cada produto que passa pela ROI.
   - Ele exibe o número total de produtos e quantos estão atualmente na área de interesse.

3. **Resultado**:
   - Você obtém dados precisos sobre a produção em tempo real.
   - Pode identificar gargalos ou problemas na linha de produção.

---

## Contribuição

Contribuições são bem-vindas! Se você quiser melhorar o yoloCounter, siga os passos abaixo:

1. Faça um fork do repositório.
2. Crie uma branch para sua feature (`git checkout -b feature/nova-feature`).
3. Commit suas mudanças (`git commit -m 'Adicionando nova feature'`).
4. Faça um push para a branch (`git push origin feature/nova-feature`).
5. Abra um Pull Request.

---

## Contato

Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato:

- **Nome**: [Vitor Domingues]
- **Email**: [vdmrvitor@gmail.com]
- **GitHub**: [vitorshaft](https://github.com/vitorshaft)