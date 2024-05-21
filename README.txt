# Proyecto 2
Este proyecto implementa una tabla de hash para almacenar y gestionar datos personales. Permite cargar datos desde un archivo, buscar registros por DPI, mostrar la ubicación de un registro en la tabla y eliminar todos los registros.

## Archivos
- src/main.c: Contiene el código fuente del programa.
- datos.txt: Archivo de entrada con los datos personales.
- README.md: Este archivo con instrucciones.

## Instrucciones para Compilar y Ejecutar

### Requisitos
- [CLion](https://www.jetbrains.com/clion/) (Editor y entorno de desarrollo integrado)
- [CMake](https://cmake.org/) (Sistema de construcción)
- [GCC](https://gcc.gnu.org/) (Compilador de C)

### Pasos
#### Usando CLion

1. **Abrir CLion**: Inicia CLion en tu computadora. (Puede utilizar cualquier IDE de preferencia)
2. **Abrir Proyecto**: Selecciona Open en la pantalla de bienvenida y navega hasta la carpeta raíz del proyecto. Abre la carpeta del proyecto.
3. **Construir el Proyecto**:
- Haz clic en el botón Build en la esquina superior derecha de la ventana. Esto compilará tu proyecto y generará un ejecutable.
4. ** Ejecutar el Proyecto**:
Haz clic en el botón Run (icono de una flecha verde) en la esquina superior derecha de la ventana. Esto ejecutará el programa.

### Archivos de entrada

Archivo de Entrada (datos.txt): Debe crear este archivo en la carpeta raíz del proyecto. Cada línea de este archivo debe contener los datos personales separados por punto y coma (;). Ejemplo de datos.txt:
scss

1234567890;Juan;;Perez;;Calle 123;juan.perez@correo.com;123456789;
2345678901;Maria;Jose;Gomez;Rodriguez;Avenida 456;maria.gomez@correo.com;987654321;
3456789012;Luis;;Ramirez;;Calle 789;luis.ramirez@correo.com;111222333;

###Opciones del Menú

1. Carga de Archivo: Permite cargar datos personales desde un archivo especificado por el usuario.
2. Búsqueda: Permite buscar un registro en la tabla por DPI y muestra la información completa si el registro se encuentra.
3. Ubicación: Muestra la posición de un registro en la tabla por DPI.
4. Eliminar: Elimina todos los registros de la tabla y libera la memoria utilizada.
5. Salir: Cierra el programa.

### Ejemplo de uso

Crear Archivo de Entrada: Crea un archivo llamado datos.txt en la carpeta raíz del proyecto con el siguiente contenido:

1234567890;Juan;;Perez;;Calle 123;juan.perez@correo.com;123456789;
2345678901;Maria;Jose;Gomez;Rodriguez;Avenida 456;maria.gomez@correo.com;987654321;
3456789012;Luis;;Ramirez;;Calle 789;luis.ramirez@correo.com;111222333;


Compilar y Ejecutar: Sigue las instrucciones anteriores para compilar y ejecutar el programa.

### Interacción con el Programa

## Carga de Archivo:

1. Al seleccionar la opción 1, ingresa la ruta del archivo datos.txt.
2. El programa cargará los datos desde el archivo y los almacenará en la tabla de hash.

## Búsqueda:

1. Al seleccionar la opción 2, ingresa el DPI a buscar.
2. El programa mostrará la información completa del registro si se encuentra.

## Ubicación:

1. Al seleccionar la opción 3, ingresa el DPI a buscar.
2. El programa mostrará la posición del registro en la tabla de hash si se encuentra.

## Eliminar:

1. Al seleccionar la opción 4, todos los registros serán eliminados y la memoria será liberada.

### IMPORTANTE
1. Asegurarse de que el archivo datos.txt esté en la carpeta raíz del proyecto.
2. Si hay errores en los datos del archivo de entrada, el programa los manejará adecuadamente.
3. Puede modificar el archivo datos.txt para probar diferentes datos personales.