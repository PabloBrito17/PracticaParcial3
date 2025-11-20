#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Estructura del jugador
struct Player {
    int id;
    string nombre;
    int nivel;
    string clase;
    int poder;

    // Constructor por defecto (NECESARIO)
    Player()
        : id(0), nombre(""), nivel(0), clase(""), poder(0) {}

    // Constructor normal
    Player(int i, string n, int niv, string c, int p) 
        : id(i), nombre(n), nivel(niv), clase(c), poder(p) {}

    // Operador < para ordenar por id en el set
    bool operator<(const Player& other) const {
        return id < other.id;
    }

    // Función para mostrar datos
    void mostrar() const {
        cout << "ID: " << id << " | " << nombre << " | Nivel: " << nivel 
             << " | Clase: " << clase << " | Poder: " << poder << endl;
    }
};

// Comparador para ordenar por poder (descendente)
bool compararPorPoder(const Player& a, const Player& b) {
    return a.poder > b.poder;
}

int main() {
    // 1. Set ordenado por id
    set<Player> jugadores;

    // Agregar jugadores de ejemplo
    jugadores.insert(Player(101, "Aragorn", 45, "Guerrero", 850));
    jugadores.insert(Player(102, "Gandalf", 80, "Mago", 950));
    jugadores.insert(Player(103, "Legolas", 60, "Arquero", 780));
    jugadores.insert(Player(104, "Merlin", 75, "Mago", 920));
    jugadores.insert(Player(105, "Conan", 50, "Guerrero", 800));
    jugadores.insert(Player(106, "Robin", 55, "Arquero", 720));
    jugadores.insert(Player(107, "Arthas", 70, "Guerrero", 890));
    jugadores.insert(Player(108, "Jaina", 65, "Mago", 870));

    cout << "=== SISTEMA DE GESTION DE JUGADORES RPG ===" << endl << endl;

    // Mostrar todos los jugadores
    cout << "1. JUGADORES REGISTRADOS (ordenados por ID):" << endl;
    for (const auto& j : jugadores) {
        j.mostrar();
    }
    cout << endl;

    // 2. Map que clasifica jugadores por clase
    map<string, set<int>> jugadoresPorClase;

    for (const auto& j : jugadores) {
        jugadoresPorClase[j.clase].insert(j.id);
    }

    cout << "2. JUGADORES POR CLASE:" << endl;
    for (const auto& par : jugadoresPorClase) {
        cout << par.first << ": ";
        for (int id : par.second) {
            cout << id << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 3. Unordered_map para acceso rápido por ID
    unordered_map<int, Player> accesoRapido;

    for (const auto& j : jugadores) {
        accesoRapido[j.id] = j;
    }

    cout << "3. ACCESO RAPIDO - Buscar jugador con ID 104:" << endl;
    if (accesoRapido.find(104) != accesoRapido.end()) {
        accesoRapido[104].mostrar();
    }
    cout << endl;

    // 4. Vector con todos los niveles para ordenar y calcular estadísticas
    vector<int> niveles;

    for (const auto& j : jugadores) {
        niveles.push_back(j.nivel);
    }

    sort(niveles.begin(), niveles.end());

    cout << "4. NIVELES ORDENADOS:" << endl;
    for (int n : niveles) {
        cout << n << " ";
    }
    cout << endl;

    // Calcular estadísticas
    int suma = 0;
    for (int n : niveles) {
        suma += n;
    }
    double promedio = static_cast<double>(suma) / niveles.size();

    cout << "Nivel minimo: " << niveles.front() << endl;
    cout << "Nivel maximo: " << niveles.back() << endl;
    cout << "Nivel promedio: " << promedio << endl;
    cout << endl;

    // 5. Buscar si un nivel específico existe usando binary_search
    int nivelBuscado = 60;
    bool encontrado = binary_search(niveles.begin(), niveles.end(), nivelBuscado);

    cout << "5. BUSQUEDA BINARIA - Nivel " << nivelBuscado << ": ";
    if (encontrado) {
        cout << "ENCONTRADO" << endl;
    } else {
        cout << "NO ENCONTRADO" << endl;
    }
    cout << endl;

    // 6. Filtrar jugadores con poder mayor a cierto valor
    int poderMinimo = 850;
    cout << "6. JUGADORES CON PODER > " << poderMinimo << ":" << endl;

    for (const auto& j : jugadores) {
        if (j.poder > poderMinimo) {
            j.mostrar();
        }
    }
    cout << endl;

    // 7. Top 3 jugadores más fuertes
    vector<Player> ranking;
    for (const auto& j : jugadores) {
        ranking.push_back(j);
    }

    sort(ranking.begin(), ranking.end(), compararPorPoder);

    cout << "7. TOP 3 JUGADORES MAS FUERTES:" << endl;
    for (int i = 0; i < 3 && i < ranking.size(); i++) {
        cout << "Posicion " << (i + 1) << ": ";
        ranking[i].mostrar();
    }

    return 0;
}