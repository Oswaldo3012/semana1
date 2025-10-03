#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 10

// Definir la estructura del producto
typedef struct {
    int id;
    char nombre[50];
    int stock;
    float precio;
    float ganancias;
} Producto;

int main() {
    Producto productos[MAX_PRODUCTOS];
    int opcion, cantidad, numProductos = 0;
    char nombreTemp[50];

    // Menú principal
    do {
        printf("\n=== MENU ===\n");
        printf("1. Registrar producto\n");
        printf("2. Vender producto\n");
        printf("3. Reabastecer producto\n");
        printf("4. Consultar informacion de productos\n");
        printf("5. Consultar ganancias obtenidas\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1: { // registrar producto
                if (numProductos >= MAX_PRODUCTOS) {
                    printf(" No se pueden registrar más productos.\n");
                    break;
                }
                printf("\n=== Registro de producto ===\n");
                printf("Ingrese ID del producto: ");
                scanf("%d", &productos[numProductos].id);
                getchar();

                printf("Ingrese nombre del producto: ");
                fgets(productos[numProductos].nombre, sizeof(productos[numProductos].nombre), stdin);
                productos[numProductos].nombre[strcspn(productos[numProductos].nombre, "\n")] = '\0';

                printf("Ingrese cantidad en stock: ");
                scanf("%d", &productos[numProductos].stock);

                printf("Ingrese precio unitario: ");
                scanf("%f", &productos[numProductos].precio);

                productos[numProductos].ganancias = 0.0;

                numProductos++;
                printf("Producto registrado correctamente.\n");
                break;
            }

            case 2: { // vender
                if (numProductos == 0) {
                    printf(" No hay productos registrados.\n");
                    break;
                }
                printf("Ingrese el nombre del producto a vender: ");
                fgets(nombreTemp, sizeof(nombreTemp), stdin);
                nombreTemp[strcspn(nombreTemp, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < numProductos; i++) {
                    if (strcmp(nombreTemp, productos[i].nombre) == 0) {
                        encontrado = 1;
                        printf("Ingrese cantidad a vender: ");
                        scanf("%d", &cantidad);

                        if (cantidad <= 0) {
                            printf(" La cantidad debe ser mayor que 0.\n");
                        } else if (cantidad > productos[i].stock) {
                            printf(" No hay suficiente stock disponible.\n");
                        } else {
                            productos[i].stock -= cantidad;
                            productos[i].ganancias += cantidad * productos[i].precio;
                            printf(" Venta realizada. Stock restante de %s: %d\n", productos[i].nombre, productos[i].stock);
                        }
                        break;
                    }
                }
                if (!encontrado) {
                    printf(" No existe un producto con ese nombre.\n");
                }
                break;
            }

            case 3: { // reabastecer
                if (numProductos == 0) {
                    printf(" No hay productos registrados.\n");
                    break;
                }
                printf("Ingrese el nombre del producto a reabastecer: ");
                fgets(nombreTemp, sizeof(nombreTemp), stdin);
                nombreTemp[strcspn(nombreTemp, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < numProductos; i++) {
                    if (strcmp(nombreTemp, productos[i].nombre) == 0) {
                        encontrado = 1;
                        printf("Ingrese cantidad a reabastecer: ");
                        scanf("%d", &cantidad);

                        if (cantidad <= 0) {
                            printf("La cantidad debe ser mayor que 0.\n");
                        } else {
                            productos[i].stock += cantidad;
                            printf(" Reabastecimiento exitoso. Stock actual de %s: %d\n", productos[i].nombre, productos[i].stock);
                        }
                        break;
                    }
                }
                if (!encontrado) {
                    printf("No existe un producto con ese nombre.\n");
                }
                break;
            }

            case 4: { // consultar info
                if (numProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }
                printf("\n--- Informacion de todos los productos ---\n");
                for (int i = 0; i < numProductos; i++) {
                    printf("ID: %d\n", productos[i].id);
                    printf("Nombre: %s\n", productos[i].nombre);
                    printf("Stock: %d\n", productos[i].stock);
                    printf("Precio unitario: $%.2f\n", productos[i].precio);
                    printf("Ganancias acumuladas: $%.2f\n", productos[i].ganancias);
                    printf("--------------------------------------\n");
                }
                break;
            }

            case 5: { // consultar ganancias
                if (numProductos == 0) {
                    printf(" No hay productos registrados.\n");
                    break;
                }
                printf("\n--- Ganancias por producto ---\n");
                float totalGanancias = 0;
                for (int i = 0; i < numProductos; i++) {
                    printf("Producto: %s | Ganancias: $%.2f\n",
                           productos[i].nombre, productos[i].ganancias);
                    totalGanancias += productos[i].ganancias;
                }
                printf("Ganancias totales: $%.2f\n", totalGanancias);
                break;
            }

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 6);

    return 0;
}
