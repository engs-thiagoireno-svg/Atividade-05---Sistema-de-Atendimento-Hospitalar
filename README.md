# Sistema de Atendimento Hospitalar

Triagem digital do Hospital Campo Real, feita em C++ com estruturas de dados lineares construídas manualmente
sem STL de estruturas.

**Disciplina:** Programação e Sistemas Computacionais II  
**Professor:** Giovane Galvão  
**Instituição:** Campo Real · Engenharia de Software

## Estruturas implementadas

| Requisito | Estrutura | Função no sistema |
|-----------|-----------|-------------------|
| R1 | Fila (FIFO) | Pacientes são atendidos na ordem de chegada |
| R2 | Pilha (LIFO) | Histórico dos atendimentos concluídos |
| R3 | Lista encadeada | Médicos de plantão, que voltam ao final da lista após atender |
| R4 | Relatório | Imprime o histórico do topo à base sem destruir os dados (pilha auxiliar) |

Todas usam a struct `No` fornecida no template, e cada `new` possui seu `delete` correspondente sem memory leak.

## Como compilar e executar

Compilar:

```bash
g++ -std=c++17 -Wall -o atendimento atendimento_template.cpp
```

Executar:

```bash
# Linux / macOS
./atendimento

# Windows (PowerShell)
chcp 65001
.\atendimento.exe
```

> No Windows, o `chcp 65001` garante que acentos e a moldura do título apareçam corretamente.

## Exemplo de saída

```
╔══════════════════════════════════════╗
║        SISTEMA DE ATENDIMENTO        ║
║         Hospital Campo Real          ║
╚══════════════════════════════════════╝

Médicos disponíveis: Dra. Ana Lima → Dr. Bruno Costa → Dra. Carla Ramos

Pacientes chegando:
  1. Eduardo com urgencia nivel 3
  2. Fernanda com urgencia nivel 1
  3. Gabriel com urgencia nivel 2
  4. Helena com urgencia nivel 1

Próximo a ser atendido: Eduardo com urgencia nivel 3
Total na fila: 4

Simulação de atendimentos:
  1. Dra. Ana Lima atende Eduardo com urgencia nivel 3
  2. Dr. Bruno Costa atende Fernanda com urgencia nivel 1
  3. Dra. Carla Ramos atende Gabriel com urgencia nivel 2
  4. Dra. Ana Lima atende Helena com urgencia nivel 1

Último atendimento registrado: Dra. Ana Lima → Helena com urgencia nivel 1

Relatório de atendimentos:
  1. Dra. Ana Lima → Helena com urgencia nivel 1
  2. Dra. Carla Ramos → Gabriel com urgencia nivel 2
  3. Dr. Bruno Costa → Fernanda com urgencia nivel 1
  4. Dra. Ana Lima → Eduardo com urgencia nivel 3
```

## Estrutura do repositório

```
├── atendimento_template.cpp   # código implementado
└── README.md                  # instruções
```

## Equipe

- Thiago Ireno