FROM gcc:latest

WORKDIR /usr/src/app

COPY . .

# Compila todos os arquivos .cpp (
RUN g++ -o meu_restaurante *.cpp

CMD ["./meu_restaurante"]