//ESTRUCTURAS NECESARIAS

typedef struct {
    int month;
    int year;
} fecha;

typedef struct {
    char nombre_fuente[50];
    double valor_mes[12];
    //si el valor se elimino el vector tendra un valor de 1 para el mes, si no tendra un valor 0 para uno no eliminado
    int eliminado[12];
    //si el valor se usa para calculos este tendra el valor de 1, si NO se usa para calculos tendra valor 0
    int calculable[12];
} energia;

typedef struct {
    fecha date[12];
    energia data[18];
} datos;


//FUNCIONES NECESARIAS

void numeroColumnas(char filas[], int *numDatos);

void compilarFechas(char fila[], datos memoria[]);

void numeroYears(datos GWh[], int *numYear);

void leerTitulo(char fila[], datos memoria[], int numYear, int numFuente);

void compilarDatos(char fila[], datos memoria[], int numYear, int numFuentes, int meses[]);

void Imprimir_tabla(datos GWh[], int numYear, int num_mes_por_year[]);

void hacer_copia_seguridad(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]);

void escoger_fichero_salida(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]);

void guardar_datos(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]);

void eliminar_dato(datos GWh[], int numYear, int num_mes_por_year[]);
//FUNCIONES PARA CALCULOS
//Nota, si el dato es eliminado = 1 o calculable = 0, no hay que tenerlo en cuenta para los calculos, para los datos totales no uses la funcion de contar datos, ya que no se añaden comas en las primeras filas