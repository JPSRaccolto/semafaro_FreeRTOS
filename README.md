![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)


# 🛠️ Projeto: Semáforo Inteligente com Modo Noturno e Acessibilidade

## 📑 Sumário
- [🎯 Objetivos](#-objetivos)
- [📋 Descrição do Projeto](#-descrição-do-projeto)
- [⚙️ Funcionalidades Implementadas](#%EF%B8%8F-funcionalidades-implementadas)
- [🛠️ Requisitos do Projeto](#%EF%B8%8F-requisitos-do-projeto)
- [📂 Estrutura do Repositório](#-estrutura-do-reposit%C3%A1rio)
- [🖥️ Como Compilar](#%EF%B8%8F-como-compilar)
- [🤝 Contribuições](#-contribui%C3%A7%C3%B5es)
- [📽️ Demonstração em Vídeo](#%EF%B8%8F-demonstra%C3%A7%C3%A3o-em-v%C3%ADdeo)
- [📜 Licença](#-licen%C3%A7a)
- [💡 Considerações Finais](#-considera%C3%A7%C3%B5es-finais)

## 🎯 Objetivos
• Utilizar as task por meio do FreeRTOS .

• Utilizar o PWM para controlar a intensidade e frequência sonora dos buzzers.

• Aplicar o protocolo de comunicação I2C na integração com o display ssd1306.

• Utilizar a matriz de LED, LED RGB e buzzers para representar o semafaro de carros e pedestres .



## 📋 Descrição do Projeto
Este projeto utiliza a placa BitDogLab com os seguintes componentes:
- LED RGB (GPIOs 11, 12 e 13)
- Botão A (GPIO 5)
- Display SSD1306 via I2C (GPIO 14 e GPIO 15)
- Matriz de LED 5x5 (GPIO 7)
- Buzzers (GPIO 10 e 21)
  
## ⚙️ Funcionalidades Implementadas
1. **FreeRTOS:**
   - Utilização de tarefas operação separadamente uma da outra.
     
2. **Modulação PWM dos Buzzers:**
   - Altera o som emitido a depender do estado do semafaro.
     
3. **Troca do modo diurno/noturno com o Botão A:**
   - Altera entre os modos desenvolvidos.

4. **Display ssd1306:**
   - Apresenta a mensagem de procedimento para os pedestres.

5. **Representação Visual:**     
   - O LED RGB é responsável por simular o semáfaro, enquanto a matriz de LED é definida para representar a operação para o pedestre.
    
## 🛠️ Requisitos do Projeto
- **Uso de Tasks:** Via FreeRTOS
- **Alteração entre os modos:** Via Botão A
- **Representação Visual:** Via LED RGB e Matriz de LED.
- **Uso do Display SSD1306:** Apresenta a mensagem de procedimento para os pedestres que comunica via I2C.
- **Feedback Visual:** Via Buzzers
- **Organização do Código:** Código estruturado e comentado.


## 📂 Estrutura do Repositório
```
├── Semafaro_V2.c             # Código principal do projeto
└── FreeRTOSConfig       # Configura as tasks
└── ssd1306.c            # Configuração do controle do display
└── ssd1306.h            # Configura a .c como biblioteca
└── ws2812.pio.h         # Configura o controle da matriz de LED
└── font.h               # Configura as letras e números para o dispaly ssd1306
└── ...                  # Demais arquivos necessários
```

## 🖥️ Como Compilar
1. Clone o repositório:
   ```bash
   https://github.com/JPSRaccolto/semafaro_FreeRTOS.git
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd semafaro_FreeRTOS
   ```
3. Compile o projeto com seu ambiente de desenvolvimento configurado para o RP2040.
4. Carregue o código na placa BitDogLab.

## 🖥️ Metodo alternativo:
1. Baixe o repositório com arquivo zip.
2. Extraia para uma pasta de fácil acesso
3. Utilize a extensão raspberry pi pico dentro do VS Code para importar o projeto.
4. Aguarde ate criar o arquivo build
5. Utilize o ícone "_compile_" para compilar.
6. Utilize o "_RUN_" com a BitDogLab em modo boot seel para enviar o programa para a sua RP2040.
7. Agora, interaja com os botões e o teclado para mergulhar nas funcionalidades do projeto.

## 🧑‍💻 Autor
**João Pedro Soares Raccolto**

## 📝 Descrição
Tarefa apresentada ao Cepedi como parte dos critérios de avaliação do curso EmbarcaTech em Software e Sistemas Embarcados, com foco na aplicação prática do FreeRTOS, PWM, I2C e integração de hardware com o microcontrolador RP2040.

## 🤝 Contribuições
Este projeto foi desenvolvido por **João Pedro Soares Raccolto**.
Contribuições são bem-vindas! Siga os passos abaixo para contribuir:

1. Fork este repositório.
2. Crie uma nova branch:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça suas modificações e commit:
   ```bash
   git commit -m 'Minha nova feature'
   ```
4. Envie suas alterações:
   ```bash
   git push origin minha-feature
   ```
5. Abra um Pull Request.

## 📽️ Demonstração em Vídeo
- O vídeo de demonstração do projeto pode ser visualizado aqui: [Drive](https://drive.google.com/file/d/12uIxSjHNvvYUlo6QIuSOJo8DHYGK5s_F/view?usp=sharing)

## 💡 Considerações Finais
Este projeto oferece uma ótima oportunidade para consolidar conhecimentos sobre conversor FreeRTOS, manipulação de hardware,
I2C, PWM e desenvolvimento com microcontroladores. Certifique-se de seguir todos os requisitos e manter um código limpo e bem comentado.
