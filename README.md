# Proyecto1-EDD
Primer proyecto del curso de Estructura de datos, en el cual realizamos una biblioteca magica utilizando estructuras como arboles AVL, B Y B+

## REQUISITOS DEL SISTEMA

### REQUISITOS MINIMOS

- Compilador C++ con soporte para C++20
- Sistema Operativo: Windows o Linux (Ubuntu/Debian)
- Make (herramienta de compilacion)
- Minimo 512 MB de RAM
- 50 MB de espacio en disco

### SOFTWARE NECESARIO

#### PARA UBUNTU/LINUX:

```bash
# Instalar compilador g++ y make
sudo apt-get update
sudo apt-get install build-essential

# Verificar instalacion
g++ --version
make --version
```

#### PARA WINDOWS:

**Opcion 1: MinGW-w64**
1. Descargar desde: https://sourceforge.net/projects/mingw-w64/
2. Instalar seleccionando arquitectura x86_64
3. Agregar al PATH: C:\mingw64\bin
4. Verificar desde CMD o PowerShell:
   ```cmd
   g++ --version
   mingw32-make --version
   ```

**Opcion 2: MSYS2**
1. Descargar desde: https://www.msys2.org/
2. Instalar y ejecutar MSYS2
3. Instalar herramientas:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S make
   ```
4. Agregar al PATH: C:\msys64\mingw64\bin

### SOFTWARE OPCIONAL

**Graphviz** (para generacion de graficas de arboles)

#### En Ubuntu/Linux:
```bash
sudo apt-get install graphviz

# Verificar instalacion
dot -V
```

#### En Windows:
1. Descargar desde: https://graphviz.org/download/
2. Instalar y agregar al PATH del sistema
3. Verificar desde CMD:
   ```cmd
   dot -V
   ```
## COMPILACION DEL PROYECTO

### EN UBUNTU/LINUX

#### Metodo 1: Usando Makefile (RECOMENDADO)

```bash
# Navegar al directorio del proyecto
cd /ruta/al/Proyecto1_EDD

# Compilar el proyecto
make

# El ejecutable generado sera: Proyecto1_EDD

### EN WINDOWS

#### Metodo 1: Usando Makefile (RECOMENDADO)

**Desde CMD o PowerShell:**

```cmd
# Navegar al directorio del proyecto
cd C:\ruta\al\Proyecto1_EDD

# Compilar el proyecto usando mingw32-make
mingw32-make

# El ejecutable generado sera: Proyecto1_EDD.exe
```

**Desde MSYS2 Terminal:**

```bash
# Navegar al directorio del proyecto
cd /c/ruta/al/Proyecto1_EDD

# Compilar el proyecto
make

# El ejecutable generado sera: Proyecto1_EDD.exe

## EJECUCION DEL PROGRAMA

### EN UBUNTU/LINUX

```bash
# Ejecutar el programa
./Proyecto1_EDD

# O con permisos explícitos
chmod +x Proyecto1_EDD
./Proyecto1_EDD
```

### EN WINDOWS

**Desde CMD:**
```cmd
Proyecto1_EDD.exe
```

**Desde PowerShell:**
```powershell
.\Proyecto1_EDD.exe
```

**Desde Explorador de Archivos:**
- Hacer doble clic en `Proyecto1_EDD.exe`
