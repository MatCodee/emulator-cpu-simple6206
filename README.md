### emulator-cpu-simple6206

# Este es un simple emulador de la cpu 6502 en C++
El objetivo de este codigo es aprender a construir un emulador de un cpu en este caso me enfoque en 6506 porque tiene pocos registros.
Tengo una carpeta de paginas en donde estan los recursos de este proyecto. 
Si esta haciendo este mismo proyecto hay muchos codigos en github de este mismo proyectoi completos y de muy buena calidad, puede ver en la carpeta DOC

Para correr este proyecto:
```
./compile.sh
./run.sh
```
Correr de forma manual
```
mkdir build
cd build
cmake ..
```
En linux:
```
make
./main
```
En Windows, tener el compilador o agregar visual estudio comunity
```
cmake --build .
cd Debug
./main
```

No necesita librerias externas ya que es un codigo simple 
