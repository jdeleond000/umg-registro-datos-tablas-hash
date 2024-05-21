#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos el tamaño de la tabla de hash
#define TAM 300

// Estructura que representa una entrada en la tabla de hash
typedef struct {
    char dpi[14];  // El DPI es una cadena de caracteres con longitud 13 + 1 para el carácter nulo
    char primerNombre[25]; // Primer nombre
    char segundoNombre[25]; // Segundo nombre (opcional)
    char primerApellido[25]; // Primer apellido
    char segundoApellido[25]; // Segundo apellido (opcional)
    char direccion[50]; // Dirección (opcional)
    char correoElectronico[50]; // Correo electrónico (opcional)
    char telefono[15]; // Teléfono (opcional)
} Entrada;

// Tabla de hash para almacenar las entradas
Entrada *tabla[TAM];

// Inicializa la tabla de hash, estableciendo todas las posiciones como vacías (NULL)
void init() {
    for (int i = 0; i < TAM; ++i) {
        tabla[i] = NULL;
    }
}

// Función que convierte el DPI en un número para encontrar su posición en la tabla
unsigned int hash(const char *dpi) {
    unsigned int hash = 0;
    while (*dpi) {
        hash = (hash * 31) + *dpi++;
    }
    return hash % TAM;
}

// Función para cargar una entrada en la tabla de hash
void cargaArchivo(const char *dpi, const char *primerNombre, const char *segundoNombre, const char *primerApellido, const char *segundoApellido,
                  const char *direccion, const char *correoElectronico, const char *telefono) {
    unsigned int clave = hash(dpi);
    unsigned int original_clave = clave;
    int i = 1;

    // Manejo de colisiones: si la posición está ocupada, busca la siguiente posición disponible
    while (tabla[clave] != NULL) {
        printf("Colisión en tabla[%d], sondeo...\n", clave);
        clave = (original_clave + i) % TAM;
        if (clave == original_clave) {
            printf("La tabla hash está llena, no se puede insertar el registro\n");
            return;
        }
        i++;
    }

    // Reserva espacio para una nueva entrada y copia los datos
    Entrada *nuevaEntrada = (Entrada *)malloc(sizeof(Entrada));
    strncpy(nuevaEntrada->dpi, dpi, 13);
    nuevaEntrada->dpi[13] = '\0'; // Asegura que la cadena termine con un carácter nulo
    strncpy(nuevaEntrada->primerNombre, primerNombre ? primerNombre : "", 24);
    strncpy(nuevaEntrada->segundoNombre, segundoNombre ? segundoNombre : "", 24);
    strncpy(nuevaEntrada->primerApellido, primerApellido ? primerApellido : "", 24);
    strncpy(nuevaEntrada->segundoApellido, segundoApellido ? segundoApellido : "", 24);
    strncpy(nuevaEntrada->direccion, direccion ? direccion : "", 49);
    strncpy(nuevaEntrada->correoElectronico, correoElectronico ? correoElectronico : "", 49);
    strncpy(nuevaEntrada->telefono, telefono ? telefono : "", 14);

    // Inserta la nueva entrada en la tabla
    tabla[clave] = nuevaEntrada;
    printf("Registro insertado en tabla[%d]\n", clave);
}

// Función para cargar entradas desde un archivo
void cargarDesdeArchivo(const char *rutaArchivo) {
    FILE *file = fopen(rutaArchivo, "r");
    if (!file) {
        perror("Error abriendo el archivo");
        return;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), file)) {
        // Elimina el carácter de nueva línea si existe
        size_t len = strlen(linea);
        if (len > 0 && linea[len - 1] == '\n') {
            linea[len - 1] = '\0';
        }

        // Divide la línea en campos usando ';' como delimitador
        char *campos[8];
        for (int i = 0; i < 8; i++) {
            campos[i] = strtok(i == 0 ? linea : NULL, ";");
            if (campos[i] == NULL) {
                campos[i] = ""; // Si un campo está vacío, se asigna una cadena vacía
            }
        }

        printf("Procesando línea: %s\n", linea);

        // Carga la entrada en la tabla
        cargaArchivo(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6], campos[7]);
    }

    fclose(file);
}

// Función para buscar una entrada en la tabla por DPI
void busqueda(const char *dpi) {
    unsigned int clave = hash(dpi);
    unsigned int original_clave = clave;
    int i = 1;

    // Busca la entrada en la tabla de hash
    while (tabla[clave] != NULL) {
        if (strncmp(tabla[clave]->dpi, dpi, 13) == 0) {
            Entrada *entrada = tabla[clave];
            printf("DPI: %s\n", entrada->dpi);
            printf("Nombre: %s %s\n", entrada->primerNombre, entrada->segundoNombre);
            printf("Apellido: %s %s\n", entrada->primerApellido, entrada->segundoApellido);
            printf("Dirección: %s\n", entrada->direccion);
            printf("Correo: %s\n", entrada->correoElectronico);
            printf("Teléfono: %s\n", entrada->telefono);
            return;
        }
        clave = (original_clave + i) % TAM;
        if (clave == original_clave) {
            break;
        }
        i++;
    }

    printf("No se encontró el registro con DPI %s\n", dpi);
}

// Función para encontrar la ubicación de una entrada en la tabla por DPI
void ubicacion(const char *dpi) {
    unsigned int clave = hash(dpi);
    unsigned int original_clave = clave;
    int i = 1;

    // Busca la entrada en la tabla de hash
    while (tabla[clave] != NULL) {
        if (strncmp(tabla[clave]->dpi, dpi, 13) == 0) {
            printf("El registro con DPI %s se encuentra en la posición %d de la tabla.\n", dpi, clave);
            return;
        }
        clave = (original_clave + i) % TAM;
        if (clave == original_clave) {
            break;
        }
        i++;
    }

    printf("No se encontró el registro con DPI %s\n", dpi);
}

// Función para eliminar todas las entradas de la tabla
void eliminar() {
    for (int i = 0; i < TAM; i++) {
        if (tabla[i] != NULL) {
            free(tabla[i]);
            tabla[i] = NULL;
        }
    }
    printf("Toda la información de la tabla ha sido eliminada y la memoria ha sido liberada.\n");
}

int main() {
    // Inicializa la tabla de hash
    init();

    int opcion;
    do {
        // Muestra las opciones disponibles
        printf("\nOpciones:\n");
        printf("1. Carga de archivo\n");
        printf("2. Búsqueda\n");
        printf("3. Ubicación\n");
        printf("4. Eliminar\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        // Ejecuta la opción seleccionada por el usuario
        if (opcion == 1) {
            char rutaArchivo[256];
            printf("Ingrese la ruta del archivo a cargar: ");
            scanf("%255s", rutaArchivo);
            cargarDesdeArchivo(rutaArchivo);
        } else if (opcion == 2) {
            char dpi[14];
            printf("Ingrese el DPI a buscar: ");
            scanf("%13s", dpi);
            busqueda(dpi);
        } else if (opcion == 3) {
            char dpi[14];
            printf("Ingrese el DPI a buscar: ");
            scanf("%13s", dpi);
            ubicacion(dpi);
        } else if (opcion == 4) {
            eliminar();
        }
    } while (opcion != 5);

    return 0;
}
