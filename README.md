# Instalar el Driver de MongoCxx
##Prerequisitos
- Tener instalado [CMake](https://cmake.org/) 3.2 o versiones posteriores
- Compilador que soporte C++11 (gcc, clang, o Visual Studio)
- boost header (opcional)
## MacOS
#### Paso 1. Instalar el Driver de MongoC (libmongoc y libbson)
Descargas el archivo comprimido de la version más reciente de la libreria:
`$ curl -LO https://github.com/mongodb/mongo-c-driver/releases/download/x.y.z/mongo-c-driver-1.16.2.tar.gz`
Lo descomprimes
`$ tar xzf mongo-c-driver-1.16.2.tar.gz`
Te cambias al directorio descargado
`$ cd mongo-c-driver-1.16.2`
Instalas el driver
`$ mkdir cmake-build`
`$ cd cmake-build`
`$ cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..`
`$ make install`
#### Paso 2. Descargar la version más reciente del driver MongoCxx
Puedes hacerlo vía git
`$ git clone https://github.com/mongodb/mongo-cxx-driver.git \ --branch releases/stable --depth 1`
Te cambias a la carpeta `/build` dentro de la carpeta descargada
`$ cd mongo-cxx-driver/build`
#### Paso 3. Configurar el driver
Configurar para que el driver MongoCxx se instale en `/usr/local`
`cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local`
#### Paso 4. Hacer Build e instalar el driver
`sudo make EP_mnmlstc_core`
`make && sudo make install`
## Listo 🤟
