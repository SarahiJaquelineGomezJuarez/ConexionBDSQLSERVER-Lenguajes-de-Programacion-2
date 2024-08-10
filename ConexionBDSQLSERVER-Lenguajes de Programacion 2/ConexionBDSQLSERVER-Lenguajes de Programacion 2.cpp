// ConexionBDSQLSERVER-Lenguajes de Programacion 2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>// Librería para funciones de Windows, como la configuración de la consola.
#include <windows.h>// Librería para funcionalidades de Windows
#include <sql.h>// Librería principal de ODBC para funciones y estructuras
#include <sqlext.h>// Librería de extensiones de ODBC para funciones adicionales
#include <iomanip>// Librería para manipulación de formatos de entrada y salida
#include <locale>// Librería para manejo de locales
#include <codecvt>// Librería para conversiones entre diferentes codificaciones de caracteres
#include <string>// Librería para manejar cadenas de texto

using namespace std;// Usar el espacio de nombres estándar para simplificar el uso de clases y funciones comunes.

// Configura la consola para que use la codificación UTF-8
void SetConsoleToUtf8() {
    SetConsoleOutputCP(CP_UTF8);// Establece la página de códigos de salida de la consola a UTF-8.
    SetConsoleCP(CP_UTF8);// Establece la página de códigos de entrada de la consola a UTF-8.
}

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;// Convertidor para cadenas UTF-8 a UTF-16

