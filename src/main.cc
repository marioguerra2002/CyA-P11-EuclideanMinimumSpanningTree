#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "point_set.h" // Asegúrate de que el archivo esté disponible en el directorio correcto

// Usar el espacio de nombres CyA
void write_dot(const std::string &filename, const CyA::point_set &ps) {
    std::ofstream dot_file(filename);
    if (!dot_file) {
        std::cerr << "Error al abrir el archivo para escribir: " << filename << std::endl;
        return;
    }

    // Inicio del archivo DOT
    dot_file << "graph {\n\n";

    // Escribir nodos con sus posiciones
    const auto &points = ps.get_points();
    for (size_t i = 0; i < points.size(); ++i) {
        dot_file << "  " << i << " [pos = \"" << points[i].first << "," << points[i].second << "!\"];\n";
    }
    dot_file << "\n";

    // Escribir aristas del EMST (sin duplicar)
    const auto &tree = ps.get_tree();
    std::set<std::pair<int, int>> unique_edges; // Para guardar aristas únicas

    for (const auto &arc : tree) {
        int u = std::find(points.begin(), points.end(), arc.first) - points.begin();
        int v = std::find(points.begin(), points.end(), arc.second) - points.begin();

        if (u < points.size() && v < points.size()) { // Validar índices válidos
            // Ordenar los nodos para evitar duplicados
            if (u > v) std::swap(u, v);

            if (unique_edges.insert({u, v}).second) { // Solo agregar si es nuevo
                dot_file << "  " << u << " -- " << v << ";\n";
            }
        }
    }

    // Fin del archivo DOT
    dot_file << "}" << std::endl;

    dot_file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3) { // Cambiar para requerir archivo de entrada y salida
        std::cerr << "Uso: " << argv[0] << " <archivo_de_puntos> <archivo_de_salida.dot> [-d]\n";
        return 1;
    }

    // Leer puntos desde el archivo de entrada
    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error al abrir el archivo de puntos: " << argv[1] << std::endl;
        return 1;
    }

    CyA::point_vector points;
    int n_points;
    input >> n_points; // Leer el número de puntos

    while (n_points-- > 0) {
        CyA::point p;
        input >> p.first >> p.second;
        points.push_back(p);
    }
    input.close();

    if (points.empty()) {
        std::cerr << "El archivo de puntos está vacío o no contiene datos válidos." << std::endl;
        return 1;
    }

    CyA::point_set ps(points); // Corregir declaración

    // Calcular el EMST
    ps.EMST();

    // Obtener el nombre del archivo de salida y asegurarnos de que tenga la extensión .dot o .txt
    std::string output_dot = argv[2];
    // si no se le pone la opcion -d, se mantiene el txt como extension del archivo
    if (argc == 4 && std::string(argv[3]) == "-d") {
        if (output_dot.find(".txt") != std::string::npos) {
            output_dot.replace(output_dot.find(".txt"), 4, ".dot"); // Reemplazar .txt por .dot
        }
        write_dot(output_dot, ps); // Genera el archivo DOT
        std::cout << "Archivo DOT generado: " << output_dot << std::endl;
    } else { // cuando no se pone la opcion -d
        if (output_dot.find(".txt") == std::string::npos) {
            output_dot += ".txt"; // Si no tiene la extensión .txt, agregarla
        }
        std::ofstream output(output_dot);
        if (!output) {
            std::cerr << "Error al abrir el archivo de salida: " << output_dot << std::endl;
            return 1;
        }

        output << ps.get_cost() << std::endl; // Escribir el costo total del EMST
        output.close();

    }

    // if (output_dot.find(".dot") == std::string::npos) {
    //     output_dot += ".dot"; // Si no tiene la extensión .dot, agregarla
    // }

    // // Escribir el archivo DOT si se pasa la opción -d 
    // if (argc == 4 && std::string(argv[3]) == "-d") {
    //     write_dot(output_dot, ps); // Genera el archivo DOT
    //     std::cout << "Archivo DOT generado: " << output_dot << std::endl;
    // } 

    std::cout << "Costo total del EMST: " << ps.get_cost() << std::endl;

    return 0;
}
