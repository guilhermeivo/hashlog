# hashlog

<img src="assets/log-big.png" align="left" width="128" height="128" alt="log big">

> Sistema de conversas baseado em commits imutáveis, organizados em um grafo direcionado acíclico (DAG). Cada commit representa uma mensagem e referencia seu commit pai, permitindo ramificações por meio de threads. O modelo garante integridade histórica e possibilita renderização eficiente de conversas completas ou parciais.

## 1. Dependências

```bash
sudo apt install libconfuse-dev
```

## 2. Compilação

```bash
make
```

O binário será gerado no diretório `bin/`.

```bash
./hashlog help
```