int main() {
    // Configurar la consola para UTF-8
    SetConsoleToUtf8();

    SQLHENV hEnv;// Manejador de entorno ODBC
    SQLHDBC hDbc;// Manejador de conexión ODBC
    SQLRETURN ret;// Variable para almacenar el resultado de las funciones ODBC

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);    // Establece el entorno de ODBC a la versión 3.0

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos SQL Server con los parámetros proporcionados(de ser nesesario se colocara nombre de servidor, usuario y contraseña)
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"username", SQL_NTS, (SQLWCHAR*)L"password", SQL_NTS);
    // Verificar si la conexión fue exitosa
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        wcout << L"Conectado a la base de datos exitosamente." << endl;// Conexión exitosa, se muestra un mensaje

        // Consulta y mostrar datos de la tabla EMPLEADO
        SQLHSTMT hStmt;// Crear un manejador de consulta
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        // Mostrar encabezado de la tabla EMPLEADO
        wcout << endl << L"Tabla EMPLEADO:" << endl;
        wcout << L"+-------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        wcout << L"| " << left << setw(11) << L"#EMPLEADO"
            << L"| " << left << setw(7) << L"NOMBRE"
            << L"| " << left << setw(16) << L"APELLIDO PATERNO"
            << L"| " << left << setw(16) << L"APELLIDO MATERNO"
            << L"| " << left << setw(11) << L"FECHA.NAC"
            << L"| " << left << setw(13) << L"RFC"
            << L"| " << left << setw(16) << L"#CENTRO DE TRABAJO"
            << L"| " << left << setw(10) << L"No.PUESTO"
            << L"| " << left << setw(8) << L"DESC.DEL PUESTO"
            << L"| " << left << setw(5) << L"DIRECTIVO""| ";
        wcout << L"+-------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

        // Consulta SELECT para EMPLEADO(seleccionar todos los datos de la tabla EMPLEADO)
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM EMPLEADO", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            //Define variables para almacenar los datos de cada columna de la tabla EMPLEADO
            int ID_NUMERO_DE_EMPLEADO;
            SQLWCHAR NOMBRE_EMPLEADO[7];
            SQLWCHAR APELLIDO_PATERNO_EMPLEADO[16];
            SQLWCHAR APELLIDO_MATERNO_EMPLEADO[16];
            SQLWCHAR FECHA_NACIMIENTO_EMPLEADO[11];
            SQLWCHAR RFC[15];
            int ID_CENTRO_DE_TRABAJO;
            SQLWCHAR ID_PUESTO[9];
            SQLWCHAR DESCRIPCION_DEL_PUESTO[9];
            SQLWCHAR DIRECTIVO[2]; // Cambio para mostrar BIT como CHAR

            // Bucle para obtener y mostrar cada fila de la tabla EMPLEADO
            while (SQLFetch(hStmt) == SQL_SUCCESS) {// Obtener datos de cada columna:
                SQLGetData(hStmt, 1, SQL_C_LONG, &ID_NUMERO_DE_EMPLEADO, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, NOMBRE_EMPLEADO, sizeof(NOMBRE_EMPLEADO), NULL);
                SQLGetData(hStmt, 3, SQL_C_WCHAR, APELLIDO_PATERNO_EMPLEADO, sizeof(APELLIDO_PATERNO_EMPLEADO), NULL);
                SQLGetData(hStmt, 4, SQL_C_WCHAR, APELLIDO_MATERNO_EMPLEADO, sizeof(APELLIDO_MATERNO_EMPLEADO), NULL);
                SQLGetData(hStmt, 5, SQL_C_WCHAR, FECHA_NACIMIENTO_EMPLEADO, sizeof(FECHA_NACIMIENTO_EMPLEADO), NULL);
                SQLGetData(hStmt, 6, SQL_C_WCHAR, RFC, sizeof(RFC), NULL);
                SQLGetData(hStmt, 7, SQL_C_LONG, &ID_CENTRO_DE_TRABAJO, 0, NULL);
                SQLGetData(hStmt, 8, SQL_C_WCHAR, ID_PUESTO, sizeof(ID_PUESTO), NULL);
                SQLGetData(hStmt, 9, SQL_C_WCHAR, DESCRIPCION_DEL_PUESTO, sizeof(DESCRIPCION_DEL_PUESTO), NULL);
                SQLGetData(hStmt, 10, SQL_C_WCHAR, DIRECTIVO, sizeof(DIRECTIVO), NULL); // Cambio para mostrar BIT como CHAR
                // Mostrar los datos en formato tabular 
                wcout << L"| " << left << setw(11) << ID_NUMERO_DE_EMPLEADO// 'setw' define el ancho de campo para alinear columnas en la salida de datos.
                    << L"| " << left << setw(7) << NOMBRE_EMPLEADO
                    << L"| " << left << setw(16) << APELLIDO_PATERNO_EMPLEADO
                    << L"| " << left << setw(16) << APELLIDO_MATERNO_EMPLEADO
                    << L"| " << left << setw(11) << FECHA_NACIMIENTO_EMPLEADO
                    << L"| " << left << setw(13) << RFC
                    << L"| " << left << setw(18) << ID_CENTRO_DE_TRABAJO
                    << L"| " << left << setw(10) << ID_PUESTO
                    << L"| " << left << setw(15) << DESCRIPCION_DEL_PUESTO
                    << L"| " << left << setw(9) << (DIRECTIVO[0] == L'1' ? L"1" : L"0") // Mostrar '1' o '0' para Directivo
                    << L"|" << endl;
            }
            // Muestra la línea divisoria al final de la tabla EMPLEADO
            wcout << L"+-------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        }
        else {
            wcout << L"Error en la consulta SELECT para EMPLEADO." << endl;// Se muestra este mensaje, si la conexion es fallida para la tabla EMPLEADO
        }

        // Liberar el manejador de consulta
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Consulta y mostrar datos de la tabla Directivo
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);// Se repite el proceso para la tabla Directivo y el resto de tablas

        // Mostrar encabezado de la tabla Directivo
        wcout << endl << L"Tabla Directivo:" << endl;
        wcout << L"+------------------------------+" << endl;
        wcout << L"| " << left << setw(10) << L"#EMPLEADO"//Es crucial contabilizar los espacios contenidos dentro de los paréntesis para garantizar un alineamiento preciso en todos los encabezados donde se implementen.
            << L"| " << left << setw(15) << L"PREST.COMBUSTIBLE"
            << L"|" << endl;
        wcout << L"+------------------------------+" << endl;

        // Consulta SELECT para Directivo
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Directivo", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Declaracion de las variables para almacenar los datos de la tabla Directivo:
            int ID_Numero_de_Empleado;
            SQLWCHAR Prestacion_de_Combustible[2]; // Cambio para mostrar BIT como CHAR
            // Bucle para obtener y mostrar cada fila de la tabla Directivo:
            while (SQLFetch(hStmt) == SQL_SUCCESS) {// Obtener y mostrar cada fila de la tabla Directivo
                SQLGetData(hStmt, 1, SQL_C_LONG, &ID_Numero_de_Empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, Prestacion_de_Combustible, sizeof(Prestacion_de_Combustible), NULL); // Cambio para mostrar BIT como CHAR
                // Mostrar los datos en formato tabular 
                wcout << L"| " << left << setw(10) << ID_Numero_de_Empleado
                    << L"| " << left << setw(17) << (Prestacion_de_Combustible[0] == L'1' ? L"1" : L"0") // Mostrar '1' o '0' para Prestacion_de_Combustible
                    << L"|" << endl;
            }
            // Muestra la línea divisoria al final de la tabla Directivo
            wcout << L"+------------------------------+" << endl;//Es fundamental contar las líneas divisoras para asegurar un alineado preciso en todos los campos donde se aplican.
        }
        else {
            wcout << L"Error en la consulta SELECT para Directivo." << endl;// Se muestra este mensaje, si la conexion es fallida para la tabla Directivo
        }

        // Liberar el manejador de consulta
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Consulta y mostrar datos de la tabla Centro_de_Trabajo
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);// Se repite el proceso para la tabla Directivo 

        // Mostrar encabezado de la tabla Centro_de_Trabajo
        wcout << endl << L"Tabla Centro de Trabajo:" << endl;
        wcout << L"+-------------------------------------------------------------+" << endl;// 'wcout' imprime caracteres anchos, y 'L' indica literales de caracteres anchos.
        wcout << L"| " << left << setw(13) << L"#CENTRO DE TRABAJO"
            << L"| " << left << setw(29) << L"NOMBRE DEL CENTRO DE TRABAJO"
            << L"| " << left << setw(9) << L"CIUDAD"
            << L"|" << endl;
        wcout << L"+-------------------------------------------------------------+" << endl;

        // Consulta SELECT para Centro_de_Trabajo
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Centro_de_Trabajo", SQL_NTS);// Se repite el proceso para la tabla Centro_de_Trabajo
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Declaracion de las variables para almacenar los datos de la tabla Centro_de_Trabajo :
            int ID_Centro_de_trabajo;
            SQLWCHAR Nombre_del_Centro_de_trabajo[29];
            SQLWCHAR CIUDAD[16];
            // Bucle para obtener y mostrar cada fila de la tabla Centro_de_Trabajo:
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &ID_Centro_de_trabajo, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, Nombre_del_Centro_de_trabajo, sizeof(Nombre_del_Centro_de_trabajo), NULL);
                SQLGetData(hStmt, 3, SQL_C_WCHAR, CIUDAD, sizeof(CIUDAD), NULL);
                // Mostrar los datos en formato tabular 
                wcout << L"| " << left << setw(18) << ID_Centro_de_trabajo
                    << L"| " << left << setw(29) << Nombre_del_Centro_de_trabajo
                    << L"| " << left << setw(9) << CIUDAD
                    << L"|" << endl;
            }
            // Muestra la línea divisoria al final de la tabla Centro_de_Trabajo
            wcout << L"+-------------------------------------------------------------+" << endl;
        }
        else {
            wcout << L"Error en la consulta SELECT para Centro_de_Trabajo." << endl;// Se muestra este mensaje, si la conexion es fallida para la tabla Centro_de_Trabajo
        }

        // Liberar el manejador de consulta
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Consulta y mostrar datos de la tabla Respuesta de si es o no Directivo:
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);// Se repite el proceso para la tabla Respuesta de si es o no Directivo(se repite el proceso para consulta combinada):

        // Mostrar encabezado de la tabla Respuesta de si es o no Directivo
        wcout << endl << L"Tabla Respuesta de si es o no Directivo:" << endl;
        wcout << L"+-------------------------------------------------------------------------------------------------------------+" << endl;
        wcout << L"| " << left << setw(9) << L"#EMPLEADO"
            << L"| " << left << setw(20) << L"NOMBRE COMPLETO"
            << L"| " << left << setw(11) << L"FECHA.NAC"
            << L"| " << left << setw(11) << L"RFC"
            << L"| " << left << setw(25) << L"CENTRO DE TRABAJO"
            << L"| " << left << setw(8) << L"DESC.PUESTO"
            << L"| " << left << setw(9) << L"DIRECTIVO"
            << L"|" << endl;
        wcout << L"+-------------------------------------------------------------------------------------------------------------+" << endl;

        // Consulta SELECT para verificar si un empleado es directivo y se concatena los atributos NOMBRE, AP.PATERNO Y MATERNO EN UNA SOLA COLUMNA LLAMDADA NOMBRE COMPLETO Y SE ELIMINA LA COLUMNA PREST.COMBUSTIBLE Y ID PUESTO (Se obtiene información de las tablas: Empleados, Directivo, Centro de trabajo)
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT E.ID_NUMERO_DE_EMPLEADO, CONCAT(E.NOMBRE_EMPLEADO, ' ', E.APELLIDO_PATERNO_EMPLEADO, ' ', E.APELLIDO_MATERNO_EMPLEADO) AS Nombre_completo, E.FECHA_NACIMIENTO_EMPLEADO, E.RFC, C.Nombre_del_Centro_de_trabajo, E.DESCRIPCION_DEL_PUESTO, CASE WHEN D.ID_Numero_de_Empleado IS NOT NULL THEN 'Si' ELSE 'No' END AS ES_DIRECTIVO, COALESCE(D.Prestacion_de_Combustible, 0) AS Prestacion_de_Combustible FROM EMPLEADO E LEFT JOIN Directivo D ON E.ID_NUMERO_DE_EMPLEADO = D.ID_Numero_de_Empleado JOIN Centro_de_Trabajo C ON E.ID_CENTRO_DE_TRABAJO = C.ID_Centro_de_trabajo;", SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            // Declaracion de las variables para almacenar los datos de la tabla Respuesta de si es o no Directivo(se repite el proceso para consulta combinada):
            int ID_NUMERO_DE_EMPLEADO;
            SQLWCHAR Nombre_completo[150]; 
            SQLWCHAR FECHA_NACIMIENTO_EMPLEADO[11];
            SQLWCHAR RFC[15];
            SQLWCHAR Nombre_del_Centro_de_trabajo[100];
            SQLWCHAR DESCRIPCION_DEL_PUESTO[100];
            SQLWCHAR ES_DIRECTIVO[3];

            // Bucle para obtener y mostrar la convinacion cada de cada fila de las diferentes tablas para dar como resultado la tabla Respuesta de si es o no Directivo
            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &ID_NUMERO_DE_EMPLEADO, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, Nombre_completo, sizeof(Nombre_completo), NULL); 
                SQLGetData(hStmt, 3, SQL_C_WCHAR, FECHA_NACIMIENTO_EMPLEADO, sizeof(FECHA_NACIMIENTO_EMPLEADO), NULL);
                SQLGetData(hStmt, 4, SQL_C_WCHAR, RFC, sizeof(RFC), NULL);
                SQLGetData(hStmt, 5, SQL_C_WCHAR, Nombre_del_Centro_de_trabajo, sizeof(Nombre_del_Centro_de_trabajo), NULL);
                SQLGetData(hStmt, 6, SQL_C_WCHAR, DESCRIPCION_DEL_PUESTO, sizeof(DESCRIPCION_DEL_PUESTO), NULL);
                SQLGetData(hStmt, 7, SQL_C_WCHAR, ES_DIRECTIVO, sizeof(ES_DIRECTIVO), NULL);

                // Mostrar los datos en formato tabular 
                wcout << L"| " << left << setw(9) << ID_NUMERO_DE_EMPLEADO
                    << L"| " << left << setw(20) << Nombre_completo
                    << L"| " << left << setw(11) << FECHA_NACIMIENTO_EMPLEADO
                    << L"| " << left << setw(10) << RFC
                    << L"| " << left << setw(25) << Nombre_del_Centro_de_trabajo
                    << L"| " << left << setw(11) << DESCRIPCION_DEL_PUESTO
                    << L"| " << left << setw(9) << ES_DIRECTIVO 
                    << L"|" << endl;
            }

            // Muestra la línea divisoria al final de la tabla Respuesta de si es o no Directivo
            wcout << L"+-------------------------------------------------------------------------------------------------------------+" << endl;
        }
        else {
            wcout << L"Error en la consulta SELECT para verificar si es Directivo." << endl; //Se muestra este mensaje, si la conexion es fallida para la tabla Respuesta de si es o no Directivo
        }

        // Liberar el manejador de consulta
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        // Desconectarse de la base de datos
        ret = SQLDisconnect(hDbc);
    }
    else {
        wcout << L"No se pudo conectar a la base de datos." << endl;//Se muestra este mensaje, si la conexion es fallida con a la base de datos SQL Server
    }

    // Liberar el manejador de conexión y el manejador de entorno
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;// Finaliza el programa
}
