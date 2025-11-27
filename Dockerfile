FROM gcc:latest

WORKDIR /usr/src/app

COPY . .

RUN g++ -o meu_restaurante *.cpp

CMD ["./meu_restaurante"]