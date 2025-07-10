Volante Arduino HID com Pedais (Joystick HID de 3 Eixos)
Este projeto transforma um Arduino Leonardo / Pro Micro em um joystick HID com três eixos analógicos, simulando um volante com acelerador e freio. Ideal para jogos de corrida no PC!

Funcionalidades
> Simula volante e dois pedais (acelerador e freio)
> Usa a biblioteca Joystick.h para envio HID ao computador
> Inclui zona morta nos eixos para maior precisão
> Faz suavização do volante com média móvel
> Permite calibração fina do centro do volante

Componentes necessários
> Arduino Leonardo, Micro ou Pro Micro
> 3 potenciômetros (volante, acelerador, freio)
> Conexão via cabo USB
> Jumpers / protoboard (opcional)

Mapeamento dos pinos
Pino	Função
A0	Volante
A1	Acelerador
A2	Freio

Bibliotecas necessárias
Joystick.h (Arduino HID Library)
