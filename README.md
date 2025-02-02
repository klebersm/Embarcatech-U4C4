# Embarcatech U4C4

Este projeto utiliza os botões A e B da placa BitdogLab para controlar o incremento/decremento de uma varíável que deve ser exibida na mariz de leds RGB.
Para as funções dos botões, foram utilizadas interrupções do sistema com alarmes para debounce das teclas.

## Funcionalidades das Teclas 🕹️

| Tecla | Funcionalidade          |
| ----- | ----------------------- |
| A     | Incrmenta o valor de i  |
| B     | Decrementa o valor de i |

## Hardware 🛠️

- Microcontrolador RP2040 (Raspberry Pi Pico).
- Botões tipo Switch.
- Display NeoPixel RGB 5x5.

## Software 💻

- **SDK do Raspberry Pi Pico:** O SDK (Software Development Kit) do Pico, que inclui as bibliotecas e ferramentas necessárias para desenvolver e compilar o código. [Instruções de instalação](https://www.raspberrypi.com/documentation/pico/getting-started/)
- **CMake:** Um sistema de construção multiplataforma usado para gerar os arquivos de construção do projeto.
- **Compilador C/C++:** Um compilador C/C++ como o GCC (GNU Compiler Collection).
- **Git:** (Opcional) Para clonar o repositório do projeto.

### O código está dividido em vários arquivos para melhor organização:

- **`U4T4.C`**: Código com a função de loop principal: lê as teclas e chama as funções de animação.
- **`neopixel.c/.h`:** Controla o display NeoPixel (inicialização e envio de cores).
- **`CMakeLists.txt`:** Define a estrutura do projeto para o CMake.
- **`diagram.json`:** Diagramas de conexões.
  |

## Como Compilar e Executar ⚙️

1. **Instale o SDK do Raspberry Pi Pico:** Siga as instruções no site oficial do Raspberry Pi.
2. **Clone este repositório:** `git clone git@github.com:klebersm/embarcatech-U4C4.git`
3. **Navegue até o diretório do projeto:** `cd Embarcatech-U4C4`
4. **Compile o projeto:** `cmake -B build && cmake --build build`
5. **Copie para o Pico:** Copie o arquivo `U4C4.uf2` da pasta `build` (gerada após a compilação) para o Raspberry Pi Pico. O programa iniciará automaticamente.

## Funcionamento do Loop Principal 🔄

```
while (true) {

        // Renderiza o caractere de acordo com o número armazenado em i
        switch(i){
            case 0:
                renderMatrix(CHAR_0);
                break;
            case 1:
                renderMatrix(CHAR_1);
                break;
            case 2:
                renderMatrix(CHAR_2);
                break;
            ...

            case 9:
                renderMatrix(CHAR_9);
                break;
            default:
                break;
        }

        // Insere um delay de 100ms
        sleep_ms(100);

        // Alterna o status do led vermelho
        led = !led;
        gpio_put(LED_R, led);
    }
```

O loop while (true) renderiza o valor de i na Matriz de leds e alterna o status do led vermelho. Como o intervalo de execução do loop é de 100ms, o led apresenta 5 ciclos de 200ms a cada segundo.

## Tratamento dos botões - Interrupções e Alarmes ⏱️

Os botões A e B foram inicializados como entradas em PULL UP e são monitorados por interrupções com uma função para o tratamento dessas interrupções. À medida que ocorre uma interrupção, a função de tratamento verifica qual o botão gerou o evento e qual o tipo de evento. Se o evento foi de FALL EDGE (borda de descida), significa que o botão foi pressionado e um alarme é gerado para ser disparado em 100ms (Tempo configurado para debounce). Se qualquer outro evento acontecer no mesmo botão, esse alarme é cancelado. Sendo assim, o alarme só é realmente disparado se o botão for pressionado e ficar 100ms sem sofrer qualquer alteração.

## 🔗 Link do Vídeo de Funcionamento:

https://drive.google.com/file/d/10UVoBCmHYdQiQWnTHUrCCxOcuyx9PWY3/view?usp=drive_link

## 📞 Contato

- 👤 **Autor**: Kleber Marçal

- 📧 **E-mail**:kleber.sm@gmail.com

---
