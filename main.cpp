#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define TAM 30

using namespace std;

void pausa();
string conversor(string);
int prioridad(char);
bool esOperando(char);
void limpiaBuffer (void);

class Lista {

    private:

        char datos[TAM];
        int ult;

    public:

        Lista(){ult = -1;};
        bool inserta(char, int);
        bool agrega(char);
        int busca(char)const;
        bool elimina(int);
        bool vacia()const;
        bool llena()const;
        int muestra();
        void ultMenos();
        char ultimo()const;

};

bool Lista::vacia()const {
    if (ult == -1)
        return true;
    return false;
}

bool Lista::llena()const {
    if (ult == TAM - 1)
        return true;
    return false;
}

bool Lista::agrega(char datosAux) {
    if (llena()) {
        cout << "Error de insercion...";
        return false;
    }
    else {
        ult++;
        datos[ult] = datosAux;
        return true;
    }
}

int Lista::busca(char buscado)const {
    if (vacia()) {
        cout << "Error, no hay datos que buscar...";
        pausa();
        return -1;
    }
    else{
        int indice = -1;
        for (int i = 0; i < ult; i++) {
            if (buscado == datos[i]){
                    indice = i; break;
            }
        }
        return indice;
    }
}

bool Lista::elimina(int indiceAux) {
    if (vacia() || (indiceAux < 0 || indiceAux > ult)) {
        cout << "Error, no hay datos que borrar o indice equivocado...";
        pausa();
        return false;
    }
    else {
        int i = indiceAux;

        while (i < ult) {
            datos[i] = datos[i + 1];
            i++;
        }

        ult--;
        return true;
    }
}

int Lista::muestra() {
    if (vacia()) {
        cout << "Error, no hay datos que mostrar..." <<endl;
        pausa();
        return false;
    }
    else {
        for (int i = 0; i <= ult; i++) {
            cout << i + 1 << ")._ ";
            cout << datos[i] <<endl;
        }
        pausa();
        return true;
    }
}

bool Lista::inserta(char charAux, int indice){
    if (vacia() || (indice < 0 || indice > ult)){
        cout << endl << "No hay posicion en donde guardarlo o no existe..." <<endl;
        pausa();
        return false;
    }
    else {
        datos[indice] = charAux;
        cout << "Datos Guardados correctamente..." <<endl;
        pausa();
        return true;
    }
}

void Lista::ultMenos() {
    ult--;
}

char Lista::ultimo()const{
    if(vacia()){
       return -1;
    }
    return datos[ult];
}

class Pila : public Lista {


    public:

        void push(char);
        void pop();
        char top();

};

void Pila::push(char elemento) {
    if (llena()) {
        cout << "Pila llena...";
        pausa();
    }
    else {
        agrega(elemento);
    }
}

void Pila::pop () {
    if (vacia()){
        std::cout << std::endl << "la pila esta vacia...";
        pausa();
    }
    else {
        ultMenos();
    }
}

char Pila::top () {
    if (vacia()) {
        std::cout << "Error de exepcion...";
        pausa();
        return -1;
    }
    else {
        return ultimo();
    }
}

void limpiaBuffer (void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void pausa() {
    cin.clear(); cin.sync(); cin.ignore();
}

int prioridad(char operador) {
    if (operador == '^')
        return 3;
    else if (operador == '*' || operador == '/')
        return 2;
    else if (operador == '+' || operador == '-')
        return 1;
    else
        return 0;
}

bool esOperando(char caracter) {
    if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^')
        return false;
    else {
        return true;
    }
}

string conversor(string infija) {

    Pila pila;
    string cadenaAux = "";

    for (int i = 0; i < (int)infija.length(); i++) {

        char ficha = infija[i];


        if (esOperando(ficha)){
            cadenaAux += ficha;
        }


        else if (ficha == '(') {
            pila.push(ficha);
        }


        else if (ficha == ')') {
            while (!pila.vacia() && pila.top() != '(') {
                cadenaAux += pila.top();
                pila.pop();
            }
            pila.pop();
        }


        else if (!esOperando(ficha)) {
            while (!pila.vacia() && pila.top() != '(' && prioridad(pila.top()) >= prioridad(ficha)) {
                cadenaAux += pila.top();
                pila.pop();
            }
            pila.push(ficha);
        }

    }

    ///Si la cadena ya se acabo.
    while (!pila.vacia()) {
        cadenaAux += pila.top();
        pila.pop();
    }

    return cadenaAux;

}

int main () {

    short opc;
    do {

        system(CLEAR);
        cout << "CONVERSOR DE NOTACION" <<endl<<endl;
        cout << "Que quieres hacer?" <<endl;
        cout << "1) Convertir de notacion infija a posfija." <<endl;
        cout << "0) Salir." <<endl;
        cin >> opc;

        switch (opc) {

            case 0: break;

            case 1:{

                string notacionInfija, notacionPosfija;

                system("cls");
                cout << "CONVERSOR DE NOTACION" <<endl<<endl;
                cout << "ingresa la operacion a convertir:  ";
                limpiaBuffer();
                getline(cin, notacionInfija);

                notacionPosfija = conversor(notacionInfija);

                cout << "La notacion posfija de " << notacionInfija << " es de: " << notacionPosfija << "." <<endl<<endl;
                cout << endl << "Presiona \"Enter\" para continuar...";
                pausa();

            }break;

            default:

                cout << endl << "Opcion equivocada, intentalo de nuevo...";
                pausa();

            break;

        }

    } while (opc != 0);

    return 0;

}
