#include <iostream>
#include <string>
using namespace std;

// ESTRUCTURA DE PACIENTE
struct Paciente {
    string nombre;
    int edad;
    string dni;
    Paciente* siguiente;

    Paciente(string n, int e, string d) {
        nombre = n;
        edad = e;
        dni = d;
        siguiente = NULL;
    }
};


// ESTRUCTURA DE ACCION (para pila)

struct Accion {
    string descripcion;
    Accion* siguiente;

    Accion(string texto) {
        descripcion = texto;
        siguiente = NULL;
    }
};


// FUNCIONES DE LA COLA (PACIENTES EN ESPERA)
void encolar(Paciente*& frente, Paciente*& fin, string nombre, int edad, string dni) {
    Paciente* nuevo = new Paciente(nombre, edad, dni);
    if (frente == NULL) {
        frente = fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }
    cout << "? Paciente " << nombre << " agregado a la cola de espera.\n";
}

Paciente* desencolar(Paciente*& frente, Paciente*& fin) {
    if (frente == NULL) {
        cout << "?? No hay pacientes en espera.\n";
        return NULL;
    } else {
        Paciente* atendido = frente;
        frente = frente->siguiente;
        if (frente == NULL) fin = NULL;
        atendido->siguiente = NULL; // aislamos el nodo
        cout << "????? Paciente atendido: " << atendido->nombre << endl;
        return atendido;
    }
}

void mostrarCola(Paciente* frente) {
    if (frente == NULL) {
        cout << "?? No hay pacientes en espera.\n";
        return;
    }
    cout << "\n?? Pacientes en espera:\n";
    Paciente* temp = frente;
    while (temp != NULL) {
        cout << " - " << temp->nombre << " (" << temp->edad << " anios, DNI: " << temp->dni << ")\n";
        temp = temp->siguiente;
    }
}

// FUNCIONES DE LA LISTA (PACIENTES ATENDIDOS)
void agregarAtendido(Paciente*& lista, Paciente* paciente) {
    if (lista == NULL) {
        lista = paciente;
    } else {
        Paciente* temp = lista;
        while (temp->siguiente != NULL)
            temp = temp->siguiente;
        temp->siguiente = paciente;
    }
    cout << "??? Paciente " << paciente->nombre << " agregado al historial de atendidos.\n";
}

void mostrarLista(Paciente* lista) {
    if (lista == NULL) {
        cout << "?? No hay pacientes atendidos aún.\n";
        return;
    }
    cout << "\n?? Pacientes atendidos:\n";
    Paciente* temp = lista;
    while (temp != NULL) {
        cout << " - " << temp->nombre << " (" << temp->edad << " anios, DNI: " << temp->dni << ")\n";
        temp = temp->siguiente;
    }
}

// FUNCIONES DE LA PILA (HISTORIAL DE ACCIONES)

void pushAccion(Accion*& tope, string texto) {
    Accion* nueva = new Accion(texto);
    nueva->siguiente = tope;
    tope = nueva;
}

void mostrarPila(Accion* tope) {
    if (tope == NULL) {
        cout << "?? No hay acciones registradas.\n";
        return;
    }
    cout << "\n?? Historial de acciones (ultima primero):\n";
    Accion* temp = tope;
    while (temp != NULL) {
        cout << " - " << temp->descripcion << endl;
        temp = temp->siguiente;
    }
}

// FUNCIÓN PRINCIPAL (MENÚ)
int main() {
    Paciente* frente = NULL; // frente de la cola
    Paciente* fin = NULL;    // fin de la cola
    Paciente* listaAtendidos = NULL; // lista de pacientes atendidos
    Accion* historial = NULL; 

    int opcion;
    do {
        cout << "\n====== CLINICA DE PACIENTES ======\n";
        cout << "1. Registrar paciente (agregar a la cola)\n";
        cout << "2. Atender paciente (mover de cola a lista)\n";
        cout << "3. Mostrar pacientes en espera\n";
        cout << "4. Mostrar pacientes atendidos\n";
        cout << "5. Ver historial de acciones\n";
        cout << "6. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombre, dni;
                int edad;
                cout << "Nombre del paciente: ";
                getline(cin, nombre);
                cout << "Edad: ";
                cin >> edad;
                cin.ignore();
                cout << "DNI: ";
                getline(cin, dni);
                encolar(frente, fin, nombre, edad, dni);
                pushAccion(historial, "Se registro al paciente " + nombre);
                break;
            }

            case 2: {
                Paciente* atendido = desencolar(frente, fin);
                if (atendido != NULL) {
                    agregarAtendido(listaAtendidos, atendido);
                    pushAccion(historial, "Se atendio al paciente " + atendido->nombre);
                }
                break;
            }

            case 3:
                mostrarCola(frente);
                break;

            case 4:
                mostrarLista(listaAtendidos);
                break;

            case 5:
                mostrarPila(historial);
                break;

            case 6:
                cout << "?? Saliendo del sistema de clinica...\n";
                break;

            default:
                cout << "? Opción invalida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}

