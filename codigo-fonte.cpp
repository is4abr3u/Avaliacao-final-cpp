#include <iostream>
#include <string>
#include <iomanip>

const int     maximoalunos = 2;
const int     numprovas = 2;
const double  mediamin  = 6.0;

std::string nomes[maximoalunos];
double       notas[maximoalunos][numprovas];
int          total = 0;

double calcularMedia(int idx) {
    double soma = 0;
    for (int j = 0; j < numprovas; j++) soma += notas[idx][j];
    return soma / numprovas;
}

std::string calcularSituacao(double media) {
    return (media >= mediamin) ? "APROVADO" : "REPROVADO";
}

double lerNota(const std::string& label) {
    double nota;
    while (true) {
        std::cout << "  " << label << " (0 a 10): ";
        std::cin >> nota;
        if (std::cin.fail() || nota < 0.0 || nota > 10.0) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cerr << "  [ERRO] Nota invalida.\n";
        } else {
            break;
        }
    }
    return nota;
}

void cadastrarAluno() {
    std::cout << "\n=== A. CADASTRAR ALUNO ===\n";

    if (total >= maximoalunos) {
        std::cerr << "[ERRO] Sistema cheio.\n";
        return;
    }

    std::cin.ignore();
    std::cout << "  Nome: ";
    std::getline(std::cin, nomes[total]);

    if (nomes[total].empty()) {
        std::cerr << "[ERRO] Nome nao pode ser vazio.\n";
        return;
    }

    notas[total][0] = lerNota("P1");
    notas[total][1] = lerNota("P2");

    double media = calcularMedia(total);
    std::cout << "\n  Media: " << std::fixed << std::setprecision(1) << media
              << " -> " << calcularSituacao(media) << "\n";
    std::cout << "[OK] Aluno \"" << nomes[total] << "\" cadastrado.\n";
    total++;
}

void exibirTodos() {
    std::cout << "\n=== B. INFORMACOES DOS ALUNOS ===\n";

    if (total == 0) {
        std::cout << "  (nenhum aluno cadastrado)\n";
        return;
    }

    std::cout << "---------------------------------------------------\n";
    std::cout << std::left
              << std::setw(20) << "Nome"
              << std::setw(8)  << "P1"
              << std::setw(8)  << "P2"
              << std::setw(8)  << "Media"
              << "Situacao\n";
    std::cout << "---------------------------------------------------\n";

    for (int i = 0; i < total; i++) {
        double media = calcularMedia(i);
        std::cout << std::left
                  << std::setw(20) << nomes[i]
                  << std::setw(8)  << std::fixed << std::setprecision(1) << notas[i][0]
                  << std::setw(8)  << notas[i][1]
                  << std::setw(8)  << media
                  << calcularSituacao(media) << "\n";
    }

    std::cout << "---------------------------------------------------\n";
    std::cout << "Total: " << total << " aluno(s)\n";
}

void pesquisarAluno() {
    std::cout << "\n=== C. PESQUISAR NOTAS DE ALUNO ===\n";

    if (total == 0) {
        std::cout << "  (nenhum aluno cadastrado)\n";
        return;
    }

    std::cin.ignore();
    std::string busca;
    std::cout << "  Nome: ";
    std::getline(std::cin, busca);

    for (int i = 0; i < total; i++) {
        if (nomes[i] == busca) {
            double media = calcularMedia(i);
            std::cout << "\n---------------------------------------------------\n";
            std::cout << "  Aluno  : " << nomes[i] << "\n";
            std::cout << "  P1     : " << std::fixed << std::setprecision(1) << notas[i][0] << "\n";
            std::cout << "  P2     : " << notas[i][1] << "\n";
            std::cout << "  Media  : " << media << "\n";
            std::cout << "  Status : " << calcularSituacao(media) << "\n";
            std::cout << "---------------------------------------------------\n";
            return;
        }
    }

    std::cerr << "[ERRO] Aluno \"" << busca << "\" nao encontrado.\n";
}

void calcularMediaGeral() {
    std::cout << "\n=== D. MEDIA GERAL DE TODOS OS ALUNOS ===\n";

    if (total == 0) {
        std::cout << "  (nenhum aluno cadastrado)\n";
        return;
    }

    double somaGeral = 0;
    for (int i = 0; i < total; i++) somaGeral += calcularMedia(i);
    double mediaGeral = somaGeral / total;

    std::cout << "  Alunos avaliados : " << total << "\n";
    std::cout << "  Media geral      : " << std::fixed << std::setprecision(1) << mediaGeral << "\n";
}

void exibirMenu() {
    std::cout << "\n===================================\n";
    std::cout << "       SISTEMA DE PROVAS\n";
    std::cout << "===================================\n";
    std::cout << "  A - Cadastrar aluno e notas\n";
    std::cout << "  B - Exibir informacoes\n";
    std::cout << "  C - Pesquisar notas de aluno\n";
    std::cout << "  D - Media geral de todos\n";
    std::cout << "  S - Sair\n";
    std::cout << "-----------------------------------\n";
    std::cout << "  Opcao: ";
}

int main() {
    char opcao;

    do {
        exibirMenu();
        std::cin >> opcao;
        opcao = toupper(opcao);

        switch (opcao) {
            case 'A': cadastrarAluno();   break;
            case 'B': exibirTodos();      break;
            case 'C': pesquisarAluno();   break;
            case 'D': calcularMediaGeral(); break;
            case 'S': std::cout << "sistema encerrado\n"; break;
            default:  std::cout << "Opcao invalida\n";
        }

    } while (opcao != 'S');

    return 0;
}


