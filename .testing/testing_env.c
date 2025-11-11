#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int setenv_simple(const char *name, const char *value, int overwrite) {
    // 1. VALIDACIÓN BÁSICA (Requerido por POSIX)
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL; // Nombre inválido
        return -1;
    }

    // 2. REGLA DE SOBRESCRITURA
    // Si la variable existe Y 'overwrite' es CERO, salimos sin hacer nada.
    if (getenv(name) != NULL && overwrite == 0) {
        return 0; // Éxito (no se hacen cambios)
    }

    // 3. CREAR EL STRING "name=value"
    // Calculamos el tamaño y asignamos memoria (+1 para '=', +1 para '\0')
    size_t required_len = strlen(name) + 1 + strlen(value) + 1;
    char *new_env_var = (char *)malloc(required_len);
    
    if (new_env_var == NULL) {
        errno = ENOMEM; // No hay memoria
        return -1;
    }

    // Formateamos el string en la memoria asignada
    snprintf(new_env_var, required_len, "%s=%s", name, value);

    // 4. INSERTAR/ACTUALIZAR LA VARIABLE
    // putenv() usa el string 'new_env_var' que hicimos con malloc().
    // Esto asegura que la librería C tenga su propia copia, como requiere setenv().
    if (putenv(new_env_var) != 0) {
        free(new_env_var); // Si falla, liberamos la memoria
        return -1;
    }

    return 0; // Éxito
}

// --- Ejemplo de uso (Opcional) ---
/*
int main() {
    // 1. Añadir
    setenv_simple("TEST_VAR", "inicial", 1);
    printf("Valor inicial: %s\n", getenv("TEST_VAR"));

    // 2. Intentar no sobrescribir
    setenv_simple("TEST_VAR", "nuevo", 0);
    printf("Valor con overwrite=0: %s\n", getenv("TEST_VAR")); // Debe seguir siendo "inicial"

    // 3. Sobrescribir
    setenv_simple("TEST_VAR", "actualizado", 1);
    printf("Valor con overwrite=1: %s\n", getenv("TEST_VAR")); // Debe ser "actualizado"
    
    return 0;
}
*/
