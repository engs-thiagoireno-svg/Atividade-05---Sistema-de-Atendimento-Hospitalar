#include <iostream>
#include <string>
using namespace std;

// Três estruturas
struct No {
    string nome;
    int    urgencia;   // 1 = baixa, 2 = media, 3 = alta 
    No*    prox;
    No(const string& n, int u = 0) : nome(n), urgencia(u), prox(nullptr) {}
};


    // R1 · Fila de pacientes (FIFO): Entra por trás, sai pela frente
struct FilaPacientes {
    No* frente = nullptr; 
    No* tras   = nullptr;

    // Insere o paciente no final da fila
    void enqueue(const string& nome, int urgencia) {
        No* novo = new No(nome, urgencia);
        if (isEmpty()) {
            frente = tras = novo;
        } else {
            tras->prox = novo;
            tras = novo;
        }
    }

    // Remove o paciente da frente e devolve o nome
    string dequeue() {
        if (isEmpty()) return "";

        No* temp = frente;
        string nome = temp->nome;
        frente = frente->prox;
        if (frente == nullptr) tras = nullptr;  // fila ficou vazia
        delete temp;
        return nome;
    }

    // Mostra quem está na frente sem remover
    string frente_peek() const {
        if (isEmpty()) return "";
        return frente->nome;
    }

    bool isEmpty() const { return frente == nullptr; }

    // Conta os nós da fila
    int tamanho() const {
        int cont = 0;
        for (No* p = frente; p != nullptr; p = p->prox) cont++;
        return cont;
    }

    ~FilaPacientes() {
        while (!isEmpty()) dequeue();
    }
};


// R2 · Histórico de atendimentos 
struct PilhaHistorico {
    No* topo = nullptr;

    // Empilha um atendimento concluído
    void push(const string& nome) {
        No* novo = new No(nome);
        novo->prox = topo;
        topo = novo;
    }

    // Desempilha e devolve o último atendimento
    string pop() {
        if (isEmpty()) return "";

        No* temp = topo;
        string nome = temp->nome;
        topo = topo->prox;
        delete temp;
        return nome;
    }

    // Mostra o último atendimento sem remover
    string peek() const {
        if (isEmpty()) return "";
        return topo->nome;
    }

    bool isEmpty() const { return topo == nullptr; }

    ~PilhaHistorico() {
        while (!isEmpty()) pop();
    }
};

    // R3 · Lista de médicos disponíveis 
// O médico sai da lista ao ser chamado e volta ao final depois de atender
struct ListaMedicos {
    No* head = nullptr;

    // Adiciona um médico no final da lista
    void adicionarMedico(const string& nome) {
        No* novo = new No(nome);
        if (head == nullptr) {
            head = novo;
            return;
        }
        No* p = head;
        while (p->prox != nullptr) p = p->prox;
        p->prox = novo;
    }

    // Remove o primeiro médico da lista e devolve o nome
    string chamarMedico() {
        if (head == nullptr) return "";

        No* temp = head;
        string nome = temp->nome;
        head = head->prox;
        delete temp;
        return nome;
    }

    // Imprime todos os médicos disponíveis
    void percorrer(const string& prefixo = "") const {
        if (!prefixo.empty()) cout << prefixo << ": ";
        if (head == nullptr) {
            cout << "(lista vazia)\n";
            return;
        }
        for (No* p = head; p != nullptr; p = p->prox) {
            cout << p->nome;
            if (p->prox != nullptr) cout << " → ";
        }
        cout << "\n";
    }

    bool temMedico() const { return head != nullptr; }

    ~ListaMedicos() {
        while (head) {
            No* t = head;
            head = head->prox;
            delete t;
        }
    }
};

// R4 · Relatório: imprime do topo à base sem destruir o histórico

void imprimirHistorico(PilhaHistorico& hist) {
    cout << "\nRelatório de atendimentos:\n";
    if (hist.isEmpty()) {
        cout << "(nenhum atendimento registrado)\n";
        return;
    }

    // Pilha auxiliar guarda os itens para devolve depois
    PilhaHistorico aux;
    int n = 1;

    while (!hist.isEmpty()) {
        string item = hist.pop();
        cout << "  " << n++ << ". " << item << "\n";
        aux.push(item);
    }

    while (!aux.isEmpty()) {
        hist.push(aux.pop());
    }
}

// Coloca o paciente na fila e mostra a chegada na tela
void chegar(FilaPacientes& fila, const string& nome, int urgencia) {
    fila.enqueue(nome, urgencia);
    cout << "  " << fila.tamanho() << ". " << nome << "\n";
}

// Programa principal: integra as estruturas
int main() {
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║" << string(8, ' ') << "SISTEMA DE ATENDIMENTO" << string(8, ' ') << "║\n";
    cout << "║" << string(9, ' ') << "Hospital Campo Real" << string(10, ' ') << "║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    FilaPacientes  fila;
    PilhaHistorico historico;
    ListaMedicos   medicos;

    // Médicos de plantão (R3)
    medicos.adicionarMedico("Dra. Ana Lima");
    medicos.adicionarMedico("Dr. Bruno Costa");
    medicos.adicionarMedico("Dra. Carla Ramos");
    medicos.percorrer("Médicos disponíveis");

    // Pacientes chegam na fila (R1)
    cout << "\nPacientes chegando:\n";
    chegar(fila, "Eduardo com urgencia nivel 3", 3);
    chegar(fila, "Fernanda com urgencia nivel 1", 1);
    chegar(fila, "Gabriel com urgencia nivel 2", 2);
    chegar(fila, "Helena com urgencia nivel 1", 1);

    cout << "\nPróximo a ser atendido: " << fila.frente_peek() << "\n";
    cout << "Total na fila: " << fila.tamanho() << "\n";

    // Atendimentos: cada médico atende e volta ao final da lista
    cout << "\nSimulação de atendimentos:\n";
    int atend = 1;
    while (!fila.isEmpty() && medicos.temMedico()) {
        string paciente = fila.dequeue();
        string medico   = medicos.chamarMedico();

        cout << "  " << atend++ << ". " << medico
             << " atende " << paciente << "\n";

        historico.push(medico + " → " + paciente);  // R2
        medicos.adicionarMedico(medico);            // médico volta à lista
    }

    // Último atendimento 
    cout << "\nÚltimo atendimento registrado: " << historico.peek() << "\n";

    // Relatório final (R4)
    imprimirHistorico(historico);

    return 0;
}